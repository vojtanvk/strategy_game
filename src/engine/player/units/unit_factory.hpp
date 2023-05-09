/**
 * @file unit_factory.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>

#include "unit_interface.hpp"
#include "units.hpp"

struct UnitFactory {
  std::shared_ptr<UnitInterface> build(PlayerInterface &,
                                       const Blueprint &) const;
};