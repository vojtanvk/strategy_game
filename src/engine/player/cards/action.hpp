/**
 * @file action.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "action_interface.hpp"

class Action : public ActionInterface {
public:
  Action(size_t, GameInterface &);
  virtual ~Action() = default;
  GameInterface &get_game_interface() override;

  size_t get_value() const override;

private:
  size_t value;
  GameInterface &game_interface;
};