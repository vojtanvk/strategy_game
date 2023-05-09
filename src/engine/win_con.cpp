/**
 * @file win_con.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "win_con.hpp"

bool WinCon::resolve(const PlayerInterface &player) const {
  const auto &p_resources{player.get_resources()};

  if (std::any_of(materials.begin(), materials.end(), [&](const auto &mat) {
        return p_resources.count(mat.first) &&
               p_resources.at(mat.first) < mat.second;
      })) {
    return false;
  }

  const auto &p_units{player.get_units()};
  size_t p_pts{0};
  std::for_each(p_units.begin(), p_units.end(),
                [&](const auto &unit) { p_pts += unit->get_points(); });

  if (p_pts < points) {
    return false;
  }

  if (p_units.size() < unit_count) {
    return false;
  }

  return true;
}

size_t WinCon::get_unit_count() const { return unit_count; }
const std::map<Materials, size_t> &WinCon::get_materials() const {
  return materials;
}
size_t WinCon::get_points() const { return points; }

void WinCon::set_unit_count(size_t in_unit_count) {
  unit_count = in_unit_count;
}
void WinCon::set_materials(const std::map<Materials, size_t> &in_materials) {
  materials = in_materials;
}
void WinCon::set_points(size_t in_points) { points = in_points; }