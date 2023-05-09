/**
 * @file draw.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../../exceptions/exception.hpp"
#include "draw.hpp"

Draw::Draw(size_t value, GameInterface &game_interface)
    : Action(value, game_interface) {}

bool Draw::resolve() {
  get_game_interface().get_active_player()->draw(get_value());
  return true;
}

ActionType Draw::get_type() const { return ActionType::draw; }