/**
 * @file terminal_gui.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <sstream>

#include "../exceptions/exception.hpp"
#include "terminal_gui.hpp"

TerminalGui::TerminalGui(GameInterface &game) : game(game) {}

void TerminalGui::message(const std::string &message) const {
  std::cout << message << std::endl;
}

void TerminalGui::print_help() const {
  message("Help:");
  message(" Press H for help");
  message(" Press M to show map");
  message(" Press R to show resources");
  message(" Press D to show deck");
  message(" Press W to list conditions to win");
  message(" Press C to show action choices again");
  message(" Press ~ to cancel current action");
}

void TerminalGui::draw_map() const {
  if (!game.get_map()) {
    std::cout << "No map present. Can't draw!" << std::endl;
    return;
  }

  auto mp = game.get_map()->get_map();
  for (auto line = mp.rbegin(); line != mp.rend(); line++) {
    std::cout << map_colour;
    for (auto sp = line->begin(); sp != line->end(); ++sp) {
      if ((*sp)->is_occupied()) {
        std::cout << to_code_colour_front(
            (*sp)->get_occupant()->get_owner().get_colour());
        std::cout << symbol_unit((*sp)->get_occupant()->get_id());
      } else {
        std::cout << coloured_surface((*sp)->get_surface());
      }
    }
    std::cout << reset_colour() << std::endl;
  }
}

void TerminalGui::draw_deck(const Deck &to_draw) const {
  std::cout << "Draw pile: ";
  if (to_draw.get_draw_pile().empty()) {
    std::cout << "empty";
  } else {
    std::cout << to_draw.get_draw_pile().size();
  }
  std::cout << std::endl;
  std::cout << "------------" << std::endl;
  std::cout << "Hand:" << (to_draw.get_hand().empty() ? " empty" : "")
            << std::endl;
  draw_cards(to_draw.get_hand());
  std::cout << "------------" << std::endl;
  std::cout << "Discard pile: ";
  if (to_draw.get_discard_pile().empty()) {
    std::cout << "empty";
  } else {
    std::cout << to_draw.get_discard_pile().size();
  }
  std::cout << std::endl;
}

void TerminalGui::draw_discard_pile(const Deck &to_draw) const {
  std::cout << "Discard pile: ";
  if (to_draw.get_discard_pile().empty()) {
    std::cout << "empty";
  } else {
    std::cout << to_draw.get_discard_pile().size();
  }
  std::cout << std::endl;

  draw_cards(to_draw.get_discard_pile());
}

void TerminalGui::draw_resources(
    const std::map<Materials, size_t> &resources) const {
  for (const auto &res : resources) {
    std::cout << " " << to_string(res.first) << ": " << res.second;
  }
  std::cout << std::endl;
}

void TerminalGui::draw_player(const PlayerInterface &player) const {
  draw_map();
  std::cout << "Player: " << map_colour
            << to_code_colour_front(player.get_colour())
            << name_colour(player.get_colour()) << reset_colour()
            << " is currently playing" << std::endl;
}

void TerminalGui::draw_win_conditions() const {
  std::cout << "Winning conditions are: " << std::endl;
  std::for_each(game.get_win_cons().begin(), game.get_win_cons().end(),
                [&](const WinCon &win_con) {
                  std::cout << "Gather: ";
                  this->draw_resources(win_con.get_materials());
                  std::cout << "; "
                            << "Get points: " << win_con.get_points() << "; "
                            << "Raise army: " << win_con.get_unit_count()
                            << std::endl;
                });
  std::cout << "Complete one of these to win!" << std::endl;
}

void TerminalGui::highlight(
    const std::vector<std::pair<Coords, char>> &to_highlight) const {
  std::for_each(to_highlight.begin(), to_highlight.end(),
                [&](const auto &item) {
                  write_on_map(item.second, to_code_colour_back(Colour::black),
                               item.first);
                });
}

void TerminalGui::highlight(const Coords &actor,
                            const std::vector<Coords> &to_highlight) const {
  draw_map();
  for (const auto &draw : to_highlight) {
    write_on_map(' ', to_code_colour_back(Colour::yellow), draw);
  }
  write_on_map('A', to_code_colour_back(Colour::black), actor);
}

void TerminalGui::select_unit(
    const std::vector<std::shared_ptr<UnitInterface>> &units,
    const std::vector<char> &selection) const {
  // std::cout << "units: " << units.size() << std::endl;
  if (units.empty()) {
    std::cout << "No units to choose from" << std::endl;
    return;
  }

  draw_map();
  for (size_t i = 0; i < units.size(); ++i) {
    write_on_map(selection[i], to_code_colour_back(Colour::black),
                 units[i]->get_position());
  }

  std::cout << "Please select unit: " << std::endl;
  for (size_t i = 0; i < units.size(); ++i) {
    std::cout << " " << selection[i] << ": " << name_unit(units[i]->get_id())
              << "[" << units[i]->get_position().x << ","
              << units[i]->get_position().y << "]";
  }
  std::cout << std::endl;
}

void TerminalGui::select_material(const std::vector<Materials> &materials,
                                  const std::vector<char> &selection) const {
  for (size_t i = 0; i < materials.size(); ++i) {
    std::cout << " " << selection[i] << ": " << to_string(materials[i]);
  }
  std::cout << std::endl;
}

void TerminalGui::select_movement(const Coords &start, const Coords &actor,
                                  const std::vector<Coords> &moves,
                                  const std::vector<Coords> &area,
                                  const std::vector<char> &selection) const {
  highlight(actor, area);

  write_on_map('S', to_code_colour_back(Colour::black), start);

  std::cout << "Please select move: " << std::endl;
  for (size_t i = 0; i < moves.size(); ++i) {
    std::cout << " " << selection[i] << ": "
              << to_string(actor.get_direction_to(moves[i])) << "["
              << moves[i].x << "," << moves[i].y << "]";
  }
  std::cout << " ;: to stop moving" << std::endl;
}

void TerminalGui::build(const Coords &actor, const std::vector<Coords> &where,
                        const std::vector<Blueprint> &to_build,
                        const std::vector<char> &selection) const {
  highlight(actor, where);

  std::cout << "Please what to build: " << std::endl;
  for (size_t i = 0; i < to_build.size(); ++i) {
    std::cout << " " << selection[i] << ": " << name_unit(to_build[i].get_id())
              << "{";
    for (const auto &m : to_build[i].get_cost()) {
      std::cout << " " << to_string(m.first) << ": " << m.second;
    }
    std::cout << " }" << std::endl;
  }
}

void TerminalGui::select_buildplace(
    const Coords &actor, const std::vector<Coords> &surroundings,
    const std::vector<char> &viable_input) const {
  draw_map();
  write_on_map('A', to_code_colour_back(Colour::black), actor);
  for (size_t i = 0; i < surroundings.size(); ++i) {
    write_on_map(viable_input[i], to_code_colour_back(Colour::black),
                 surroundings[i]);
  }
  std::cout << "Please select where to build: " << std::endl;
  for (size_t i = 0; i < surroundings.size(); ++i) {
    std::cout << " " << viable_input[i] << ": "
              << to_string(actor.get_direction_to(surroundings[i])) << "["
              << surroundings[i].x << "," << surroundings[i].y << "]";
  }
  std::cout << std::endl;
}

void TerminalGui::select_card(const Deck &to_draw,
                              const std::vector<char> &selection) const {
  std::cout << "Draw pile: ";
  if (to_draw.get_draw_pile().empty()) {
    std::cout << "empty";
  } else {
    std::cout << to_draw.get_draw_pile().size();
  }
  std::cout << std::endl;
  std::cout << "------------" << std::endl;
  std::cout << "Hand:" << (to_draw.get_hand().empty() ? " empty" : "")
            << std::endl;
  draw_cards(to_draw.get_hand(), selection);
  std::cout << "------------" << std::endl;
  std::cout << "Discard pile: ";
  if (to_draw.get_discard_pile().empty()) {
    std::cout << "empty";
  } else {
    std::cout << to_draw.get_discard_pile().size();
  }
  std::cout << std::endl;
}

std::string TerminalGui::coloured_surface(Surface surf) const {
  std::stringstream ss;
  try {
    ss << surf_col_symbol.at(surf).first << surf_col_symbol.at(surf).second;
    return ss.str();
  } catch (const std::out_of_range &) {
    throw IllegalArgumentException("Unspecified surface");
  }
}

char TerminalGui::symbol_unit(size_t id) const {
  try {
    return id_name_symbol.at(id).second;
  } catch (const std::out_of_range &) {
    throw IllegalArgumentException("Unspecified unit id");
  }
}

std::string TerminalGui::name_unit(size_t id) const {
  try {
    return id_name_symbol.at(id).first;
  } catch (const std::out_of_range &) {
    throw IllegalArgumentException("Unspecified unit id");
  }
}

void TerminalGui::write_on_map(char what, const std::string &ascii,
                               const Coords &where) const {
  std::cout << SAVE_CUR << move_cursor(1, UP_CUR) << LINE_START_CUR
            << move_cursor(where.y, UP_CUR)
            << move_cursor(where.x + 1, RIGHT_CUR) << BACKSPACE << ascii << what
            << RESTORE_CUR;
}

void TerminalGui::draw_cards(
    const std::vector<std::shared_ptr<CardInterface>> &container,
    const std::vector<char> &selection) const {
  bool custom_sel = !selection.empty();

  for (size_t i = 0; i < container.size(); ++i) {
    std::cout << (custom_sel ? selection[i] - '0' : i) << ": ";
    auto &actions = container[i]->get_actions();
    for (auto it = actions.begin(); it != actions.end(); it++) {
      std::cout << to_string((*it)->get_type()) << " " << (*it)->get_value();
      if (next(it) != actions.end()) {
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
  }
}

void TerminalGui::add_surface_graphic(Surface surf, const std::string &colour,
                                      char symbol) {
  surf_col_symbol[surf] = {colour, symbol};
}
void TerminalGui::add_unit_graphic(size_t id, const std::string &name,
                                   char symbol) {
  id_name_symbol[id] = {name, symbol};
}
void TerminalGui::set_map_background(const std::string &colour_code) {
  map_colour = colour_code;
}

std::string TerminalGui::move_cursor(size_t x, char dir) const {
  std::stringstream ss;
  ss << "\033[" << x << dir;
  return ss.str();
}