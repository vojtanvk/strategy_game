/**
 * @file card.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>
#include <vector>

#include "action_interface.hpp"
#include "card_interface.hpp"

class Card : public CardInterface {
public:
  /**
   * @brief Construct a Card object with given Actions
   *
   */
  Card(const std::vector<std::shared_ptr<ActionInterface>> &);
  Card(const CardInterface &);
  virtual ~Card() = default;

  bool resolve() const;

  const std::vector<std::shared_ptr<ActionInterface>> &
  get_actions() const override;

private:
  std::vector<std::shared_ptr<ActionInterface>> actions;
};