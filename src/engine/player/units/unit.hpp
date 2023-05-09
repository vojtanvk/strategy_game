/**
 * @file unit.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../mapping/coords.hpp"
#include "unit_interface.hpp"

class Unit : public UnitInterface {
public:
  virtual ~Unit() = default;

  Unit(PlayerInterface &, const Coords &, const Blueprint &);

  bool can_build() const override;

  const Coords &get_position() const override;
  void set_position(const Coords &) override;

  PlayerInterface &get_owner() const override;

  const std::map<Materials, size_t> &get_harvest_list() const override;
  const std::vector<size_t> &get_build_list() const override;

  size_t get_points() const override;
  size_t get_id() const override;

private:
  PlayerInterface &owner;
  Coords position;

  size_t points;
  size_t id;

  std::vector<size_t> build_list;
  std::map<Materials, size_t> harvest_list;
};