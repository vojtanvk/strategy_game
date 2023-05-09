/**
 * @file player.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../exceptions/exception.hpp"
#include "player.hpp"

Player::Player() : resources({{Materials::stone, 0}, {Materials::wood, 0}}) {}

void Player::set_colour(Colour in_colour) { colour = in_colour; }

void Player::set_player_type(PlayerType type) { player_type = type; }

void Player::add_unit(std::shared_ptr<UnitInterface> unit) {
  if (unit->get_type() == UnitType::worker) {
    ++workers;
  }
  units.push_back(unit);
}

void Player::dock_player(std::shared_ptr<PlayerControllerInterface> in_api) {
  player_controller = in_api;
}

void Player::dock_deck(const Deck &in_deck) { deck = in_deck; }

std::shared_ptr<PlayerControllerInterface> Player::get_api() const {
  return player_controller;
}

void Player::start_turn() { draw(workers); }
void Player::end_turn() { deck.discard_hand(); }

const std::vector<std::shared_ptr<UnitInterface>> &Player::get_units() const {
  return units;
}
std::vector<std::shared_ptr<UnitInterface>> &Player::handle_units() {
  return units;
}

void Player::draw(size_t amount) { deck.draw(amount); }
const std::vector<std::shared_ptr<CardInterface>> &Player::get_hand() const {
  return deck.get_hand();
}

std::vector<std::shared_ptr<CardInterface>> &Player::handler_hand() {
  return deck.handler_hand();
}

// TODO use reference
bool Player::play_card(std::shared_ptr<CardInterface> card) {
  auto result = card->resolve();
  if (result) {
    // TODO test this
    // auto res = std::find(hand.begin(), hand.end(), card);

    // if (res == hand.end())
    //   return false;
    // deck.add_discard(card);
    // hand.erase(res);
    // return true;
    for (auto it = deck.handler_hand().begin(); it != deck.handler_hand().end();
         ++it) {
      if (*it == card) {
        deck.add_discard(card);
        deck.handler_hand().erase(it);
        return true;
      }
    }
    throw IllegalArgumentException("Playing unknown card");
  }
  return false;
}

void Player::add_material(Materials material, size_t amount) {
  resources[material] += amount;
}

void Player::pay_cost(const std::map<Materials, size_t> &cost) {
  for (const auto &i : cost) {
    if (resources[i.first] < i.second) {
      throw IllegalArgumentException("Insufficient resources");
    }
  }
  for (const auto &i : cost) {
    resources[i.first] -= i.second;
  }
}

const Deck &Player::get_deck() const { return deck; }

const std::map<Materials, size_t> &Player::get_resources() const {
  return resources;
}

Colour Player::get_colour() const { return colour; }

char to_char(PlayerType type) {
  switch (type) {
  case PlayerType::human:
    return 'h';
  case PlayerType::ai:
    return 'a';
  default:
    throw IllegalArgumentException("Unexpected player type");
  }
}

PlayerType char_to_player(char);