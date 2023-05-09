/**
 * @file player_loader.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>
#include <string>

#include "../engine/player/player_interface.hpp"
#include "../engine/player/units/unit_interface.hpp"
#include "file_loader.hpp"

class PlayerLoader : public FileLoader {
public:
  /**
   * @brief Creates player savefile at given path
   *
   * @param path Path into save directory
   * @param filename Name of file to be created
   * @param player Player to be saved
   *
   * @throws FileWriteException If write fails
   */
  void save(const std::string &path, const std::string &filename,
            const std::shared_ptr<PlayerInterface> &player) const;

  /**
   * @brief Loads player from given file
   *
   * @param path Path into save directory
   * @param filename Name of file to read
   * @param game Interface for Cards->Actions
   * @return std::shared_ptr<PlayerInterface> Loaded Player
   * @throws FileReadException If read fails
   * @throws CorruptedFileException If file is in unexpected state
   */
  std::shared_ptr<PlayerInterface> load(const std::string &path,
                                        const std::string &filename,
                                        GameInterface &game) const;

private:
};