/**
 * @file space_interface.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>

#include "../resources/materials.hpp"
#include "coords.hpp"
#include "surface.hpp"

class SpaceInterface;

#include "../player/units/unit_interface.hpp"

class SpaceInterface {
public:
  virtual ~SpaceInterface() = default;

  /**
   * @brief Is space walkable
   * Returns false if space is not walkable by default or has_unit
   * Slight differences in children (some check for unit)
   *
   * @return true
   * @return false
   */
  virtual bool walkable() const = 0;

  /**
   * @brief Get the materials of space
   * Returns material that this space produces or Materials::none if none
   *
   * @return Materials
   */
  virtual Materials get_material() const = 0;

  /**
   * @brief Set given unit pointer as occupant
   * @throws IllegalStateException If occupant present
   *
   */
  virtual void place_occupant(const std::shared_ptr<UnitInterface> &) = 0;

  /**
   * @brief Get the occupant as pointer to unit
   *
   * @return std::shared_ptr<UnitInterface>
   */
  virtual std::shared_ptr<UnitInterface> get_occupant() const = 0;

  /**
   * @brief Returns if occupant is set
   *
   * @return true
   * @return false
   */
  virtual bool is_occupied() const = 0;

  /**
   * @brief Removes occupant
   * @throws IllegalStateException If no occupant present
   */
  virtual void remove_occupant() = 0;

  /**
   * @brief Get the pos coordinates
   *
   * @return Coords
   */
  virtual Coords get_pos() const = 0;

  /**
   * @brief Get Surface
   *
   * @return Surface
   */
  virtual Surface get_surface() const = 0;
};
