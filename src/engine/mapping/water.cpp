/**
 * @file water.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "water.hpp"

Water::Water(const Coords &coords) : Space(coords) {}

bool Water::walkable() const { return false; }

Materials Water::get_material() const { return Materials::none; }
Surface Water::get_surface() const { return Surface::water; }