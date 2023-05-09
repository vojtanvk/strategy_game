/**
 * @file worker.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "worker.hpp"

Worker::Worker(PlayerInterface &owner, const Coords &position,
               const Blueprint &blueprint)
    : Unit(owner, position, blueprint), move(blueprint.get_move()) {}

bool Worker::can_move() const { return true; }
bool Worker::can_harvest() const { return true; }
bool Worker::can_harvest_anywhere() const { return false; }

size_t Worker::get_move() const { return move; }

UnitType Worker::get_type() const { return UnitType::worker; }