/**
 * @file terminal_menu.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../exceptions/exception.hpp"
#include "MenuGUI.hpp"

struct TerminalMenu : public MenuGUI {
  int main_menu(const std::optional<std::string> & = std::nullopt,
                const std::optional<std::string> & = std::nullopt,
                const std::optional<std::string> & = std::nullopt) override;

private:
  /**
   * @throws IllegalStateException On input fail
   */
  MenuState runtime_menu(const GameInterface &) const override;

  MenuState
  new_game(const std::string &, const std::string &,
           const std::optional<std::string> & = std::nullopt) const override;
  MenuState load_game(const std::string &) const override;
  void save_game(const GameInterface &) const override;

  /**
   * @brief Draws menu with given option
   *
   * @param options Vector of options to be drawn and inserted in output set
   *
   * @return std::set<char> Valid input set (Upper and Lower case first letter
   * of each option)
   */
  std::set<char> draw_menu(const std::vector<std::string> &options) const;

  /**
   * @brief Print line with underlined first character
   *
   * @param line String to be printed
   * @return char Underlinech character
   */
  char underline_first(const std::string &line) const;

  /**
   * @brief Cycles until valid input is read or until input fail
   *
   * @tparam Input Type of input to be read
   * @param valid Set of valid input, empty if any is valid
   * @return Input Read value of given type
   * @throws IllegalStateException On input fail
   */
  template <typename Input>
  Input read_in(const std::set<Input> &valid = {}) const {
    Input input;
    while (true) {
      if (!(std::cin >> input)) {
        std::cin.clear();
        throw InputException();
      }
      std::cout << std::endl;

      if (valid.empty() || valid.count(input)) {
        return input;
      }
    }
  }

  /**
   * @brief Assigns input char to every element of given vector
   *
   * @tparam Item Type of object can be selected
   * @param to_enumerate Vector of objects from which is to be selected
   * @return std::vector<std::pair<Item, char>> Vector with assigned inputs
   * ('1','2', .. ,'a','b')
   * @throws IllegalArgumentException If to_enumerate is too big to enumerate
   */
  template <typename Item>
  std::vector<std::pair<Item, char>>
  enumerate_vector(const std::vector<Item> &to_enumerate) const {
    std::vector<std::pair<Item, char>> out;
    if (to_enumerate.size() > (('9' - '0') + 1 + ('z' - 'a') + 1)) {
      throw IllegalArgumentException("Vector is too big to enumerate");
    }
    for (size_t i = 0; i < to_enumerate.size(); ++i) {
      if (i < ('9' - '0' + 1)) {
        out.push_back({to_enumerate[i], '0' + i});
      } else {
        out.push_back({to_enumerate[i], 'a' + i});
      }
    }
    return out;
  }
};
