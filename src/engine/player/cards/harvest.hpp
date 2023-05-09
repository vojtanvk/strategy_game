/**
 * @file harvest.hpp
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

class Harvest : public Action {
public:
  Harvest(size_t, GameInterface &);

  /**
   * @brief Lets Player choose Unit that can harvest and then harvests using it
   * or it's postition
   */
  bool resolve() override;
  ActionType get_type() const override;
};