/**
 * @file building.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "building.hpp"

Building::Building(PlayerInterface &owner, const Coords &position,
                   const Blueprint &blueprint)
    : Unit(owner, position, blueprint),
      harvest(!blueprint.get_harvest_list().empty()) {}

bool Building::can_move() const { return false; }

bool Building::can_harvest() const { return harvest; }
bool Building::can_harvest_anywhere() const { return true; }

size_t Building::get_move() const { return 0; }

UnitType Building::get_type() const { return UnitType::building; }