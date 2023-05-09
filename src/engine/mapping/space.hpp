/**
 * @file space.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../player/units/unit_interface.hpp"
#include "space_interface.hpp"

class Space : public SpaceInterface {
public:
  Space(const Coords &);
  ~Space() = default;

  void place_occupant(const std::shared_ptr<UnitInterface> &) override;
  std::shared_ptr<UnitInterface> get_occupant() const override;
  bool is_occupied() const;
  void remove_occupant() override;
  Coords get_pos() const override;
  Surface get_surface() const override;

private:
  Coords coords;
  std::shared_ptr<UnitInterface> occupant{nullptr};
  Surface surf;
};
