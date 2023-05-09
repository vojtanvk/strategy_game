/**
 * @file card.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "card.hpp"

#include <iostream>

Card::Card(const std::vector<std::shared_ptr<ActionInterface>> &actions)
    : actions(actions) {}
Card::Card(const CardInterface &card) : actions(card.get_actions()) {}

bool Card::resolve() const {
  for (const auto &a : actions) {
    if (!a->resolve()) {
      return false;
    }
  }
  return true;
}

const std::vector<std::shared_ptr<ActionInterface>> &Card::get_actions() const {
  return actions;
}