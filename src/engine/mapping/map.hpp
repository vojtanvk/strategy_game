/**
 * @file map.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <vector>

#include "map_interface.hpp"

class Map : public MapInterface {
public:
  virtual ~Map() = default;

  static const size_t max_dimension = 1024;

  Map(const std::vector<std::vector<std::shared_ptr<SpaceInterface>>> &map,
      const std::list<Coords> &starting_points);

  /**
   * @brief Get the dimensions of map
   *
   * @return Coords
   */
  Coords get_dimensions() const override;

  Coords get_starting_point() override;
  size_t get_max_movable() const override;
  size_t available_starts() const override;
  const std::list<Coords> &get_starting_points() const override;

  /**
   * @brief Get available resources immediately around given coordinates
   *
   * const std::shared_ptr<SpaceInterface> & where - coordinates from which we
   * harvest
   *
   * @return std::vector<Materials>
   */
  std::vector<Materials> harvest(const Coords &) const override;
  // std::vector<Materials> harvest(const Coords &) const override;

  /**
   * @brief Get immediate surrounding of given coordinates
   *
   * const std::shared_ptr<SpaceInterface> & where - coordinates of which we
   * want surroundings
   *
   * @return std::set<std::shared_ptr<SpaceInterface>>
   */
  std::vector<std::shared_ptr<SpaceInterface>>
  surroundings(const Coords &) const override;

  /**
   * @brief Get immediate walkable surrounding of given coordinates
   *
   * const std::shared_ptr<SpaceInterface> & where - coordinates of which we
   * want surroundings
   *
   * @return std::set<std::shared_ptr<SpaceInterface>>
   */
  // std::set<std::shared_ptr<SpaceInterface>>
  // walkable_surroundings(const std::shared_ptr<SpaceInterface> &) const
  // override;

  std::vector<Coords> walkable_surroundings(const Coords &) const override;

  /**
   * @brief Get area of possible movement from given coordinates{start} and with
   * walking distance{movement}
   *
   * const std::shared_ptr<SpaceInterface> & start - coordinates of unit about
   * to move size_t movement - max walking distance
   *
   * @return std::set<std::shared_ptr<SpaceInterface>>
   */
  std::vector<Coords> movable_area(const Coords &, size_t) const override;

  /**
   * @brief Get the space at given coordinates
   *
   * @return std::shared_ptr<Space>
   */
  std::shared_ptr<SpaceInterface> get_space(const Coords &) const override;

  const std::vector<std::vector<std::shared_ptr<SpaceInterface>>> &
  get_map() const override;

private:
  std::vector<std::vector<std::shared_ptr<SpaceInterface>>> map;
  std::list<Coords> starting_points;
  size_t max_movable{0};
};
