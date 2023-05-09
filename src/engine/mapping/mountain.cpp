/**
 * @file mountain.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "mountain.hpp"

Mountain::Mountain(const Coords &coords) : Space(coords) {}

bool Mountain::walkable() const { return false; }

Materials Mountain::get_material() const { return Materials::stone; }
Surface Mountain::get_surface() const { return Surface::mountain; }