/**
 * @file game_config_generator.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <optional>
#include <vector>

#include "../engine/game_interface.hpp"
#include "../engine/player/cards/action_type.hpp"
#include "../engine/player/units/blueprint.hpp"
#include "../loader/file_loader.hpp"

struct GameConfigGenerator : public FileLoader {
  GameConfigGenerator() = default;
  /**
   * @brief Constructs and immediately loads game from given game configuration
   * file
   *
   * @param game To be loaded
   * @param filename Path to game configuration file
   */
  GameConfigGenerator(GameInterface &game, const std::string &filename);

  /**
   * @brief Guides User through game configuration
   *
   * @return int Standard exit code
   */
  int start(GameInterface &) const;

  enum class ToConfig { units, deck, wincon };

  /**
   * @brief Names ToConfig option
   *
   * @param config To name
   * @return std::string Name of ToConfig option with first character underlined
   * @throws IllegalArgumentException If unknown config is given
   */
  std::string to_string(ToConfig config) const;
  /**
   * @brief Translates ToConfig to char
   *
   * @param config To translate
   * @return char
   * @throws IllegalArgumentException If unknown config is given
   */
  char to_char(ToConfig config) const;
  /**
   * @brief Translates char to ToConfig
   *
   * @param config To translate
   * @return ToConfig
   * @throws IllegalArgumentException If unknown config is given
   */
  ToConfig char_to_config(char config) const;

private:
  /**
   * @brief Guides User through creation of game configuration
   *
   * @param game To load
   * @return int Standard exit code
   */
  int create(GameInterface &game) const;

  /**
   * @brief Loads game configration from given file
   *
   * @param game To load
   * @param filename Path to game configuration file to read
   * @return int Standard exit code
   */
  int load(GameInterface &game,
           const std::optional<std::string> &filename = std::nullopt) const;

  /**
   * @brief Underline given string and return in
   *
   * @return std::string
   */
  std::string underline(const std::string &) const;

  /**
   * @brief Lets User create Configuration element and when finished writes it
   * into given file
   *
   * @tparam ConfigType Object that can be loaded edited and written
   * @param file Where to write
   * @param what What is User creating
   * @param symbol What symbol represents it in final file
   * @param game
   * @return true
   * @return false
   */
  template <typename ConfigType>
  bool write(FILE *file, const std::string &what, char symbol,
             GameInterface &game) const {
    const auto m_underline = [](const std::string &line) {
      return "\u001b[4m" + line + "\u001b[0m";
    };
    std::cout << "Creating " << what << ": " << std::endl;

    write_single(file, symbol);
    write_single(file, '{');

    std::vector<ConfigType> arr;

    char input;
    while (true) {
      std::cout << "Select option: " << std::endl
                << " " << m_underline("A") << "dd new; " << m_underline("C")
                << "opy existing; " << m_underline("E") << "dit; "
                << m_underline("R") << "emove; " << m_underline("D") << "one; "
                << "cance" << m_underline("L") << std::endl;

      if (!(std::cin >> input)) {
        return false;
      }

      ConfigType n_obj;
      size_t index{0};
      std::vector<ConfigType> holder;
      switch (input) {
      case 'A':
      case 'a':
        if (n_obj.create(arr)) {
          arr.push_back(n_obj);
        }
        break;
      case 'R':
      case 'r':
        for (const auto &item : arr) {
          std::cout << index << ": ";
          item.print();
          std::cout << std::endl;
          ++index;
        }

        if (!(std::cin >> index)) {
          std::cin.clear();
          break;
        }
        if (index < arr.size()) {
          std::cout << "Removing: ";
          arr[index].print();
          std::cout << std::endl;
          arr.erase(arr.begin() + index);
        }
        break;
      case 'C':
      case 'c':
        for (const auto &item : arr) {
          std::cout << index << ": ";
          item.print();
          std::cout << std::endl;
          ++index;
        }

        if (!(std::cin >> index)) {
          std::cin.clear();
          break;
        }

        if (index < arr.size()) {
          std::cout << "Copying: ";
          arr[index].print();
          std::cout << std::endl;
          arr.insert(arr.begin() + index, arr[index]);
        }
        break;
      case 'E':
      case 'e':
        for (const auto &item : arr) {
          std::cout << index << ": ";
          item.print();
          std::cout << std::endl;
          ++index;
        }

        if (!(std::cin >> index)) {
          std::cin.clear();
          break;
        }

        if (index < arr.size()) {
          std::cout << "Editing: ";
          arr[index].print();
          std::cout << std::endl;
          std::copy(arr.begin(), arr.end(), std::back_inserter(holder));
          holder.erase(holder.begin() + index);
          arr[index].edit(holder);
        }
        break;
      case 'D':
      case 'd':
        if (arr.empty()) {
          std::cout << what << " cannot be empty!" << std::endl;
          break;
        }
        write_single(file, arr.size());
        for (const auto &item : arr) {
          item.write(file);
        }
        write_single(file, '}');

        std::for_each(arr.begin(), arr.end(),
                      [&](const auto &item) { item.load(game); });

        return true;
      case 'L':
      case 'l':
        return false;
      }
    }
    return false;
  }

  template <typename ConfigType>
  void read(FILE *file, GameInterface &game) const {
    read_single(file, '{');

    for (size_t amount{read_single<size_t>(file)}; amount > 0; --amount) {
      ConfigType().read(file).load(game);
    }
    read_single(file, '}');
  }
};
