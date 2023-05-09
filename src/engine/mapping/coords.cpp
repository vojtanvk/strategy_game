/**
 * @file coords.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../exceptions/exception.hpp"
#include "coords.hpp"

Coords Coords::move_up() const { return {x, y + 1}; }
Coords Coords::move_down() const { return {x, y - 1}; }
Coords Coords::move_left() const { return {x - 1, y}; }
Coords Coords::move_right() const { return {x + 1, y}; }

Coords Coords::move(Directions dir) const {
  switch (dir) {
  case Coords::Directions::up:
    return move_up();
  case Coords::Directions::down:
    return move_down();
  case Coords::Directions::left:
    return move_left();
  case Coords::Directions::right:
    return move_right();
  default:
    throw IllegalArgumentException("Unknown direction");
  }
}

Coords::Directions Coords::get_direction_to(const Coords &finish) const {
  if (finish.x == x + 1 && finish.y == y) {
    return Coords::Directions::right;
  } else if (finish.x + 1 == x && finish.y == y) {
    return Coords::Directions::left;
  } else if (finish.y == y + 1) {
    return Coords::Directions::up;
  } else if (finish.y + 1 == y) {
    return Coords::Directions::down;
  } else {
    throw IllegalArgumentException("Unknown direction");
  }
}

bool Coords::operator<(const Coords &other) const {
  return x < other.x && y < other.y;
}

bool Coords::operator==(const Coords &other) const {
  return x == other.x && y == other.y;
}

std::ostream &operator<<(std::ostream &out, const Coords &coords) {
  out << "[" << coords.x << "," << coords.y << "]";
  return out;
}

std::string to_string(Coords::Directions dir) {
  switch (dir) {
  case Coords::Directions::down:
    return "down";
  case Coords::Directions::left:
    return "left";
  case Coords::Directions::right:
    return "right";
  case Coords::Directions::up:
    return "up";
  default:
    throw IllegalArgumentException("Unknown direction");
  }
}