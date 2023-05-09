/**
 * @file action_interface.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

class ActionInterface;

#include "../../game_interface.hpp"
#include "action_type.hpp"

class ActionInterface {
public:
  virtual ~ActionInterface() = default;

  /**
   * @brief Get GameInterface reference
   *
   * @return GameInterface&
   */
  virtual GameInterface &get_game_interface() = 0;

  /**
   * @brief Through GameInterface and API tries to resolve current action
   *
   * @return true Success
   * @return false Rollback
   */
  virtual bool resolve() = 0;

  /**
   * @brief Get bonus of action
   *
   * @return size_t
   */
  virtual size_t get_value() const = 0;

  /**
   * @brief Get ActionType
   *
   * @return ActionType
   */
  virtual ActionType get_type() const = 0;
};