/**
 * @file game_config_generator.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../exceptions/exception.hpp"
#include "../loader/my_file.hpp"
#include "config_types.hpp"

#include "game_config_generator.hpp"

std::string GameConfigGenerator::to_string(ToConfig type) const {
  switch (type) {
  case ToConfig::units:
    return underline("U") + "nits";
  case ToConfig::deck:
    return underline("D") + "eck";
  case ToConfig::wincon:
    return underline("W") + "incon";
  default:
    throw IllegalArgumentException("Unknown config type");
  }
}

char GameConfigGenerator::to_char(ToConfig type) const {
  switch (type) {
  case ToConfig::units:
    return 'U';
  case ToConfig::deck:
    return 'D';
  case ToConfig::wincon:
    return 'W';
  default:
    throw IllegalArgumentException("Unknown config type");
  }
}

GameConfigGenerator::ToConfig
GameConfigGenerator::char_to_config(char type) const {
  switch (type) {
  case 'U':
    return ToConfig::units;
  case 'D':
    return ToConfig::deck;
  case 'W':
    return ToConfig::wincon;
  default:
    throw IllegalArgumentException("Unknown config type");
  }
}

GameConfigGenerator::GameConfigGenerator(GameInterface &game,
                                         const std::string &filename) {
  load(game, filename);
}

int GameConfigGenerator::start(GameInterface &game) const {
  std::cout << "Welcome to game config generator" << std::endl;
  std::cout << "This tool was created to help creating and editing config "
               "files for this semestral."
            << std::endl;

  std::cout << "Do you wish to create new config file? y/n" << std::endl;
  std::string input;
  std::vector<std::string> yes{"y", "Y", "yes", "Yes", "YES"};
  std::vector<std::string> no{"n", "N", "no", "NO", "No"};
  while (true) {

    if (!(std::cin >> input)) {
      continue;
    }

    if (std::any_of(yes.begin(), yes.end(),
                    [&](const auto &in) { return in == input; })) {
      return create(game);
    }

    if (std::any_of(no.begin(), no.end(),
                    [&](const auto &in) { return in == input; })) {
      return load(game);
    }
  }
}

int GameConfigGenerator::create(GameInterface &game) const {
  std::cout << "Please name Your config file: ";
  std::string path;
  if (!(std::cin >> path)) {
    std::cerr << "Invalid input" << std::endl;
    return 1;
  }

  std::map<ToConfig, bool> configured{{ToConfig::deck, false},
                                      {ToConfig::units, false},
                                      {ToConfig::wincon, false}};

  try {
    MyFile file{path, "w"};
    write_string(file, "GameConf");
    char input;

    //
    while (std::any_of(configured.begin(), configured.end(),
                       [](const auto &item) { return !item.second; })) {
      std::cout << "Select to configure next:" << std::endl;
      std::for_each(configured.begin(), configured.end(),
                    [&](const auto &conf) {
                      if (!conf.second) {
                        std::cout << " " << to_string(conf.first);
                      }
                    });
      std::cout << std::endl;

      if (!(std::cin >> input)) {
        throw Exception(10, "Write ended prematurely");
      }

      switch (input) {
      case 'D':
      case 'd':
        if (configured[ToConfig::deck]) {
          break;
        }
        if (!write<CardConfig>(file, "deck", to_char(ToConfig::deck), game)) {
          break;
        }
        configured[ToConfig::deck] = true;
        break;
      case 'U':
      case 'u':
        if (configured[ToConfig::units]) {
          break;
        }
        if (!write<UnitConfig>(file, "units", to_char(ToConfig::units), game)) {
          break;
        }
        configured[ToConfig::units] = true;
        break;
      case 'W':
      case 'w':
        if (configured[ToConfig::wincon]) {
          break;
        }
        if (!write<WinConfig>(file, "wincon", to_char(ToConfig::wincon),
                              game)) {
          break;
        }
        configured[ToConfig::wincon] = true;
        break;
      default:
        break;
      }
    }
  } catch (const Exception &ex) {
    std::cerr << "Error: " << ex.get_message() << std::endl;
    remove(path.data());
    return 1;
  }

  return 0;
}

int GameConfigGenerator::load(
    GameInterface &game, const std::optional<std::string> &filename) const {

  std::string path;
  if (filename) {
    path = *filename;
  } else {
    std::cout << "Input path to config file: ";
    path = read_in<std::string>({});
  }

  MyFile file(path, "r");
  std::cout << std::endl;
  if (read_string(file) != "GameConf") {
    throw CorruptedFileException();
  }

  std::map<ToConfig, bool> configured{{ToConfig::deck, false},
                                      {ToConfig::units, false},
                                      {ToConfig::wincon, false}};
  try {
    while (std::any_of(configured.begin(), configured.end(),
                       [](const auto &item) { return !item.second; })) {
      char conf{read_single<char>(file)};
      switch (char_to_config(conf)) {
      case ToConfig::deck:
        read<CardConfig>(file, game);
        configured[ToConfig::deck] = true;
        break;
      case ToConfig::units:
        read<UnitConfig>(file, game);
        configured[ToConfig::units] = true;
        break;
      case ToConfig::wincon:
        read<WinConfig>(file, game);
        configured[ToConfig::wincon] = true;
        break;
      default:
        throw CorruptedFileException();
      }
    }
  } catch (const Exception &ex) {
    std::cerr << "Error: " << ex.get_message() << std::endl;
    return 1;
  }
  return 0;
}

std::string GameConfigGenerator::underline(const std::string &line) const {
  return "\u001b[4m" + line + "\u001b[0m";
}
