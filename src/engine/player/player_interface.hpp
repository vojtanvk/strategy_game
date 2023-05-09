/**
 * @file player_interface.hpp
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
#include <memory>
#include <vector>

struct PlayerInterface;

#include "../../api/player_controller_interface.hpp"
#include "cards/card_interface.hpp"
#include "cards/deck.hpp"
#include "units/unit_interface.hpp"

#include "../../colour.hpp"

enum class PlayerType { human, ai };

/**
 * @brief Holds player resources state
 * Has handlers for actions
 */
struct PlayerInterface {
  virtual ~PlayerInterface() {}

  /**
   * @brief Set player's colour
   *
   * @param colour Colour to set
   */
  virtual void set_colour(Colour colour) = 0;

  /**
   * @brief Set player's type(human/ai)
   *
   * @param type Type to set
   */
  virtual void set_player_type(PlayerType type) = 0;
  /**
   * @brief Assign PlayerControllerInterface to Player
   *
   * @param api API - can be of human or AI(WIP)
   *
   */
  virtual void dock_player(std::shared_ptr<PlayerControllerInterface> api) = 0;

  /**
   * @brief Assign Deck Player
   *
   * @param deck To assign
   */
  virtual void dock_deck(const Deck &deck) = 0;

  /**
   * @brief Prepare Player resources for turn's begin
   *
   */
  virtual void start_turn() = 0;

  /**
   * @brief Complete Player turn and prepare for next player's turn
   *
   */
  virtual void end_turn() = 0;

  /**
   * @brief Add unit to Players army
   * If worker is added, increase their count
   *
   */
  virtual void add_unit(std::shared_ptr<UnitInterface>) = 0;

  /**
   * @brief Get the vector of units of player (workers and buildings)
   *
   * @return std::vector<std::shared_ptr<UnitInterface>>
   */
  virtual const std::vector<std::shared_ptr<UnitInterface>> &
  get_units() const = 0;

  /**
   * @brief Get units handler for manipulation
   *
   * @return std::vector<std::shared_ptr<UnitInterface>>&
   */
  virtual std::vector<std::shared_ptr<UnitInterface>> &handle_units() = 0;

  /**
   * @brief Make player draw n CardInterfaces from his deck (No more than whole
   * deck - shuffles if possible)
   * @param n Amount of Cards to draw
   */
  virtual void draw(size_t n) = 0;

  /**
   * @brief Get the vector of CardInterfaces in Player's hand
   *
   * @return std::vector<std::shared_ptr<CardInterface>>
   */
  virtual const std::vector<std::shared_ptr<CardInterface>> &
  get_hand() const = 0;

  /**
   * @brief Get Player hand handler for manipulation
   *
   * @return std::vector<std::shared_ptr<CardInterface>>&
   */
  virtual std::vector<std::shared_ptr<CardInterface>> &handler_hand() = 0;

  /**
   * @brief Resolve given card and discard it
   *
   * @param card Card to resolve
   * @return true Success
   * @return false Rollback
   */
  virtual bool play_card(std::shared_ptr<CardInterface> card) = 0;

  /**
   * @brief Get the API of this Player
   *
   * @return std::shared_ptr<PlayerControllerInterface>
   */
  virtual std::shared_ptr<PlayerControllerInterface> get_api() const = 0;

  /**
   * @brief adds Material into Player's resources
   *
   * @param material Type of Material
   * @param amount How much to add
   */
  virtual void add_material(Materials material, size_t amount) = 0;

  /**
   * @brief Expend Materials
   *
   * @param materials materials mapped by Material to pay
   * @throws IllegalStateException If Player is unable to pay the cost
   */
  virtual void pay_cost(const std::map<Materials, size_t> &materials) = 0;

  /**
   * @brief Get the deck object
   *
   * @return const Deck&
   */
  virtual const Deck &get_deck() const = 0;

  /**
   * @brief Get Player resources
   *
   * @return const std::map<Materials, size_t>&
   */
  virtual const std::map<Materials, size_t> &get_resources() const = 0;

  /**
   * @brief Get Player Colour
   *
   * @return Colour
   */
  virtual Colour get_colour() const = 0;
};
