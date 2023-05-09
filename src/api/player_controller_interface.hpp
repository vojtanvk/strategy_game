/**
 * @file player_controller_interface.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

struct PlayerControllerInterface;

#include <functional>

#include "../engine/game_interface.hpp"
#include "../engine/mapping/coords.hpp"
#include "../engine/player/cards/deck.hpp"
#include "../engine/player/units/blueprint.hpp"
#include "../engine/player/units/unit_interface.hpp"
#include "../engine/resources/materials.hpp"

constexpr char REPEAT{'C'};
constexpr char CANCEL{'~'};
constexpr char MAP{'M'};
constexpr char HELP{'H'};
constexpr char RESOURCES{'R'};
constexpr char WIN{'W'};
constexpr char DECK{'D'};
constexpr char STOP{';'};
constexpr char MORE{'0'};

constexpr int ROLLBACK{-1};
constexpr int CONTINUE{1};
constexpr int SKIP{0};

struct PlayerControllerInterface {
  virtual ~PlayerControllerInterface() {}
  virtual GameInterface &handler_game() = 0;

  /**
   * @brief Lets Player choose a card from his hand and returns it in referenced
   * argument
   *
   * @param deck Deck to draw
   * @param player Actor
   * @param played_card Reference where chosen Card goes
   * @return int CONTINUE(1), ROLLBACK(-1), SKIP(0)
   */
  virtual int select_card(const Deck &deck, const PlayerInterface &player,
                          std::shared_ptr<CardInterface> &played_card) = 0;

  /**
   * @brief Lets active Player choose Card from given list and returns it in
   * referenced argument
   *
   * @param units To choose from
   * @param chosen Chosen unit reference
   * @return true If chosen successfully
   * @return false If canceled
   */
  virtual bool
  select_unit(const std::vector<std::shared_ptr<UnitInterface>> &units,
              std::shared_ptr<UnitInterface> &chosen) const = 0;

  /**
   * @brief Lets Player move Unit at given Coordinates around
   *
   * @param start Starting position
   * @param current Current position
   * @param immediate Where can move currently
   * @param max_possible To highlight where move is possible
   * @return int CONTINUE(1), ROLLBACK(-1), SKIP(0)
   */
  virtual int read_movement(const Coords &start, Coords &current,
                            const std::vector<Coords> &immediate,
                            const std::vector<Coords> &max_possible) const = 0;

  /**
   * @brief Lets Player choose what to harvest
   *
   * @param harvestable List of harvestable materials
   * @param harvested Return value
   * @return true Success
   * @return false Cancel
   */
  virtual bool choose_material(const std::vector<Materials> &harvestable,
                               Materials &harvested) const = 0;

  /**
   * @brief Lets Player choose what to build from given list
   *
   * @param possible_builds To choose from
   * @param where Where is builder
   * @param possible_sites Where can be built
   * @param resources Player resources
   * @param chosen_build What was chosen to be built
   * @param chosen_position Where was chosen to be built
   * @return int CONTINUE(1), ROLLBACK(-1), SKIP(0)
   */
  virtual int build(const std::vector<Blueprint> &possible_builds,
                    const Coords &where,
                    const std::vector<Coords> &possible_sites,
                    const std::map<Materials, size_t> &resources,
                    Blueprint &chosen_build, Coords &chosen_position) const = 0;
};