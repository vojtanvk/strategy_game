/**
 * @file unit_factory.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../../exceptions/exception.hpp"
#include "unit_factory.hpp"

std::shared_ptr<UnitInterface> UnitFactory::build(PlayerInterface &owner,
                                                  const Blueprint &bp) const {
  switch (bp.get_type()) {
  case UnitType::building:
    return std::make_shared<Building>(owner, Coords{}, bp);
  case UnitType::worker:
    return std::make_shared<Worker>(owner, Coords{}, bp);
  default:
    throw IllegalArgumentException("Unexpected unit type");
  }
}