/**
 * @file human_controller.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../gui/GUI.hpp"
#include "../gui/MenuGUI.hpp"
#include "player_controller_interface.hpp"

class HumanController : public PlayerControllerInterface {
public:
  HumanController(GameInterface &, const GUI &, const MenuGUI &);
  virtual ~HumanController() = default;

  GameInterface &handler_game() override;

  int select_card(const Deck &, const PlayerInterface &,
                  std::shared_ptr<CardInterface> &) override;
  bool select_unit(const std::vector<std::shared_ptr<UnitInterface>> &,
                   std::shared_ptr<UnitInterface> &) const override;
  bool choose_material(const std::vector<Materials> &,
                       Materials &) const override;
  int read_movement(const Coords &, Coords &, const std::vector<Coords> &,
                    const std::vector<Coords> &) const override;
  int build(const std::vector<Blueprint> &, const Coords &,
            const std::vector<Coords> &, const std::map<Materials, size_t> &,
            Blueprint &, Coords &) const override;

private:
  GameInterface &game;
  const GUI &gui;
  const MenuGUI &menu;

  const std::set<char> def_inputs{CANCEL, RESOURCES, HELP, MAP,
                                  DECK,   REPEAT,    WIN};
  /**
   * @brief Cycles and waits for valid input defined in arguments

   *
   * @param valid Set of valid inputs
   * @param to_num If true, translates '1' to 0 and 'a' to 9 for indexing
   * purpouses
   * '0' is a special value and will not be translated to number
   * @return char Read input (can be transalted)
   */
  char process_input(const std::set<char> &valid, bool to_num = true) const;

  /**
   * @brief Generates char input set of given size
   * Translates 0 to '1' ... 9 to 'a' so numbers are of single char (And won't
   * break graphics)
   *
   * @param size How many inputs
   * @param cap Limit
   * @return std::vector<char>
   */
  std::vector<char> generate_input_set(size_t size, size_t cap = 0) const;
};