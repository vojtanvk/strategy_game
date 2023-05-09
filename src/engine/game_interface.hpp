/**
 * @file game_interface.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>
#include <vector>

struct GameInterface;

#include "mapping/map_interface.hpp"
#include "player/cards/card_interface.hpp"
#include "player/cards/rollback.hpp"
#include "player/player_interface.hpp"
#include "player/units/blueprint.hpp"
#include "win_con.hpp"
/**
 * @brief Main Game Interface that specifies all methods available for calling
 * from outside sources
 *
 */
struct GameInterface {
  virtual ~GameInterface() {}

  /**
   * @brief Set up game before starting and calls run method
   *
   * @return std::shared_ptr<PlayerInterface> pointer to winner or nullptr if
   * game not finisheds
   */
  virtual std::shared_ptr<PlayerInterface> start() = 0;

  /**
   * @brief Cycle through connected players and lets them call on api to choose
   * card
   *
   * @return std::shared_ptr<PlayerInterface> pointer to winner or nullptr if
   * game not finished
   */
  virtual std::shared_ptr<PlayerInterface> run() = 0;

  /**
   * @brief Add player before starting game, prepare him according to given
   * configurtation and place his units on map
   *
   */
  virtual void add_player_start(std::shared_ptr<PlayerInterface>) = 0;

  /**
   * @brief Add player into game in progress (loaded) and place his units on map
   *
   */
  virtual void add_player(std::shared_ptr<PlayerInterface>) = 0;

  /**
   * @brief Dock map into game
   *
   * @return size_t max available starting points (player count)
   */
  virtual size_t dock_map(std::shared_ptr<MapInterface>) = 0;

  /**
   * @brief Dock available unit blueprints mapped by their id
   *
   */
  virtual void dock_unit_bps(const std::map<size_t, Blueprint> &) = 0;

  /**
   * @brief Add new unit -> insert it to players army and place it on map
   *
   */
  virtual void add_unit(std::shared_ptr<UnitInterface>) = 0;

  /**
   * @brief Add card to starting deck (deck will be given to player in
   * add_player_start method)
   *
   */
  virtual void add_start_card(const CardInterface &) = 0;

  /**
   * @brief Add available unit
   *
   */
  virtual void add_blueprint(const Blueprint &) = 0;

  /**
   * @brief Add unit to starting units (units will be given in add_player_start
   * method)
   *
   */
  virtual void add_starting_unit(const Blueprint &, size_t) = 0;

  /**
   * @brief Add win condition
   *
   */
  virtual void add_win_con(const WinCon &) = 0;

  /**
   * @brief Get list of players added to the game
   *
   * @return const std::vector<std::shared_ptr<PlayerInterface>>&
   */
  virtual const std::vector<std::shared_ptr<PlayerInterface>> &
  get_players() const = 0;

  /**
   * @brief Get pointer to map
   *
   * @return std::shared_ptr<MapInterface>
   */
  virtual std::shared_ptr<MapInterface> get_map() const = 0;

  /**
   * @brief Get pointer to player on turn
   *
   * @return std::shared_ptr<PlayerInterface>
   */
  virtual std::shared_ptr<PlayerInterface> get_active_player() const = 0;

  /**
   * @brief Get index of active player
   *
   * @return size_t player index (0 <= index < get_players().size())
   */
  virtual size_t get_active_player_index() const = 0;

  /**
   * @brief Get vector of available units by id
   *
   * @return std::vector<size_t>
   */
  virtual std::vector<size_t> get_unit_ids() const = 0;

  /**
   * @brief Set active player index
   *
   * @throws IllegalArgumentException If index is out of range
   *
   */
  virtual void set_active_player(size_t) = 0;

  /**
   * @brief Get blueprint by given id
   *
   * @return const Blueprint& reference to unit's blueprint
   * @throws IllegalArgumentException If given id is not present in available
   * units
   */
  virtual const Blueprint &get_blueprint(size_t) const = 0;

  /**
   * @brief Get available Blueprints mapped by their id
   *
   * @return const std::map<size_t, Blueprint>&
   */
  virtual const std::map<size_t, Blueprint> &get_blueprints() const = 0;

  /**
   * @brief Get reference to vector of win conditions
   *
   * @return const std::vector<WinCon>&
   */
  virtual const std::vector<WinCon> &get_win_cons() const = 0;

  /**
   * @brief Get handler to action stack (for action rollback purpouses)
   *
   * @return ActionStack&
   */
  virtual ActionStack &handler_action_stack() = 0;

  /**
   * @brief Check if game is in valid state to begi playing
   *
   * @throws IllegalStateException If map is not present or empty
   * @throws IllegalStateException If no units are available
   * @throws IllegalStateException If players are not ready (not connected,
   * missing deck or units)
   */
  virtual void ready_check() const = 0;
};