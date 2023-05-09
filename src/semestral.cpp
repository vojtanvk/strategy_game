/**
 * @file semestral.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <memory>
#include <sstream>
#include <string.h>

#include "api/human_controller.hpp"
#include "config/game_config_generator.hpp"
#include "config/graphic_config_generator.hpp"
#include "engine/game.hpp"
#include "engine/mapping/mapping.hpp"
#include "engine/player/cards/actions.hpp"
#include "engine/player/cards/card.hpp"
#include "engine/player/cards/deck.hpp"
#include "engine/player/player.hpp"
#include "engine/player/units/units.hpp"
#include "gui/terminal_gui.hpp"
#include "gui/terminal_menu.hpp"
#include "loader/loaders.hpp"

template <typename Item>
std::vector<std::pair<Item, char>>
enumerate_vector(const std::vector<Item> &to_enumerate) {
  std::vector<std::pair<Item, char>> out;
  for (size_t i = 0; i < to_enumerate.size(); ++i) {
    if (i < 10) {
      out.push_back({to_enumerate[i], '0' + i});
    } else {
      out.push_back({to_enumerate[i], 'a' + i});
    }
  }
  return out;
}

size_t load_map(GameInterface &game, const GUI &gui) {
  std::stringstream ss;
  while (true) {
    gui.message("Please select map on which you want to play: ");
    std::string map_path;
    if (!(std::cin >> map_path)) {
      throw InputException();
    }

    try {
      return game.dock_map(MapLoader().load(map_path));
    } catch (const Exception &ex) {
      std::stringstream ss;
      ss << "An error occured while loading map: " << ex.get_message();
      gui.message(ss.str());
    }
  }
}

int main(int argc, char **argv) {
  std::cout << "Run program with -c for config generators" << std::endl
            << "Run program with up to 3 arguments (gui config file, game "
               "config file, map file)"
            << std::endl;

  if (argc >= 2 && strcmp(argv[1], "-c") == 0) {
    Game game{};
    TerminalGui gui{game};
    try {
      GameConfigGenerator().start(game);
      GraphicConfigGenerator().start(game, gui);
    } catch (const Exception &ex) {
      std::cout << "An unexpected error occured \"" << ex.get_message()
                << "\" program will now shut down.";
      return 1;
    }
    return 0;
  }
  try {
    if (argc >= 4) {
      return TerminalMenu().main_menu(argv[1], argv[2], argv[3]);
    } else if (argc >= 3) {
      return TerminalMenu().main_menu(argv[1], argv[2]);
    } else if (argc >= 2) {
      return TerminalMenu().main_menu(argv[1]);
    }
    return TerminalMenu().main_menu();
  } catch (const Exception &ex) {
    std::cout << "Program will be terminated after: \"" << ex.get_message()
              << "\"" << std::endl;
    return 1;
  }
}