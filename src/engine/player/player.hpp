/**
 * @file player.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <map>

#include "cards/deck.hpp"
#include "player_interface.hpp"

char to_char(PlayerType);
PlayerType char_to_player(char);

class Player : public PlayerInterface {
public:
  virtual ~Player() = default;

  /**
   * @brief Construct a new Player invalid. Needs more resources to be complete
   *
   */
  Player();

  void set_colour(Colour) override;
  void set_player_type(PlayerType) override;

  void add_unit(std::shared_ptr<UnitInterface>) override;

  void dock_player(std::shared_ptr<PlayerControllerInterface>) override;

  void dock_deck(const Deck &) override;

  std::shared_ptr<PlayerControllerInterface> get_api() const override;

  void start_turn() override;

  void end_turn() override;
  const std::vector<std::shared_ptr<UnitInterface>> &get_units() const override;
  std::vector<std::shared_ptr<UnitInterface>> &handle_units() override;
  void draw(size_t) override;
  const std::vector<std::shared_ptr<CardInterface>> &get_hand() const override;
  std::vector<std::shared_ptr<CardInterface>> &handler_hand() override;

  bool play_card(std::shared_ptr<CardInterface>) override;

  void add_material(Materials, size_t) override;
  void pay_cost(const std::map<Materials, size_t> &) override;

  const Deck &get_deck() const override;
  const std::map<Materials, size_t> &get_resources() const override;
  Colour get_colour() const override;

private:
  std::shared_ptr<PlayerControllerInterface> player_controller;
  std::vector<std::shared_ptr<UnitInterface>> units;
  size_t workers{0};
  Deck deck;
  Colour colour{Colour::black};
  PlayerType player_type;

  std::map<Materials, size_t> resources;
};