/**
 * @file deck.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <list>
#include <memory>
#include <vector>

class Deck;

#include "card_interface.hpp"

class Deck {
public:
  /**
   * @brief Construct an empty Deck
   *
   */
  Deck() = default;

  /**
   * @brief Construct a Deck with given Cards
   *
   */
  Deck(const std::vector<std::shared_ptr<CardInterface>> &);

  /**
   * @brief Draw n Cards
   * Move amount Cards from draw_pile to hand
   * If draw_pile is empty -> shuffle
   *
   */
  void draw(size_t);

  /**
   * @brief Shuffle discard pile to draw pile
   * Creates rng and uses shuffle on discard pile
   *
   */
  void shuffle();

  /**
   * @brief Get list of Cards in hand
   *
   * @return const std::vector<std::shared_ptr<CardInterface>>&
   */
  const std::vector<std::shared_ptr<CardInterface>> &get_hand() const;

  /**
   * @brief Get handler to Cards in hand for manipulation
   *
   * @return std::vector<std::shared_ptr<CardInterface>>&
   */
  std::vector<std::shared_ptr<CardInterface>> &handler_hand();

  /**
   * @brief Get list of Cards in draw pile
   *
   * @return const std::list<std::shared_ptr<CardInterface>>&
   */
  const std::list<std::shared_ptr<CardInterface>> &get_draw_pile() const;

  /**
   * @brief Get list of Cards in discard pile
   *
   * @return const std::vector<std::shared_ptr<CardInterface>>&
   */
  const std::vector<std::shared_ptr<CardInterface>> &get_discard_pile() const;

  /**
   * @brief Adds Card to draw pile
   *
   */
  void add_draw(std::shared_ptr<CardInterface>);

  /**
   * @brief Adds Card to hand
   *
   */
  void add_hand(std::shared_ptr<CardInterface>);

  /**
   * @brief Adds Card to discard pile
   *
   */
  void add_discard(std::shared_ptr<CardInterface>);

  /**
   * @brief Discards all Cards in hand (moves them from hand to discard pile)
   *
   */
  void discard_hand();

private:
  /**
   * @brief Using list fo easy pushing to back and extracting from front
   *
   */
  std::list<std::shared_ptr<CardInterface>> draw_pile;
  std::vector<std::shared_ptr<CardInterface>> hand;
  std::vector<std::shared_ptr<CardInterface>> discard_pile;
};