/**
 * @file movement.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "action.hpp"

class Movement : public Action {
public:
  Movement(size_t, GameInterface &);

  /**
   * @brief Lets Player choose Unit and then move around
   */
  bool resolve() override;
  ActionType get_type() const override;
};