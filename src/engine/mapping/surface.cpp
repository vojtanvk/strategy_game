/**
 * @file surface.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../exceptions/exception.hpp"
#include "surface.hpp"

char to_char(Surface type) {
  switch (type) {
  case Surface::plains:
    return 'p';
  case Surface::forest:
    return 'f';
  case Surface::water:
    return 'w';
  case Surface::mountain:
    return 'm';
  default:
    throw IllegalArgumentException("Unknown surface type");
  }
}

std::string to_string(Surface type) {
  switch (type) {
  case Surface::plains:
    return "Plains";
  case Surface::forest:
    return "Forest";
  case Surface::water:
    return "Water";
  case Surface::mountain:
    return "Mountain";
  default:
    throw IllegalArgumentException("Unknown surface type");
  }
}

Surface char_to_surface(char type) {
  switch (type) {
  case 'p':
    return Surface::plains;
  case 'f':
    return Surface::forest;
  case 'w':
    return Surface::water;
  case 'm':
    return Surface::mountain;
  default:
    throw IllegalArgumentException("Unknown surface type");
  }
}

std::vector<Surface> list_surface() {
  return {Surface::plains, Surface::forest, Surface::mountain, Surface::water};
}