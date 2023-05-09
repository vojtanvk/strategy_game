/**
 * @file action.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../../exceptions/exception.hpp"
#include "action.hpp"

Action::Action(size_t value, GameInterface &game_interface)
    : value(value), game_interface(game_interface) {}

GameInterface &Action::get_game_interface() { return game_interface; }

size_t Action::get_value() const { return value; }