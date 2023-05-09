/**
 * @file card_interface.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

class CardInterface;

#include "action_interface.hpp"

class CardInterface {
public:
  virtual ~CardInterface() = default;

  /**
   * @brief Resolve all actions on this card in given order
   *
   * @return true Success
   * @return false Rollback
   */
  virtual bool resolve() const = 0;

  /**
   * @brief Get list of Actions
   *
   * @return const std::vector<std::shared_ptr<ActionInterface>>&
   */
  virtual const std::vector<std::shared_ptr<ActionInterface>> &
  get_actions() const = 0;
};