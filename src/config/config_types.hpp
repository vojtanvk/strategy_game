/**
 * @file config_types.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <functional>
#include <map>
#include <set>

#include "../engine/game_interface.hpp"
#include "../engine/player/cards/action_type.hpp"
#include "../engine/player/units/blueprint.hpp"
#include "../engine/player/units/unit_type.hpp"
#include "../engine/resources/materials.hpp"
#include "../engine/win_con.hpp"
#include "../gui/GUI.hpp"
#include "../loader/file_loader.hpp"

const std::string CHECK{"\u2714"};
const std::string CROSS{"\u274c"};

struct Config : public FileLoader {
  virtual void print() const = 0;
  virtual void write(FILE *) const = 0;
  virtual Config &read(FILE *) = 0;

protected:
  void
  process_material(const std::map<Materials, size_t> &,
                   std::function<void(const std::map<Materials, size_t> &)>);
  void process_coef(std::function<void(size_t)>);

  void print_material(const std::map<Materials, size_t> &) const;
  void print_bp(const Blueprint &) const;

  std::string underline(const std::string &);
  std::string underline_first(const std::string &);
};

struct UnitConfig : public Config {
  bool create(const std::vector<UnitConfig> &);
  bool edit(const std::vector<UnitConfig> &);
  void write(FILE *) const;
  void print() const override;
  void load(GameInterface &) const;
  UnitConfig &read(FILE *) override;

private:
  void set_harvest_list(const std::map<Materials, size_t> &);
  void set_cost(const std::map<Materials, size_t> &);

  void set_move(size_t);
  void set_points(size_t);

  size_t start_count{0};
  Blueprint unit;
};

struct CardConfig : public Config {
  bool create(const std::vector<CardConfig> &);
  bool edit(const std::vector<CardConfig> &);
  void print() const override;
  void write(FILE *) const override;
  void load(GameInterface &) const;
  CardConfig &read(FILE *) override;

private:
  int add_action();
  bool empty() const;

  std::vector<std::pair<ActionType, size_t>> actions;
};

template <typename Input> Input read_in(const std::set<Input> &valid) {
  Input input;
  while (true) {
    if (!(std::cin >> input)) {
      throw Exception(10, "Input ended prematurely");
    }

    if (valid.empty() || valid.count(input)) {
      return input;
    }
  }
}

struct WinConfig : public Config {
  bool create(const std::vector<WinConfig> &);
  bool edit(const std::vector<WinConfig> &);
  void print() const override;
  void write(FILE *) const override;
  void load(GameInterface &) const;
  WinConfig &read(FILE *) override;

private:
  WinCon condition;
};

struct SurfaceGraphics : public Config {
  Surface create(const std::map<Surface, bool> &);
  void print() const override;
  void write(FILE *) const override;
  void load(GUI &) const;
  SurfaceGraphics &read(FILE *) override;
  Surface get_surface() const;

private:
  Surface surface;
  char symbol;
  Colour colour;
};

struct UnitGraphics : public Config {
  size_t create(const std::map<size_t, bool> &, GameInterface &);
  void print() const override;
  void write(FILE *) const override;
  void load(GUI &) const;
  UnitGraphics &read(FILE *) override;

  size_t get_id() const;

private:
  size_t id;
  char symbol;
  std::string name;
};