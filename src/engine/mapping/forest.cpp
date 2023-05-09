/**
 * @file forest.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "forest.hpp"

Forest::Forest(const Coords &coords) : Space(coords) {}

bool Forest::walkable() const { return false; }

Materials Forest::get_material() const { return Materials::wood; }
Surface Forest::get_surface() const { return Surface::forest; }