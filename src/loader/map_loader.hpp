/**
 * @file map_loader.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>

#include "../engine/mapping/map_interface.hpp"
#include "file_loader.hpp"

class MapLoader : public FileLoader {
public:
  /**
   * @brief Creates map savefile with given name at given path
   *
   * @param path Path to save directory
   * @param filename Name of file to be created
   * @param map Map to save
   *
   * @throws FileWriteException If write fails
   */
  void save(const std::string &path, const std::string &filename,
            const std::shared_ptr<MapInterface> &map) const;

  /**
   * @brief Loads map from given file
   *
   * @param path_filename Path to file to be read
   * @return std::shared_ptr<MapInterface> Loaded map
   * @throws FileWriteException If read fails
   * @throws CorruptedFileException If file is not in expected state
   */
  std::shared_ptr<MapInterface> load(const std::string &path_filename) const;

private:
  /**
   * @brief Create new space based on given data
   *
   * @param type Char to be translated into Surface
   * @param x X coordinate of Space
   * @param y Y coordinate of Space
   * @return std::shared_ptr<SpaceInterface> Created Space
   */
  std::shared_ptr<SpaceInterface> space_factory(char type, size_t x,
                                                size_t y) const;
};