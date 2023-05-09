/**
 * @file map.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <sstream>

#include "../../exceptions/exception.hpp"
#include "map.hpp"

Map::Map(const std::vector<std::vector<std::shared_ptr<SpaceInterface>>> &map,
         const std::list<Coords> &starting_points)
    : map(map), starting_points(starting_points), max_movable(0) {

  std::for_each(map.begin(), map.end(), [&](const auto &line) {
    this->max_movable +=
        std::count_if(line.begin(), line.end(),
                      [](const auto &sp) { return sp->walkable(); });
  });
}

Coords Map::get_dimensions() const {
  if (map.empty()) {
    return {0, 0};
  }
  return {map.begin()->size(), map.size()};
}

std::vector<Materials> Map::harvest(const Coords &where) const {
  std::vector<Materials> mats;
  auto surr = surroundings(where);
  for (const auto &space : surr) {
    auto mat = space->get_material();
    if (mat != Materials::none) {
      mats.push_back(mat);
    }
  }
  return mats;
}
std::vector<Coords> Map::movable_area(const Coords &where,
                                      size_t movement) const {
  std::vector<Coords> out{where};

  movement = std::min(movement, max_movable);
  if (movement == 0) {
    return out;
  }
  if (movement == 1) {
    return walkable_surroundings(where);
  }
  auto surr = walkable_surroundings(where);
  for (const auto &s : surr) {
    auto area = movable_area(s, movement - 1);
    out.insert(out.end(), area.begin(), area.end());
    out.push_back(s);
  }
  return out;
}

std::vector<std::shared_ptr<SpaceInterface>>
Map::surroundings(const Coords &where) const {
  std::vector<std::shared_ptr<SpaceInterface>> out;
  std::set<Coords::Directions> dirs{
      Coords::Directions::up, Coords::Directions::down,
      Coords::Directions::left, Coords::Directions::right};
  Coords mv;
  for (auto dir : dirs) {
    mv = where.move(dir);
    if (mv < get_dimensions()) {
      out.push_back(get_space(mv));
    }
  }
  return out;
}

std::vector<Coords> Map::walkable_surroundings(const Coords &where) const {
  std::vector<Coords> out;
  auto surr = surroundings(where);
  for (const auto &space : surr) {
    if (space->walkable()) {
      out.push_back(space->get_pos());
    }
  }
  return out;
}

std::shared_ptr<SpaceInterface> Map::get_space(const Coords &where) const {
  if (!(where < get_dimensions())) {
    std::stringstream ss;
    ss << "Position [" << where.x << "," << where.y << "]"
       << " out of bounds";
    throw IllegalArgumentException(ss.str());
  }
  return map[where.y][where.x];
}

const std::vector<std::vector<std::shared_ptr<SpaceInterface>>> &
Map::get_map() const {
  return map;
}

Coords Map::get_starting_point() {
  if (starting_points.empty()) {
    throw IllegalStateException("No start point available");
  }
  Coords out{starting_points.front()};
  starting_points.pop_front();
  return out;
}

size_t Map::get_max_movable() const { return max_movable; }
size_t Map::available_starts() const { return starting_points.size(); }
const std::list<Coords> &Map::get_starting_points() const {
  return starting_points;
}