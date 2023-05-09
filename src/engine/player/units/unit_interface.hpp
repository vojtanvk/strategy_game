/**
 * @file unit_interface.hpp
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
#include <set>

class UnitInterface;

#include "blueprint.hpp"
#include "unit_type.hpp"

#include "../player_interface.hpp"

class UnitInterface {
public:
  virtual ~UnitInterface() = default;
  /**
   * @brief Returns whether chosen unit can move
   *
   * @return true
   * @return false
   */
  virtual bool can_move() const = 0;

  /**
   * @brief Return whether can harvest
   *
   * @return true
   * @return false
   */
  virtual bool can_harvest() const = 0;

  /**
   * @brief Returns whethercan harvest anywhere(doesn't care about
   * surroundings)
   *
   * @return true
   * @return false
   */
  virtual bool can_harvest_anywhere() const = 0;

  /**
   * @brief Returns whether can build
   *
   * @return true
   * @return false
   */
  virtual bool can_build() const = 0;

  /**
   * @brief Get Coordinates of unit
   *
   * @return const Coords&
   */
  virtual const Coords &get_position() const = 0;

  /**
   * @brief Set Coordinates
   *
   */
  virtual void set_position(const Coords &) = 0;

  /**
   * @brief Get the owner of unit
   *
   * @return PlayerInterface&
   */
  virtual PlayerInterface &get_owner() const = 0;

  /**
   * @brief Get the type object
   *
   * @return unit_type
   */
  virtual UnitType get_type() const = 0;

  /**
   * @brief Get units id for looking up in blueprints
   *
   * @return size_t
   */
  virtual size_t get_id() const = 0;

  /**
   * @brief Get list of harvest bonuses
   *
   * @return const std::map<Materials, size_t>&
   */
  virtual const std::map<Materials, size_t> &get_harvest_list() const = 0;

  /**
   * @brief Get ids of possible builds
   *
   * @return const std::vector<size_t>&
   */
  virtual const std::vector<size_t> &get_build_list() const = 0;

  /**
   * @brief Get move bonus
   *
   * @return size_t
   */
  virtual size_t get_move() const = 0;

  /**
   * @brief Get huw much points this unit is worth
   *
   * @return size_t
   */
  virtual size_t get_points() const = 0;
};