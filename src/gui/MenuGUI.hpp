/**
 * @file MenuGUI.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <optional>

#include "../engine/game_interface.hpp"

enum class MenuState { Continue, Menu, Quit };

/**
 * @brief Interface for Menu GUI that specifies all methods available for
 * calling from outside sources
 *
 */
struct MenuGUI {

  /**
   * @brief Draws main menu and awaits player's input before continuing
   *
   * @param gui_conf OPTIONAL Path to gui configuration file
   * @param game_conf OPTIONAL Path to game configuration file
   * @param map_file OPTIONAL Path to map file
   *
   * @return int Standard return (0 if OK; !=0 if error)
   */
  virtual int
  main_menu(const std::optional<std::string> &gui_conf = std::nullopt,
            const std::optional<std::string> &game_conf = std::nullopt,
            const std::optional<std::string> &map_file = std::nullopt) = 0;

protected:
  /**
   * @brief Draws runtime menu (during game) and awaits player's input
   *
   * @param game Running Game in case player wants to save
   *
   * @return MenuState
   */
  virtual MenuState runtime_menu(const GameInterface &game) const = 0;

  /**
   * @brief Resolves all necessities to sart a new game, including loading map
   * and connecting players
   *
   * @param game_conf Path to game configuration file
   * @param gui_conf Path to gui configuration file
   * @param map_file OPTIONAL Path to map file
   *
   * @return MenuState State defining what should happen in menu
   */
  virtual MenuState
  new_game(const std::string &game_conf, const std::string &gui_conf,
           const std::optional<std::string> &map_file = std::nullopt) const = 0;

  /**
   * @brief Resolves all necessities to load saved game and connect players
   *
   * @param gui_conf Path to gui configuration file
   *
   * @return MenuState State defining what should happen in menu
   */
  virtual MenuState load_game(const std::string &gui_conf) const = 0;

  /**
   * @brief Saves given name based on player input
   *
   * @param game Game to be saved
   *
   * @throws In children
   */
  virtual void save_game(const GameInterface &game) const = 0;
};