/**
 * @file build.hpp
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

class Build : public Action {
public:
  Build(size_t, GameInterface &);

  /**
   * @brief Let's Player chose Unit that can build and then build new Unit in
   * its neigbourhood
   */
  bool resolve() override;
  ActionType get_type() const override;
};