/**
 * @file deck.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <algorithm>
#include <iostream>
#include <random>

#include "deck.hpp"

Deck::Deck(const std::vector<std::shared_ptr<CardInterface>> &cards)
    : discard_pile(cards) {
  shuffle();
}

void Deck::draw(size_t amount) {
  size_t to_draw{amount};
  if (amount > draw_pile.size()) {
    shuffle();
    to_draw = std::min(to_draw, draw_pile.size());
  }
  for (; to_draw > 0; --to_draw) {
    hand.push_back(draw_pile.front());
    draw_pile.pop_front();
  }

  // inform player that more cards cannot be drawn?
}

void Deck::shuffle() {
  auto rng = std::default_random_engine{};
  std::shuffle(discard_pile.begin(), discard_pile.end(), rng);
  for (auto c : discard_pile) {
    draw_pile.push_back(c);
  }
  discard_pile.clear();
}

const std::vector<std::shared_ptr<CardInterface>> &Deck::get_hand() const {
  return hand;
}

std::vector<std::shared_ptr<CardInterface>> &Deck::handler_hand() {
  return hand;
}

const std::list<std::shared_ptr<CardInterface>> &Deck::get_draw_pile() const {
  return draw_pile;
}

const std::vector<std::shared_ptr<CardInterface>> &
Deck::get_discard_pile() const {
  return discard_pile;
}

void Deck::add_draw(std::shared_ptr<CardInterface> card) {
  draw_pile.push_back(card);
}

void Deck::add_hand(std::shared_ptr<CardInterface> card) {
  hand.push_back(card);
}

void Deck::add_discard(std::shared_ptr<CardInterface> card) {
  discard_pile.push_back(card);
}

void Deck::discard_hand() {
  discard_pile.insert(discard_pile.end(), hand.begin(), hand.end());
  hand.clear();
}