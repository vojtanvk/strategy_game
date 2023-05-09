/**
 * @file game.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "game_interface.hpp"
#include "win_con.hpp"

#include <iostream>

/**
 * @brief Main class of the Game. Holds all information considering game state
 * (players, units, win cons, map...)
 *
 */
class Game : public GameInterface {
public:
  /**
   * @brief Construct default Game. Invalid for use, in need of docking
   * additional sources
   *
   */
  Game() = default;
  /**
   * @brief Destroys Game. Since all in-game components are using stl and no
   * smart-pointer-cycles present, default shoud be enough
   *
   */
  virtual ~Game() {}

  std::shared_ptr<PlayerInterface> start() override;

  std::shared_ptr<PlayerInterface> run() override;

  void add_player_start(std::shared_ptr<PlayerInterface>) override;
  void add_player(std::shared_ptr<PlayerInterface>) override;

  size_t dock_map(std::shared_ptr<MapInterface>) override;

  void dock_unit_bps(const std::map<size_t, Blueprint> &) override;

  void add_unit(std::shared_ptr<UnitInterface>) override;

  void add_start_card(const CardInterface &) override;
  void add_blueprint(const Blueprint &) override;
  void add_starting_unit(const Blueprint &, size_t) override;
  void add_win_con(const WinCon &) override;

  const std::vector<std::shared_ptr<PlayerInterface>> &
  get_players() const override;

  std::shared_ptr<MapInterface> get_map() const override;

  std::shared_ptr<PlayerInterface> get_active_player() const override;

  size_t get_active_player_index() const override;
  void set_active_player(size_t) override;

  ActionStack &handler_action_stack();

  const Blueprint &get_blueprint(size_t) const override;
  std::vector<size_t> get_unit_ids() const override;
  const std::map<size_t, Blueprint> &get_blueprints() const override;

  const std::vector<WinCon> &get_win_cons() const override;

  void ready_check() const override;

private:
  /**
   * @brief Available unit blueprints mapped by id
   *
   */
  std::map<size_t, Blueprint> bp_list;
  /**
   * @brief Units given to players at game's start
   *
   */
  std::vector<std::pair<Blueprint, size_t>> starting_units;
  /**
   * @brief Players active in current game
   *
   */
  std::vector<std::shared_ptr<PlayerInterface>> players;
  /**
   * @brief Deck given to players at game's start
   *
   */
  Deck starting_deck;
  /**
   * @brief Current game's map
   *
   */
  std::shared_ptr<MapInterface> map;
  /**
   * @brief Index of player on turn
   *
   */
  size_t active_player_index{0};
  /**
   * @brief Stack of played actions on current card ready to rollback if needed
   *
   */
  ActionStack action_stack{};
  /**
   * @brief Conditions necessary for winning the game
   *
   */
  std::vector<WinCon> win_conditions;
};