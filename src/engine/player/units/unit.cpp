/**
 * @file unit.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "unit.hpp"

Unit::Unit(PlayerInterface &owner, const Coords &position,
           const Blueprint &blueprint)
    : owner(owner), position(position), points(blueprint.get_points()),
      id(blueprint.get_id()), build_list(blueprint.get_build_list()),
      harvest_list(blueprint.get_harvest_list()) {}

bool Unit::can_build() const { return !build_list.empty(); }

const Coords &Unit::get_position() const { return position; }

void Unit::set_position(const Coords &in_pos) { position = in_pos; }

PlayerInterface &Unit::get_owner() const { return owner; }

const std::map<Materials, size_t> &Unit::get_harvest_list() const {
  return harvest_list;
}
const std::vector<size_t> &Unit::get_build_list() const { return build_list; }

size_t Unit::get_points() const { return points; }
size_t Unit::get_id() const { return id; }