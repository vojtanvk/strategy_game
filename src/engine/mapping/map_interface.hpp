/**
 * @file map_interface.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <list>
#include <memory>
#include <set>

struct MapInterface;

#include "space_interface.hpp"

struct MapInterface {
  virtual ~MapInterface() = default;

  /**
   * @brief Max viable size of map. Larger maps won't be loaded
   *
   */
  static const size_t MAX_SIZE = 1024;
  static const size_t MAX_PLAYERS = 6;

  /**
   * @brief Get the dimensions of map
   *
   * @return Coords
   */
  virtual Coords get_dimensions() const = 0;

  /**
   * @brief Get current starting point from list
   *
   * @return Coords
   * @throws IllegalStateException If no more starting points are available
   */
  virtual Coords get_starting_point() = 0;

  /**
   * @brief Get the max movable Spaces as loaded
   *
   * @return size_t
   */
  virtual size_t get_max_movable() const = 0;

  /**
   * @brief Get amount of currently available starting positions
   *
   * @return size_t
   */
  virtual size_t available_starts() const = 0;

  /**
   * @brief Get list of currently available starting points
   *
   * @return const std::list<Coords>&
   */
  virtual const std::list<Coords> &get_starting_points() const = 0;

  /**
   * @brief Get available resources immediately around given coordinates
   *
   * @param where Coordinates from which will
   * be harvested
   *
   * @return std::vector<Materials>
   */
  virtual std::vector<Materials> harvest(const Coords &where) const = 0;

  /**
   * @brief Get immediate surroundings of given coordinates
   *
   * @param where Coordinates of which will be given surroundings
   *
   * @return std::set<std::shared_ptr<SpaceInterface>(x,y)>
   */
  virtual std::vector<std::shared_ptr<SpaceInterface>>
  surroundings(const Coords &where) const = 0;

  /**
   * @brief Get immediate surroundings that are walkable
   *
   * @param where Coordinates of which will be given surroundings
   * @return std::vector<Coords>
   */
  virtual std::vector<Coords>
  walkable_surroundings(const Coords &where) const = 0;

  /**
   * @brief Get area of possible movement from given coordinates and with
   * walking distance
   *
   * @param where Where to start
   * @param move How far can move (Max is set at max movable)
   * @return std::vector<Coords>
   */
  virtual std::vector<Coords> movable_area(const Coords &where,
                                           size_t move) const = 0;

  /**
   * @brief Get the space at given Coordinates
   *
   * @return std::shared_ptr<SpaceInterface>
   * @throws IllegalArgumentException If Coordinates are out of bounds
   */
  virtual std::shared_ptr<SpaceInterface> get_space(const Coords &) const = 0;

  /**
   * @brief Get the map
   *
   * @return const std::vector<std::vector<std::shared_ptr<SpaceInterface>>>&
   */
  virtual const std::vector<std::vector<std::shared_ptr<SpaceInterface>>> &
  get_map() const = 0;
};