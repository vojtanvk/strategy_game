/**
 * @file graphic_config_generator.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <optional>
#include <vector>

#include "../engine/game_interface.hpp"
#include "../gui/GUI.hpp"
#include "../loader/file_loader.hpp"
#include "../loader/my_file.hpp"

struct GraphicConfigGenerator : public FileLoader {
  GraphicConfigGenerator() = default;

  /**
   * @brief Immediately loads given config form file to gui
   *
   * @param game To check if gui is valid (Every unit needs symbol and
   * name)
   * @param gui To be loaded
   * @param filename Path to gui configuration file to read
   */
  GraphicConfigGenerator(GameInterface &game, GUI &gui,
                         const std::string &filename);

  /**
   * @brief Starts gui generator tool
   * Lets User choose if he/she wants to load configuration or create new one
   *
   * @param game To check if gui is valid (Every unit needs symbol and
   * name)
   * @param gui To be loaded
   * @return int Standard exit code
   */
  int start(GameInterface &game, GUI &gui) const;

private:
  /**
   * @brief Guides User thorugh configuration creation
   *
   * @param game To check if gui is valid (Every unit needs symbol and
   * name)
   * @param gui To be loaded
   * @return int Standard exit code
   * @throws FileWriteException If write fails
   */
  int create(GameInterface &game, GUI &gui) const;

  /**
   * @brief Loads gui configuration into gui
   *
   * @param game To check if gui is valid (Every unit needs symbol and
   * name)
   * @param gui To be loaded
   * @param filename OPTIONAL Gui configuration file to load
   * @return int Standard exit code
   * @throws FileReadException If read fails
   * @throws CorruptedFileException If file is in unexpected state
   */
  int load(GameInterface &game, GUI &gui,
           const std::optional<std::string> &filename = std::nullopt) const;

  /**
   * @brief Returns given string with underlined first character
   *
   * @return std::string
   */
  std::string underline_first(const std::string &) const;
};