/**
 * @file plains.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "plains.hpp"

Plains::Plains(const Coords &coords) : Space(coords) {}

bool Plains::walkable() const { return !is_occupied(); }

Materials Plains::get_material() const { return Materials::none; }

Surface Plains::get_surface() const { return Surface::plains; }