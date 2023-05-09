/**
 * @file terminal_gui.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "GUI.hpp"

#include "../engine/player/units/units.hpp"

#include "../colour.hpp"

class TerminalGui : public GUI {
public:
  TerminalGui(GameInterface &);
  virtual ~TerminalGui() = default;

  // void dock_game(std::shared_ptr<GameInterface>) override;

  void message(const std::string &) const override;
  void print_help() const override;

  void draw_map() const override;
  void draw_deck(const Deck &) const override;
  void draw_discard_pile(const Deck &) const override;
  void draw_resources(const std::map<Materials, size_t> &) const override;
  void draw_player(const PlayerInterface &) const override;
  void draw_win_conditions() const override;

  void highlight(const std::vector<std::pair<Coords, char>> &) const override;
  void highlight(const Coords &, const std::vector<Coords> &) const override;

  void select_unit(const std::vector<std::shared_ptr<UnitInterface>> &,
                   const std::vector<char> &) const override;
  void select_material(const std::vector<Materials> &,
                       const std::vector<char> &) const override;
  void select_movement(const Coords &, const Coords &,
                       const std::vector<Coords> &, const std::vector<Coords> &,
                       const std::vector<char> &) const override;
  void build(const Coords &, const std::vector<Coords> &,
             const std::vector<Blueprint> &,
             const std::vector<char> &) const override;
  void select_buildplace(const Coords &, const std::vector<Coords> &,
                         const std::vector<char> &) const override;
  void select_card(const Deck &, const std::vector<char> &) const override;

  void add_surface_graphic(Surface, const std::string &, char) override;
  void add_unit_graphic(size_t, const std::string &, char) override;
  void set_map_background(const std::string &) override;

private:
  const char UP_CUR{'A'};
  const char DOWN_CUR{'B'};
  const char LEFT_CUR{'D'};
  const char RIGHT_CUR{'C'};
  const std::string SAVE_CUR{"\033[s"};
  const std::string RESTORE_CUR{"\033[u"};
  const char LINE_START_CUR{'\r'};
  const char BACKSPACE{'\b'};

  char symbol_unit(size_t) const;
  std::string coloured_surface(Surface) const;
  std::string name_unit(size_t) const;

  void write_on_map(char, const std::string &, const Coords &) const;

  void draw_cards(const std::vector<std::shared_ptr<CardInterface>> &,
                  const std::vector<char> & = {}) const;

  GameInterface &game;
  std::map<size_t, std::pair<std::string, char>> id_name_symbol;
  std::map<Surface, std::pair<std::string, char>> surf_col_symbol;
  std::string map_colour{"\u001b[47m"};

  std::string move_cursor(size_t x, char dir) const;
};