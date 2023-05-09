/**
 * @file blueprint.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "blueprint.hpp"

Blueprint::Blueprint(size_t id) : id(id) {}

Blueprint::Blueprint(size_t id, UnitType type,
                     const std::map<Materials, size_t> &cost)
    : id(id), type(type), cost(cost) {}

size_t Blueprint::get_id() const { return id; }
void Blueprint::set_id(size_t in_id) { id = in_id; }

UnitType Blueprint::get_type() const { return type; }
void Blueprint::set_type(UnitType in_type) { type = in_type; }

const std::map<Materials, size_t> &Blueprint::get_cost() const { return cost; }
void Blueprint::set_cost(const std::map<Materials, size_t> &in_cost) {
  cost = in_cost;
}

const std::map<Materials, size_t> &Blueprint::get_harvest_list() const {
  return harvest_list;
}
void Blueprint::set_harvest_list(
    const std::map<Materials, size_t> &in_harvest_list) {
  harvest_list = in_harvest_list;
}

const std::vector<size_t> &Blueprint::get_build_list() const {
  return build_list;
}
void Blueprint::set_build_list(const std::vector<size_t> &in_build_list) {
  build_list = in_build_list;
}
void Blueprint::add_build_list(const size_t &n_build) {
  build_list.push_back(n_build);
}

size_t Blueprint::get_move() const { return move; }
void Blueprint::set_move(size_t in_move) { move = in_move; }

size_t Blueprint::get_points() const { return points; }
void Blueprint::set_points(size_t in_points) { points = in_points; }