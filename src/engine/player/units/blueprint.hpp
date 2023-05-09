/**
 * @file blueprint.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <map>
#include <vector>

#include "../../resources/materials.hpp"
#include "unit_type.hpp"

/**
 * @brief Blueprint for unit containing all game relevant information
 */
struct Blueprint {
public:
  Blueprint() = default;
  /**
   * @brief Construct Blueprint with given id
   * @param id
   */
  Blueprint(size_t id);

  /**
   * @brief Construct Blueprint with given, id, type and cost
   *
   * @param id
   * @param type
   * @param cost
   */
  Blueprint(size_t id, UnitType type, const std::map<Materials, size_t> &cost);

  /**
   * @brief Get the id
   *
   * @return size_t
   */
  size_t get_id() const;

  /**
   * @brief Set the id object
   *
   * @param id
   */
  void set_id(size_t id);

  /**
   * @brief Get the type object
   *
   * @return UnitType
   */
  UnitType get_type() const;

  /**
   * @brief Set the type object
   *
   * @param type
   */
  void set_type(UnitType type);

  /**
   * @brief Get the Material price of Unit
   *
   * @return const std::map<Materials, size_t>&
   */
  const std::map<Materials, size_t> &get_cost() const;

  /**
   * @brief Set the cost
   *
   * @param materials
   */
  void set_cost(const std::map<Materials, size_t> &materials);

  /**
   * @brief Get bonus to harvests mapped by Material
   *
   * @return const std::map<Materials, size_t>&
   */
  const std::map<Materials, size_t> &get_harvest_list() const;

  /**
   * @brief Set bonus to harvests mapped by Material
   *
   * @param harves_list
   */
  void set_harvest_list(const std::map<Materials, size_t> &harves_list);

  /**
   * @brief Get list of possible builds
   *
   * @return const std::vector<size_t>&
   */
  const std::vector<size_t> &get_build_list() const;

  /**
   * @brief Set list of possible builds
   *
   * @param build_list
   */
  void set_build_list(const std::vector<size_t> &build_list);

  /**
   * @brief Add id to possible builds
   *
   */
  void add_build_list(const size_t &);

  /**
   * @brief Get move bonus
   *
   * @return size_t
   */
  size_t get_move() const;

  /**
   * @brief Set move bonus
   *
   */
  void set_move(size_t);

  /**
   * @brief Get points worth
   *
   * @return size_t
   */
  size_t get_points() const;

  /**
   * @brief Set points worth
   *
   */
  void set_points(size_t);

private:
  size_t id{0};
  UnitType type;
  std::map<Materials, size_t> cost;

  std::map<Materials, size_t> harvest_list;
  std::vector<size_t> build_list;
  size_t move{0};

  size_t points{0};
};