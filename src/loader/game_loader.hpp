/**
 * @file game_loader.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <sstream>
#include <string>

#include "../engine/game_interface.hpp"
#include "file_loader.hpp"
#include "player_loader.hpp"

class GameLoader : public FileLoader {
public:
  /**
   * @brief Creates folder at given path with given filename and there creates
   * multiple files describing saved game
   *
   * @param path Where to create directory
   * @param filename New direcotry's name and save file's postfix
   * @param game To be saved
   * @throws FileWriteException If write fails
   */
  void save(const std::string &path, const std::string &filename,
            const GameInterface &game) const;

  /**
   * @brief Tries to open directory of given name at given path and from files
   * saved there loads game into given object
   *
   * @param path Where is save directory located
   * @param filename Name of save directory
   * @param game Game object into which data will be loaded
   * @throws FileReadException If read fails
   * @throws CorruptedFileException If files don't match expectations
   */
  void load(const std::string &path, const std::string &filename,
            GameInterface &game) const;

private:
  /**
   * @brief Save players into created directory (save method)
   *
   * @tparam Container STL container containing players to be saved
   * @param file Main savefile where player savefiles will be written
   * @param filename Main savefile name
   * @param path Path to main savefile directory
   * @param container STL container of PlayerInterfaces (Players)
   * @param prefix Player savefile prefix (p)
   * @param p_loader Object capable of saving/loading players
   *
   * @throws FileWriteException If write fails
   */
  template <typename Container>
  void save_players(FILE *file, const std::string &filename,
                    const std::string &path, const Container &container,
                    char prefix, const PlayerLoader &p_loader) const {
    size_t index{0};
    for (const auto &c : container) {
      std::stringstream c_filename_ss;
      c_filename_ss << prefix << "_" << index << "_" << filename;
      std::string c_filename{c_filename_ss.str()};
      p_loader.save(path, c_filename, c);
      write_string(file, c_filename);
      ++index;
    }
  }
};