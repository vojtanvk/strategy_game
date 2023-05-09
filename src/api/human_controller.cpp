/**
 * @file human_controller.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <sstream>

#include "human_controller.hpp"

HumanController::HumanController(GameInterface &game, const GUI &gui,
                                 const MenuGUI &menu)
    : game(game), gui(gui), menu(menu) {}

GameInterface &HumanController::handler_game() { return game; }

int HumanController::select_card(const Deck &deck, const PlayerInterface &actor,
                                 std::shared_ptr<CardInterface> &out) {
  gui.draw_player(actor);
  auto viable_inputs{generate_input_set(deck.get_hand().size())};
  viable_inputs.push_back(STOP);
  while (true) {
    gui.select_card(deck, viable_inputs);
    gui.message(";: end turn ~: quit game");
    char input{process_input({viable_inputs.begin(), viable_inputs.end()})};
    if (input == STOP) {
      return SKIP;
    } else if (input == CANCEL) {
      return ROLLBACK;
    } else if (input == REPEAT) {
      continue;
    } else {
      try {
        out = deck.get_hand().at(input);
      } catch (...) {
        gui.message("Selected card outside of hand please try again");
        continue;
      }
      return CONTINUE;
    }
  }
}

bool HumanController::select_unit(
    const std::vector<std::shared_ptr<UnitInterface>> &units,
    std::shared_ptr<UnitInterface> &out) const {
  size_t cycle{0};
  char input;
  const size_t max_draw_count{9};

  auto viable_input = generate_input_set(units.size(), max_draw_count);
  if (units.size() > max_draw_count) {
    viable_input.push_back(MORE);
  }
  while (true) {
    size_t remaining = units.size() - cycle;
    gui.select_unit(
        {units.begin() + cycle,
         units.begin() + cycle + std::min(remaining, size_t(max_draw_count))},
        viable_input);
    if (viable_input.size() == 10) {
      gui.message("0: more");
    }
    input = process_input({viable_input.begin(), viable_input.end()});
    if (input == MORE) {
      cycle += max_draw_count;
      if (viable_input.size() > remaining) {
        viable_input = generate_input_set(remaining);
      }
    } else if (input == CANCEL) {
      return false;
    } else if (input == REPEAT) {
      continue;
    } else {
      out = units[input + cycle];
      return true;
    }
  }
}

bool HumanController::choose_material(const std::vector<Materials> &materials,
                                      Materials &out) const {
  auto viable_input = generate_input_set(materials.size());

  while (true) {
    gui.message("Your resources are: ");
    gui.draw_resources(game.get_active_player()->get_resources());
    gui.select_material(materials, viable_input);
    char input{process_input({viable_input.begin(), viable_input.end()})};

    if (input == CANCEL) {
      return false;
    } else if (input != REPEAT) {
      out = materials[input];
      return true;
    }
  }
}

int HumanController::read_movement(const Coords &start, Coords &where,
                                   const std::vector<Coords> &surroundings,
                                   const std::vector<Coords> &area) const {
  auto viable_input{generate_input_set(surroundings.size())};

  gui.select_movement(start, where, surroundings, area, viable_input);
  viable_input.push_back(STOP);
  while (true) {
    char input{process_input({viable_input.begin(), viable_input.end()})};
    if (input == CANCEL) {
      return ROLLBACK;
    } else if (input == STOP) {
      return SKIP;
    } else if (input == REPEAT) {
      continue;
    } else {
      where = surroundings[input];
      return CONTINUE;
    }
  }
}

int HumanController::build(const std::vector<Blueprint> &build_list,
                           const Coords &actor,
                           const std::vector<Coords> &surroundings,
                           const std::map<Materials, size_t> &resources,
                           Blueprint &out, Coords &where) const {
  auto viable_input{generate_input_set(build_list.size())};

  while (true) {
    gui.build(actor, surroundings, build_list, viable_input);
    viable_input.push_back(STOP);
    gui.message(";: don't build  ~: cancel");
    gui.message("Your resources are: ");
    gui.draw_resources(resources);
    char input{process_input({viable_input.begin(), viable_input.end()})};
    if (input == CANCEL) {
      return ROLLBACK;
    } else if (input == STOP) {
      return SKIP;
    } else if (input == REPEAT) {
      continue;
    }

    auto to_build = build_list[input];
    const auto &predicate = [&](const auto &m_cost) {
      return resources.at(m_cost.first) < m_cost.second;
    };

    if (std::any_of(to_build.get_cost().begin(), to_build.get_cost().end(),
                    predicate)) {
      gui.message("Insufficient resources, please select another blueprint.");
      continue;
    }

    viable_input = generate_input_set(surroundings.size());
    gui.select_buildplace(actor, surroundings, viable_input);
    input = process_input({viable_input.begin(), viable_input.end()});
    if (input == CANCEL) {
      return ROLLBACK;
    }
    where = surroundings[input];
    out = to_build;
    return CONTINUE;
  }
}

char HumanController::process_input(const std::set<char> &viable_inputs,
                                    bool to_num) const {
  char input;
  while (true) { // TODO
    if (!(std::cin >> input)) {
      throw InputException();
    }
    if (viable_inputs.count(input) || def_inputs.count(input)) {
      // TODO when M, R and other pre-defined entries are read
      // TODO
      // if (commands.count(input)) {
      //   commands[input]();
      // } else {
      //
      switch (input) {
      case MAP:
        gui.draw_map();
        break;
      case RESOURCES:
        gui.message("Your resources are: ");
        gui.draw_resources(game.get_active_player()->get_resources());
        break;
      case DECK:
        gui.draw_deck(game.get_active_player()->get_deck());
        break;
      case HELP:
        gui.print_help();
        break;
      case WIN:
        gui.draw_win_conditions();
        break;
      case REPEAT:
        return REPEAT;
      default:
        if (!to_num) {
          return input;
        }
        if (input > '0' && input <= '9') {
          return input - '1';
        } else if (input >= 'a' && input <= 'z') {
          return input - 'a';
        } else {
          return input;
        }
      }
      continue;
    }
  }
  throw IllegalStateException("Unexpectedly exited loop");
}

std::vector<char> HumanController::generate_input_set(size_t size,
                                                      size_t limit) const {
  std::vector<char> out;
  size_t loops = limit == 0 ? size : std::min(limit, size);
  for (size_t i = 0; i < loops; ++i) {
    if (i >= 9) {
      out.push_back('a' + i - 9);
    } else {
      out.push_back('1' + i);
    }
  }
  return out;
}