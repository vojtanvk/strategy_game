/**
 * @file draw.hpp
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

class Draw : public Action {
public:
  Draw(size_t, GameInterface &);
  /**
   * @brief Lets Player draw Cards
   *
   * @return true
   */
  bool resolve() override;
  ActionType get_type() const override;
};