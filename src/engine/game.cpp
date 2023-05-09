/**
 * @file game.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>

#include "../exceptions/exception.hpp"
#include "game.hpp"
#include "player/cards/card.hpp"
#include "player/units/unit_factory.hpp"

std::shared_ptr<PlayerInterface> Game::start() {

  if (!map || players.empty()) {
    throw IllegalStateException("Game is missing map or players");
  }
  set_active_player(0);
  get_active_player()->start_turn();
  return run();
}

std::shared_ptr<PlayerInterface> Game::run() {

  while (true) {
    std::shared_ptr<CardInterface> chosen_card;
    auto &active_player = *get_active_player();

    while (true) {
      auto val = active_player.get_api()->select_card(
          active_player.get_deck(), active_player, chosen_card);
      if (val == -1) {
        return nullptr;
      } else if (val == 0) {
        active_player.end_turn();
        break;
      } else {
        if (active_player.play_card(chosen_card)) {
          action_stack.clear();
        } else {
          action_stack.rollback();
          continue;
        }
        if (active_player.get_hand().empty()) {
          active_player.end_turn();
          break;
        }
      }
    }

    if (std::any_of(win_conditions.begin(), win_conditions.end(),
                    [&](const WinCon &win_con) {
                      return win_con.resolve(active_player);
                    })) {
      return get_active_player();
    }

    size_t next_player = get_active_player_index() + 1;
    if (next_player == get_players().size()) {
      set_active_player(0);
    } else {
      set_active_player(next_player);
    }
    get_active_player()->start_turn();
  }
  throw IllegalStateException("Unexpectedly exited game cycle");
}

void Game::add_player_start(std::shared_ptr<PlayerInterface> player) {
  player->dock_deck(starting_deck);
  std::for_each(
      starting_units.begin(), starting_units.end(), [&](const auto &starter) {
        for (size_t i = 0; i < starter.second; ++i) {
          player->add_unit(UnitFactory().build(*player, starter.first));
        }
      });

  auto u_count{player->get_units().size()};
  Coords starting_point{map->get_starting_point()};
  size_t area_size{u_count / 4};
  auto area{map->movable_area(starting_point, area_size)};

  while (area.size() < u_count) {
    area_size++;
    area = map->movable_area(starting_point, area_size);
  }

  for (size_t i = 0; i < u_count; ++i) {
    player->get_units()[i]->set_position(area[i]);
  }

  add_player(player);
}

void Game::add_player(std::shared_ptr<PlayerInterface> player) {
  players.push_back(player);
  for (const auto &u : players.back()->get_units()) {
    map->get_space(u->get_position())->place_occupant(u);
  }
}

size_t Game::dock_map(std::shared_ptr<MapInterface> in_map) {
  size_t starting_units_count{0};
  std::for_each(
      starting_units.begin(), starting_units.end(),
      [&](const auto &starter) { starting_units_count += starter.second; });
  if (starting_units_count * in_map->available_starts() >
      in_map->get_max_movable()) {
    throw IllegalArgumentException("This map is unusable with current config");
  }

  map = in_map;
  return map->available_starts();
}

void Game::dock_unit_bps(const std::map<size_t, Blueprint> &unit_bps) {
  bp_list = unit_bps;
}

void Game::add_unit(std::shared_ptr<UnitInterface> unit) {
  unit->get_owner().add_unit(unit);
  map->get_space(unit->get_position())->place_occupant(unit);
}

void Game::add_start_card(const CardInterface &card) {
  starting_deck.add_discard(std::make_shared<Card>(card));
}

void Game::add_blueprint(const Blueprint &bp) { bp_list[bp.get_id()] = bp; }
void Game::add_starting_unit(const Blueprint &bp, size_t count) {
  starting_units.push_back({bp, count});
}
void Game::add_win_con(const WinCon &win_con) {
  win_conditions.push_back(win_con);
}

std::shared_ptr<PlayerInterface> Game::get_active_player() const {
  return players[active_player_index];
}

std::shared_ptr<MapInterface> Game::get_map() const { return map; }

const std::vector<std::shared_ptr<PlayerInterface>> &Game::get_players() const {
  return players;
}

size_t Game::get_active_player_index() const { return active_player_index; }
void Game::set_active_player(size_t index) {
  if (index >= players.size()) {
    throw IllegalArgumentException("Player index too big");
  }
  active_player_index = index;
}

ActionStack &Game::handler_action_stack() { return action_stack; }

const Blueprint &Game::get_blueprint(size_t id) const {
  if (bp_list.count(id)) {
    return bp_list.at(id);
  }
  throw IllegalArgumentException("Unknown unit id");
}

std::vector<size_t> Game::get_unit_ids() const {
  std::vector<size_t> out;
  std::for_each(bp_list.begin(), bp_list.end(),
                [&](const auto &key_value) { out.push_back(key_value.first); });
  return out;
}

const std::map<size_t, Blueprint> &Game::get_blueprints() const {
  return bp_list;
}

const std::vector<WinCon> &Game::get_win_cons() const { return win_conditions; }

void Game::ready_check() const {
  if (!map || map->get_map().empty()) {
    throw IllegalStateException("Missing map");
  }

  if (bp_list.empty()) {
    throw IllegalStateException("No units present");
  }

  if (players.empty() ||
      std::any_of(players.begin(), players.end(),
                  [](const std::shared_ptr<PlayerInterface> &p) {
                    const Deck &d{p->get_deck()};
                    return !p->get_api() || p->get_units().size() == 0 ||
                           (d.get_discard_pile().empty() &&
                            d.get_draw_pile().empty() && d.get_hand().empty());
                  })) {
    throw IllegalStateException("Players are not ready");
  }
}