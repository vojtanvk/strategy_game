/**
 * @file config_types.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <algorithm>
#include <iostream>
#include <vector>

#include "../engine/player/cards/actions.hpp"
#include "../engine/player/cards/card.hpp"
#include "config_types.hpp"
#include "sstream"

bool CardConfig::create(const std::vector<CardConfig> &current) {
  return edit(current);
}
bool CardConfig::edit(const std::vector<CardConfig> &) {
  while (true) {
    auto val = add_action();
    if (val == 0 && !empty()) {
      return true;
    }
    if (val == -1) {
      return false;
    }
  }
}

void CardConfig::load(GameInterface &game) const {
  std::vector<std::shared_ptr<ActionInterface>> a_vector;
  std::for_each(actions.begin(), actions.end(), [&](const auto &action) {
    switch (action.first) {
    case ActionType::build:
      a_vector.push_back(std::make_shared<Build>(action.second, game));
      break;
    case ActionType::draw:
      a_vector.push_back(std::make_shared<Draw>(action.second, game));
      break;
    case ActionType::harvest:
      a_vector.push_back(std::make_shared<Harvest>(action.second, game));
      break;
    case ActionType::movement:
      a_vector.push_back(std::make_shared<Movement>(action.second, game));
      break;
    default:
      throw IllegalArgumentException("Unknown action type");
    }
  });
  game.add_start_card(Card{a_vector});
}

void CardConfig::write(FILE *file) const {
  write_single(file, '[');
  write_single(file, actions.size());
  std::for_each(actions.begin(), actions.end(), [&](const auto &action) {
    write_single(file, to_char(action.first));
    write_single(file, action.second);
  });
  write_single(file, ']');
}

CardConfig &CardConfig::read(FILE *file) {
  read_single(file, '[');
  for (size_t a_count{read_single<size_t>(file)}; a_count > 0; --a_count) {
    actions.push_back(
        {char_to_action(read_single<char>(file)), read_single<size_t>(file)});
  }
  read_single(file, ']');
  return *this;
}

int CardConfig::add_action() {
  char input;
  while (true) {
    if (!actions.empty()) {
      std::cout << "Currently: ";
      print();
      std::cout << std::endl;
    }
    std::cout << "Select action to add or finish: " << std::endl
              << " " << underline("B") << "uild, \u001b[4mD\u001b[0mraw, "
              << underline("H") << "arvest, " << underline("M") << "ove, do"
              << underline("N") << "e, " << underline("C") << "ancel"
              << std::endl;
    if (!(std::cin >> input)) {
      throw Exception(10, "Write ended prematurely");
    }

    switch (input) {
    case 'C':
    case 'c':
      return -1;
    case 'N':
    case 'n':
      return 0;
    case 'b':
    case 'B':
    case 'H':
    case 'h':
    case 'M':
    case 'm':
    case 'D':
    case 'd':
      process_coef([&](size_t coef) {
        this->actions.push_back(std::make_pair(char_to_action(input), coef));
      });
      if (char_to_action(input) == ActionType::draw) {
        return 0;
      }
      return 1;
    }
  }
}

void CardConfig::print() const {
  for (const auto &a : actions) {
    std::cout << to_string(a.first) << " " << a.second << " ";
  }
}
bool CardConfig::empty() const { return actions.empty(); }

bool UnitConfig::create(const std::vector<UnitConfig> &currently) {
  unit.set_id(currently.size());
  std::cout << "Select type: " << std::endl
            << underline("W") << "orker; " << underline("B") << "uilding"
            << std::endl;

  unit.set_type(char_to_unit(tolower(read_in<char>({'W', 'w', 'B', 'b'}))));
  return edit(currently);
}

bool UnitConfig::edit(const std::vector<UnitConfig> &currently) {
  while (true) {
    size_t index{0};
    std::cout << "Current: ";
    print();
    std::cout << std::endl
              << "Select modificator or finish: " << std::endl
              << underline("C") << "ost; " << underline("M") << "ove bonus; "
              << underline("H") << "arvest; " << underline("P") << "oints; "
              << underline("S") << "tart count; " << underline("A")
              << "dd build; " << underline("D") << "one; cance"
              << underline("L") << std::endl;
    switch (read_in<char>({'C', 'c', 'M', 'm', 'H', 'h', 'P', 'p', 'D', 'd',
                           'L', 'l', 'S', 's', 'A', 'a'})) {
    case 'C':
    case 'c':
      process_material(
          unit.get_cost(),
          [&](const std::map<Materials, size_t> &val) { unit.set_cost(val); });
      break;
    case 'M':
    case 'm':
      process_coef([&](size_t val) { unit.set_move(val); });
      break;
    case 'H':
    case 'h':
      process_material(unit.get_harvest_list(),
                       [&](const std::map<Materials, size_t> &val) {
                         unit.set_harvest_list(val);
                       });
      break;
    case 'P':
    case 'p':
      process_coef([&](size_t val) { unit.set_points(val); });
      break;
    case 'S':
    case 's':
      std::cout << "How many at start? ";
      process_coef([&](size_t val) { this->start_count = val; });
      std::cout << std::endl;
      break;
    case 'A':
    case 'a':
      if (currently.empty()) {
        break;
      }
      for (const auto unit : currently) {
        std::cout << index << ": ";
        unit.print();
        std::cout << std::endl;
        index++;
      }
      index = read_in<size_t>({});
      if (index < currently.size()) {
        unit.add_build_list(currently[index].unit.get_id());
      }
      break;
    case 'D':
    case 'd':
      return true;
    case 'L':
    case 'l':
      return false;
    default:
      break;
    }
  }
}

void UnitConfig::load(GameInterface &game) const {
  game.add_blueprint(unit);
  if (start_count) {
    game.add_starting_unit(unit, start_count);
  }
}

void UnitConfig::print() const {
  print_bp(unit);
  std::cout << " at start: " << start_count;
}

void UnitConfig::write(FILE *file) const {
  write_single(file, 'x');
  write_single(file, start_count);
  write_blueprint(file, unit);
}

UnitConfig &UnitConfig::read(FILE *file) {
  read_single(file, 'x');
  start_count = read_single<size_t>(file);

  unit = read_blueprint(file);
  return *this;
}

void UnitConfig::set_harvest_list(
    const std::map<Materials, size_t> &harvest_list) {
  unit.set_harvest_list(harvest_list);
}

void UnitConfig::set_cost(const std::map<Materials, size_t> &cost) {
  unit.set_cost(cost);
}

void UnitConfig::set_move(size_t move) { unit.set_move(move); }

void UnitConfig::set_points(size_t points) { unit.set_points(points); }

bool WinConfig::create(const std::vector<WinConfig> &current) {
  return edit(current);
}

bool WinConfig::edit(const std::vector<WinConfig> &) {
  while (true) {
    std::cout << "Current: ";
    print();
    std::cout << std::endl;

    std::cout << "Select option: " << std::endl
              << underline("P") << "oints; " << underline("U") << "nits; "
              << underline("M") << "aterial; " << underline("D") << "one; "
              << underline("C") << "ancel" << std::endl;

    char input{
        read_in<char>({'P', 'p', 'U', 'u', 'M', 'm', 'D', 'd', 'C', 'c'})};
    switch (input) {
    case 'P':
    case 'p':
      process_coef([&](size_t coef) { this->condition.set_points(coef); });
      break;
    case 'U':
    case 'u':
      process_coef([&](size_t coef) { this->condition.set_unit_count(coef); });
      break;
    case 'M':
    case 'm':
      process_material(condition.get_materials(), [&](const auto &material) {
        this->condition.set_materials(material);
      });
      break;
    case 'D':
    case 'd':
      return true;
    case 'C':
    case 'c':
      return false;
    default:
      break;
    }
  }
}

void WinConfig::load(GameInterface &game) const { game.add_win_con(condition); }

void WinConfig::print() const {
  std::cout << "Points: " << condition.get_points()
            << "; Unit count: " << condition.get_unit_count()
            << "; Materials: ";
  print_material(condition.get_materials());
}

void WinConfig::write(FILE *file) const { write_win_con(file, condition); }

WinConfig &WinConfig::read(FILE *file) {
  condition = read_win_con(file);
  return *this;
}

void Config::process_material(
    const std::map<Materials, size_t> &material,
    std::function<void(const std::map<Materials, size_t> &)> fun) {
  std::map<Materials, size_t> curr = material;
  while (true) {
    std::cout << "current: [ ";
    for (const auto &c : curr) {
      std::cout << to_string(c.first) << ": " << c.second << " ";
    }
    std::cout << "]" << std::endl;

    std::cout << "Select material: " << underline("S") << "tone; "
              << underline("W") << "ood; " << underline("D") << "one; "
              << underline("C") << "ancel" << std::endl;
    switch (read_in<char>({'W', 'w', 'S', 's', 'D', 'd', 'C', 'c'})) {
    case 'S':
    case 's':
      process_coef([&](size_t coef) { curr[Materials::stone] = coef; });
      break;
    case 'W':
    case 'w':
      process_coef([&](size_t coef) { curr[Materials::wood] = coef; });
      break;
    case 'D':
    case 'd':
      fun(curr);
      return;
    case 'C':
    case 'c':
      return;
    default:
      break;
    }
  }
}

void Config::process_coef(std::function<void(size_t)> fun) {
  std::cout << "Input coef: ";
  fun(read_in<size_t>({}));
  std::cout << std::endl;
}

void Config::print_material(const std::map<Materials, size_t> &material) const {
  std::cout << "[ ";
  for (const auto &mat : material) {
    std::cout << to_string(mat.first) << " " << mat.second << " ";
  }
  std::cout << "]";
}

std::string Config::underline(const std::string &line) {
  return "\u001b[4m" + line + "\u001b[0m";
}
std::string Config::underline_first(const std::string &line) {
  if (line.empty()) {
    return "";
  }
  std::string m_line{line};
  std::stringstream ss;
  ss << "\u001b[4m" << m_line.front() << "\u001b[0m";
  m_line.erase(0, 1);
  ss << m_line;
  return ss.str();
}

Surface SurfaceGraphics::create(const std::map<Surface, bool> &to_configure) {
  std::for_each(to_configure.begin(), to_configure.end(),
                [](const auto &id_bool) {
                  std::cout << to_string(id_bool.first) << " "
                            << (id_bool.second ? CHECK : CROSS) << std::endl;
                });

  std::vector<Surface> surfaces{list_surface()};
  std::set<char> surface_input;
  std::for_each(surfaces.begin(), surfaces.end(), [&](const auto &surf) {
    std::cout << underline_first(to_string(surf)) << " ";
    surface_input.insert(to_char(surf));
    surface_input.insert(toupper(to_char(surf)));
  });

  surface = char_to_surface(tolower(read_in<char>(surface_input)));
  std::cout << std::endl << "What symbol should represent this surface? ";
  symbol = read_in<char>({});
  std::cout << std::endl << "How hould be this surface coloured?" << std::endl;

  std::vector<Colour> colours{list_colours()};
  std::set<char> colour_input;
  std::for_each(colours.begin(), colours.end(), [&](const auto &col) {
    std::cout << underline_first(name_colour(col)) << " ";
    colour_input.insert(to_char(col));
    colour_input.insert(toupper(to_char(col)));
  });
  colour = char_to_colour(tolower(read_in<char>(colour_input)));
  std::cout << std::endl;
  return surface;
}

void SurfaceGraphics::print() const {
  std::cout << to_string(surface) << " " << to_code_colour_front(colour)
            << symbol << '(' << symbol << ')';
}

void SurfaceGraphics::write(FILE *file) const {
  write_single(file, 't');
  write_single(file, to_char(surface));
  write_single(file, 's');
  write_single(file, symbol);
  write_single(file, 'c');
  write_single(file, to_char(colour));
}
SurfaceGraphics &SurfaceGraphics::read(FILE *file) {
  read_single(file, 't');
  surface = char_to_surface(read_single<char>(file));
  read_single(file, 's');
  symbol = read_single<char>(file);
  read_single(file, 'c');
  colour = char_to_colour(read_single<char>(file));
  return *this;
}

void SurfaceGraphics::load(GUI &gui) const {
  gui.add_surface_graphic(surface, to_code_colour_front(colour), symbol);
}

Surface SurfaceGraphics::get_surface() const { return surface; }

size_t UnitGraphics::create(const std::map<size_t, bool> &to_configure,
                            GameInterface &game) {
  // list all necessary to configure and whether are configured
  std::for_each(to_configure.begin(), to_configure.end(),
                [](const auto &id_bool) {
                  std::cout << id_bool.first << " "
                            << (id_bool.second ? CHECK : CROSS) << std::endl;
                });

  std::cout << "Select id: ";
  id = read_in<size_t>({});

  try {
    auto bp{game.get_blueprint(id)};
    print_bp(bp);

  } catch (const Exception &) {
    std::cout << "INFO: Unit of given id is not present in current game"
              << std::endl;
  }

  std::cout << "What symbol should represent this unit? ";
  symbol = read_in<char>({});
  std::cout << std::endl;
  std::cout << "What would you name this unit? ";
  name = read_in<std::string>({});
  std::cout << std::endl;

  return id;
}
void UnitGraphics::print() const {
  std::cout << id << " " << symbol << " " << name;
}
void UnitGraphics::write(FILE *file) const {
  write_single(file, 'i');
  write_single(file, id);
  write_single(file, 's');
  write_single(file, symbol);
  write_single(file, 'n');
  write_string(file, name);
}
UnitGraphics &UnitGraphics::read(FILE *file) {
  read_single(file, 'i');
  id = read_single<size_t>(file);
  read_single(file, 's');
  symbol = read_single<char>(file);
  read_single(file, 'n');
  name = read_string(file);
  return *this;
}

void UnitGraphics::load(GUI &gui) const {
  gui.add_unit_graphic(id, name, symbol);
}

size_t UnitGraphics::get_id() const { return id; }

void Config::print_bp(const Blueprint &bp) const {
  std::cout << "Id: " << bp.get_id() << " " << to_string(bp.get_type())
            << " pts: " << bp.get_points() << " move: " << bp.get_move()
            << " cost: ";
  print_material(bp.get_cost());
  std::cout << " harvest: ";
  print_material(bp.get_harvest_list());
  std::cout << " builds(ids): ";
  for (const auto &b : bp.get_build_list()) {
    std::cout << b << " ";
  }
}