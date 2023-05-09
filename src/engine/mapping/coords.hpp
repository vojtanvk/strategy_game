/**
 * @file coords.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cstddef>
#include <iostream>

/**
 * @brief Coords(x,y)
 *
 */
struct Coords {

  /**
   * @brief Possible 2D directions
   *
   */
  enum class Directions { up, down, left, right };

  /**
   * @brief Returns coordinates above this
   *
   * @return Coords
   */
  Coords move_up() const;

  /**
   * @brief Returns coordinates below this
   *
   * @return Coords
   */
  Coords move_down() const;

  /**
   * @brief Returns coordinates left of this
   *
   * @return Coords
   */
  Coords move_left() const;

  /**
   * @brief Returns coordinates right of this
   *
   * @return Coords
   */
  Coords move_right() const;

  /**
   * @brief Returns coordinates in given direction
   *
   * @param where to move
   * @return Coords
   * @throws IllegalArgumentException If unknown Direction is given
   */
  Coords move(Directions where) const;

  /**
   * @brief Get the direction to neighbour
   *
   * @param to_where Where you want to end
   * @return Directions
   * @throws IllegalArgumentException If coordinates aren't neigbours
   */
  Directions get_direction_to(const Coords &to_where) const;

  /**
   * @brief Returns if given coordinates are bigger in both x and y
   *
   * @param other To whom compare
   * @return true
   * @return false
   */
  bool operator<(const Coords &other) const;

  /**
   * @brief Returns if given coordinates are equal
   *
   * @param other To whom comapre
   * @return true
   * @return false
   */
  bool operator==(const Coords &other) const;

  size_t x;
  size_t y;
};

/**
 * @brief Names given Direction
 *
 * @param direction Direction to name
 * @return std::string Name of Direction
 * @throws IllegalArgumentException If unknown Directions is given
 */
std::string to_string(Coords::Directions direction);