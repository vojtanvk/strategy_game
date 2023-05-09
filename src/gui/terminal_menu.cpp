/**
 * @file terminal_menu.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <sstream>

#include "../api/human_controller.hpp"
#include "../config/game_config_generator.hpp"
#include "../config/graphic_config_generator.hpp"
#include "../engine/game.hpp"
#include "../engine/player/player.hpp"
#include "../loader/loaders.hpp"
#include "terminal_gui.hpp"
#include "terminal_menu.hpp"

int TerminalMenu::main_menu(const std::optional<std::string> &opt_gui_conf,
                            const std::optional<std::string> &opt_game_conf,
                            const std::optional<std::string> &opt_map_file) {

  if (opt_game_conf && opt_gui_conf) {
    switch (new_game(*opt_game_conf, *opt_gui_conf, opt_map_file)) {
    case MenuState::Menu:
      break;
    case MenuState::Quit:
      return 0;
    default:
      return 1;
    }
  }
  while (true) {
    switch (read_in<char>(draw_menu({"New Game", "Load Game", "Quit"}))) {

    case 'N':
    case 'n':
      try {
        std::string game_conf;
        if (!opt_game_conf) {
          std::cout << "Please input game configuration file path: ";
          game_conf = read_in<std::string>();
        } else {
          game_conf = *opt_game_conf;
        }

        std::string gui_conf;
        if (!opt_gui_conf) {
          std::cout << "Please input gui configuration file path: ";
          gui_conf = read_in<std::string>();
        } else {
          gui_conf = *opt_gui_conf;
        }

        switch (new_game(game_conf, gui_conf, opt_map_file)) {
        case MenuState::Menu:
          break;
        case MenuState::Quit:
          return 0;
        default:
          return 1;
        }
      } catch (const Exception &ex) {
        std::cout << "Game encountered an unexpected error: \""
                  << ex.get_message() << "\" and will now shut down."
                  << std::endl;
        return 1;
      }
      break;
    case 'L':
    case 'l':
      try {
        std::string gui_conf;
        if (!opt_gui_conf) {
          std::cout << "Please input gui configuration file path: ";
          gui_conf = read_in<std::string>();
        } else {
          gui_conf = *opt_gui_conf;
        }
        switch (load_game(gui_conf)) {
        case MenuState::Menu:
          break;
        case MenuState::Quit:
          return 0;
        default:
          return 1;
        }
      } catch (const Exception &ex) {
        std::cout << "Game encountered an unexpected error: \""
                  << ex.get_message() << "\" and will now shut down."
                  << std::endl;
        return 1;
      }
      break;
    case 'Q':
    case 'q':
      std::cout << "Goodbye" << std::endl;
      return 0;

    default:
      return 1;
    }
  }
}

MenuState TerminalMenu::runtime_menu(const GameInterface &game) const {
  switch (read_in<char>(
      draw_menu({"Continue", "Save Game", "Main Menu", "Quit"}))) {
  case 'C':
  case 'c':
    return MenuState::Continue;
  case 'S':
  case 's':
    save_game(game);
    return MenuState::Continue;
  case 'M':
  case 'm':
    // Do nothing and return to menu (quit game without saving)
    return MenuState::Menu;
  case 'Q':
  case 'q':
  default:
    return MenuState::Quit;
  }
}

void TerminalMenu::save_game(const GameInterface &game) const {
  std::set<std::string> cancel{"-C", "-c", "-cancel", "-Cancel", "-CANCEL"};
  std::cout
      << "Please, input save path(\".\") name your save file: (-c: cancel)";
  while (true) {
    std::string answer{read_in<std::string>()};
    if (cancel.count(answer)) {
      std::cout << "Game not saved";
      std::cin.clear();
      return;
    }
    auto path{answer};
    auto filename{read_in<std::string>()};
    try {
      GameLoader().save(path, filename, game);
      std::cin.clear();
      return;
    } catch (const Exception &ex) {
      std::cout
          << "An exception occured: \"" << ex.get_message()
          << "\". Please try secting a diffferent path (\".\") and save file: "
             "(-c: cancel)";
    }
  }
}

MenuState
TerminalMenu::new_game(const std::string &game_conf,
                       const std::string &gui_conf,
                       const std::optional<std::string> &opt_map_file) const {
  Game game{};
  GameConfigGenerator{game, game_conf};
  TerminalGui gui{game};
  GraphicConfigGenerator{game, gui, gui_conf};

  std::string map_file;
  if (!opt_map_file) {
    std::cout << "Please, input map file on which you want to play: ";
    map_file = read_in<std::string>();
  } else {
    map_file = *opt_map_file;
  }

  size_t max_players{0};
  while (!game.get_map()) {
    try {
      max_players = game.dock_map(MapLoader().load(map_file));
    } catch (const Exception &ex) {
      std::cout << "Program ran into an unexpected error while loading map: \""
                << ex.get_message()
                << "\". Please, select a different map file: ";
      map_file = read_in<std::string>();
    }
  }

  gui.draw_map();
  std::list<Coords> starting_points{game.get_map()->get_starting_points()};
  gui.highlight(enumerate_vector(
      std::vector<Coords>{starting_points.begin(), starting_points.end()}));
  std::cout << "Max player count on this map is: " << max_players << std::endl;

  std::set<std::string> yes{"Y", "y", "Yes", "yes", "YES"};
  std::set<std::string> no{"N", "n", "No", "no", "NO"};
  std::set<std::string> cancel{"C", "c", "cancel", "Cancel", "CANCEL"};

  std::string answer;
  const auto i_equal = [&](const auto &in) { return in == answer; };
  while (game.get_map()->available_starts()) {
    gui.message("Add player? y/n");
    if (!(std::cin >> answer)) {
      throw InputException();
    }

    if (std::any_of(yes.begin(), yes.end(), i_equal)) {
      std::shared_ptr<Player> player{std::make_shared<Player>()};
      player->dock_player(std::make_shared<HumanController>(game, gui, *this));
      player->set_colour(list_colours()[game.get_players().size()]);
      game.add_player_start(player);
      gui.message("Player: " + name_colour(player->get_colour()) + " added");
      continue;
    }

    if (std::any_of(no.begin(), no.end(), i_equal)) {
      break;
    }

    if (std::any_of(cancel.begin(), cancel.end(), i_equal)) {
      return MenuState::Menu;
    }
  }
  auto winner = game.start();
  while (!winner) {
    switch (runtime_menu(game)) {
    case MenuState::Continue:
      break;
    case MenuState::Menu:
      return MenuState::Menu;
    case MenuState::Quit:
    default:
      return MenuState::Quit;
    }
    winner = game.run();
  }

  std::cout << "Congratulations! Player: " << name_colour(winner->get_colour())
            << " won!" << std::endl;
  return MenuState::Menu;
}

MenuState TerminalMenu::load_game(const std::string &gui_conf) const {
  Game game{};
  std::cout << "Please, input save path and file which you want to load: ";
  bool game_loaded{false};
  while (!game_loaded) {
    try {
      auto path{read_in<std::string>()};
      auto filename{read_in<std::string>()};
      GameLoader().load(path, filename, game);
      game_loaded = true;
    } catch (const Exception &ex) {
      std::cout << "Program ran into an unexpected error while loading game: \""
                << ex.get_message()
                << "\". Please, select a different save file: ";
    }
  }

  TerminalGui gui{game};
  GraphicConfigGenerator(game, gui, gui_conf);

  auto controller{std::make_shared<HumanController>(game, gui, *this)};
  std::for_each(game.get_players().begin(), game.get_players().end(),
                [&](const auto &player) { player->dock_player(controller); });

  auto winner = game.run();
  while (!winner) {
    switch (runtime_menu(game)) {
    case MenuState::Continue:
      break;
    case MenuState::Menu:
      return MenuState::Menu;
    case MenuState::Quit:
    default:
      return MenuState::Quit;
    }
    winner = game.run();
  }

  std::cout << "Congratulations! Player: " << name_colour(winner->get_colour())
            << " won!" << std::endl;
  return MenuState::Menu;
}

std::set<char>
TerminalMenu::draw_menu(const std::vector<std::string> &menu) const {
  std::set<char> out;
  std::for_each(menu.begin(), menu.end(), [&](const std::string &line) {
    char option = this->underline_first(line);
    if (islower(option)) {
      out.insert(toupper(option));
    } else {
      out.insert(tolower(option));
    }
    out.insert(option);
    std::cout << std::endl;
  });
  return out;
}

char TerminalMenu::underline_first(const std::string &line) const {
  if (line.empty()) {
    return 0;
  }
  std::string m_line{line};
  char out = m_line.front();
  std::cout << "\u001b[4m" << m_line.front() << "\u001b[0m";
  m_line.erase(0, 1);
  std::cout << m_line;
  return out;
}
