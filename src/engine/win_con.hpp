/**
 * @file win_con.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <cstdlib>
#include <map>

struct WinCon;

#include "player/player_interface.hpp"

enum class WinConType { points, units, material };

struct WinCon {
  /**
   * @brief Check if given player completed all conditions
   *
   * @return true Completed all
   * @return false One or more remain incompleted
   */
  virtual bool resolve(const PlayerInterface &) const;

  /**
   * @brief Get size of army condition
   *
   * @return size_t
   */
  size_t get_unit_count() const;

  /**
   * @brief Get material storage condition
   *
   * @return const std::map<Materials, size_t>&
   */
  const std::map<Materials, size_t> &get_materials() const;

  /**
   * @brief Get amount of points condition
   *
   * @return size_t
   */
  size_t get_points() const;

  /**
   * @brief Set size of army condition
   *
   */
  void set_unit_count(size_t);

  /**
   * @brief Set material storage condition
   *
   */
  void set_materials(const std::map<Materials, size_t> &);

  /**
   * @brief Set amount of points condition
   *
   */
  void set_points(size_t);

private:
  /**
   * @brief Army size condition
   *
   */
  size_t unit_count{0};

  /**
   * @brief Material storage condition
   *
   */
  std::map<Materials, size_t> materials;

  /**
   * @brief Amount of points condition
   *
   */
  size_t points{0};
};