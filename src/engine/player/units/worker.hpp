/**
 * @file worker.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "unit.hpp"

class Worker : public Unit {
public:
  Worker(PlayerInterface &, const Coords &, const Blueprint &);
  virtual ~Worker() = default;

  bool can_move() const override;
  bool can_harvest() const override;
  bool can_harvest_anywhere() const override;

  size_t get_move() const override;

  UnitType get_type() const override;

private:
  size_t move;
};