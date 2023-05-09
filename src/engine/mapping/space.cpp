/**
 * @file space.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../exceptions/exception.hpp"
#include <iostream>

#include "space.hpp"

Space::Space(const Coords &coords) : coords(coords) {}

void Space::place_occupant(const std::shared_ptr<UnitInterface> &in_occupant) {
  if (occupant) {
    throw IllegalStateException("Occupant already present");
  }
  occupant = in_occupant;
}
std::shared_ptr<UnitInterface> Space::get_occupant() const { return occupant; }
bool Space::is_occupied() const { return occupant != nullptr; }
void Space::remove_occupant() {
  if (!occupant) {
    throw IllegalStateException("No occupant present");
  }
  occupant = nullptr;
}
Coords Space::get_pos() const { return coords; }
Surface Space::get_surface() const { return Surface::undefined; }