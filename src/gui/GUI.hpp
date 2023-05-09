/**
 * @file GUI.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>

struct GUI;

#include "../engine/mapping/map_interface.hpp"

struct GUI {
  virtual ~GUI() {}
  // virtual void dock_game(std::shared_ptr<GameInterface>) = 0;

  virtual void message(const std::string &) const = 0;
  virtual void print_help() const = 0;

  virtual void draw_map() const = 0;
  virtual void draw_deck(const Deck &) const = 0;
  virtual void draw_discard_pile(const Deck &) const = 0;
  virtual void draw_resources(const std::map<Materials, size_t> &) const = 0;
  virtual void draw_player(const PlayerInterface &) const = 0;
  virtual void draw_win_conditions() const = 0;

  virtual void
  highlight(const std::vector<std::pair<Coords, char>> &) const = 0;
  virtual void highlight(const Coords &, const std::vector<Coords> &) const = 0;

  virtual void select_unit(const std::vector<std::shared_ptr<UnitInterface>> &,
                           const std::vector<char> &) const = 0;
  virtual void select_material(const std::vector<Materials> &,
                               const std::vector<char> &) const = 0;
  virtual void select_movement(const Coords &, const Coords &,
                               const std::vector<Coords> &,
                               const std::vector<Coords> &,
                               const std::vector<char> &) const = 0;
  virtual void build(const Coords &, const std::vector<Coords> &,
                     const std::vector<Blueprint> &,
                     const std::vector<char> &) const = 0;
  virtual void select_buildplace(const Coords &, const std::vector<Coords> &,
                                 const std::vector<char> &) const = 0;
  virtual void select_card(const Deck &, const std::vector<char> &) const = 0;

  virtual void add_surface_graphic(Surface, const std::string &, char) = 0;
  virtual void add_unit_graphic(size_t, const std::string &, char) = 0;
  virtual void set_map_background(const std::string &) = 0;
};