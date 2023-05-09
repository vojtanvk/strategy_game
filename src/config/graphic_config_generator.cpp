/**
 * @file graphic_config_generator.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <sstream>

#include "config_types.hpp"
#include "graphic_config_generator.hpp"

GraphicConfigGenerator::GraphicConfigGenerator(GameInterface &game, GUI &gui,
                                               const std::string &filename) {
  load(game, gui, filename);
}

int GraphicConfigGenerator::start(GameInterface &game, GUI &gui) const {
  std::cout << "Welcome to graphic config generator" << std::endl;
  std::cout << "This tool was created to help creating and editing config "
               "files for this semestral."
            << std::endl;

  std::string input;
  std::vector<std::string> yes{"y", "Y", "yes", "Yes", "YES"};
  std::vector<std::string> no{"n", "N", "no", "NO", "No"};
  std::vector<std::string> cancel{"c", "C", "Cancel", "cancel", "CANCEL"};

  const auto equal_in = [&](const auto &in) { return in == input; };

  while (true) {
    std::cout << "Do you wish to create new config file? y/n ";
    if (!(std::cin >> input)) {
      throw InputException();
    }
    std::cout << std::endl;

    if (std::any_of(yes.begin(), yes.end(), equal_in)) {
      try {
        return create(game, gui);
      } catch (const Exception &ex) {
        std::cin.clear();
        std::cout << "Exception: " << ex.get_message()
                  << " occured during creating graphic configuration. Please, "
                     "select different option or file."
                  << std::endl;
      }
    }

    if (std::any_of(no.begin(), no.end(), equal_in)) {
      try {
        return load(game, gui);
      } catch (const Exception &ex) {
        std::cin.clear();
        std::cout << "Exception: " << ex.get_message()
                  << " occured during loading graphic configuration. Please, "
                     "select different option or file."
                  << std::endl;
      }
    }

    if (std::any_of(cancel.begin(), cancel.end(), equal_in)) {
      return 1;
    }
  }
}

int GraphicConfigGenerator::create(GameInterface &game, GUI &gui) const {

  std::map<Surface, bool> to_configure_surf;
  std::vector<Surface> surfaces{list_surface()};
  std::transform(surfaces.begin(), surfaces.end(),
                 std::inserter(to_configure_surf, to_configure_surf.end()),
                 [](const auto &surf) { return std::make_pair(surf, false); });

  std::map<size_t, bool> to_configure_unit;
  std::vector<size_t> unit_ids{game.get_unit_ids()};
  std::transform(unit_ids.begin(), unit_ids.end(),
                 std::inserter(to_configure_unit, to_configure_unit.end()),
                 [](const auto &id) { return std::make_pair(id, false); });

  const auto not_configured = [](const auto &key_val) -> bool {
    return !key_val.second;
  };

  std::map<Surface, SurfaceGraphics> surfaces_done;
  std::map<size_t, UnitGraphics> units_done;

  char map_colour{};

  std::vector<Colour> colours{list_colours()};
  std::set<char> colour_input;
  std::for_each(colours.begin(), colours.end(), [&](const auto &col) {
    colour_input.insert(to_char(col));
    colour_input.insert(toupper(to_char(col)));
  });

  bool map_done{false};
  char input;

  while (std::any_of(to_configure_surf.begin(), to_configure_surf.end(),
                     not_configured) ||
         std::any_of(to_configure_unit.begin(), to_configure_unit.end(),
                     not_configured) ||
         !map_done) {

    std::cout << "Define graphics for " << underline_first("Units") << " "
              << underline_first("Surfaces") << " " << underline_first("Map")
              << std::endl;

    if (!(std::cin >> input)) {
      throw IllegalStateException("Input ended prematurely");
    }

    UnitGraphics n_unit;
    SurfaceGraphics n_surface;

    switch (input) {
    case 'U':
    case 'u':
      try {
        to_configure_unit[n_unit.create(to_configure_unit, game)] = true;
        units_done[n_unit.get_id()] = n_unit;
      } catch (const Exception &ex) {
        std::cin.clear();
      }
      break;
    case 'S':
    case 's':
      try {
        to_configure_surf[n_surface.create(to_configure_surf)] = true;
        surfaces_done[n_surface.get_surface()] = n_surface;
      } catch (const Exception &) {
        std::cin.clear();
      }
      break;
    case 'M':
    case 'm':
      try {
        std::for_each(colours.begin(), colours.end(), [&](const auto &col) {
          std::cout << underline_first(name_colour(col)) << " ";
        });
        map_colour = tolower(read_in(colour_input));
        map_done = true;
      } catch (const Exception &) {
        std::cin.clear();
      }
      break;
    case 'C':
    case 'c':
      return 0;
    default:
      break;
    }
  }

  std::cout << "Please name your config file: ";
  MyFile file(read_in<std::string>({}), "w");
  std::cout << std::endl;
  write_string(file, "GuiConf");

  const auto write_load = [&](const auto &item) {
    item.second.write(file);
    item.second.load(gui);
  };

  write_single(file, 'M');
  write_single(file, map_colour);
  write_single(file, 'S');
  write_single(file, '{');
  write_single(file, surfaces_done.size());
  std::for_each(surfaces_done.begin(), surfaces_done.end(), write_load);
  write_single(file, '}');
  write_single(file, 'U');
  write_single(file, '{');
  write_single(file, units_done.size());
  std::for_each(units_done.begin(), units_done.end(), write_load);
  write_single(file, '}');

  return 0;
}

int GraphicConfigGenerator::load(
    GameInterface &game, GUI &gui,
    const std::optional<std::string> &filename) const {
  std::string path;
  if (filename) {
    path = *filename;
  } else {

    std::cout << "Input path to config file: ";
    path = read_in<std::string>({});
  }

  MyFile file(path, "r");

  std::cout << std::endl;
  if (read_string(file) != "GuiConf") {
    throw CorruptedFileException();
  }

  const auto to_conf_fun = [](const auto &item) {
    return std::make_pair(item, false);
  };

  const auto conf_done_fun = [](const auto item) { return !item.second; };

  read_single(file, 'M');
  char map_colour{read_single<char>(file)};
  std::vector<SurfaceGraphics> surf_graphics;

  std::map<Surface, bool> to_configure_surf;
  std::vector<Surface> surfaces{list_surface()};
  std::transform(surfaces.begin(), surfaces.end(),
                 std::inserter(to_configure_surf, to_configure_surf.end()),
                 to_conf_fun);

  read_single(file, 'S');
  read_single(file, '{');
  for (size_t i{read_single<size_t>(file)}; i > 0; --i) {
    surf_graphics.push_back(SurfaceGraphics().read(file));
    to_configure_surf[surf_graphics.back().get_surface()] = true;
  }
  read_single(file, '}');

  if (std::any_of(to_configure_surf.begin(), to_configure_surf.end(),
                  conf_done_fun)) {
    throw CorruptedFileException();
  }

  std::vector<UnitGraphics> unit_graphics;

  std::map<size_t, bool> to_configure_unit;
  std::vector<size_t> units(game.get_unit_ids());
  std::cout << "In current game are: " << units.size()
            << " units in need of graphics" << std::endl;
  std::transform(units.begin(), units.end(),
                 std::inserter(to_configure_unit, to_configure_unit.end()),
                 to_conf_fun);

  read_single(file, 'U');
  read_single(file, '{');
  for (size_t i{read_single<size_t>(file)}; i > 0; --i) {
    unit_graphics.push_back(UnitGraphics().read(file));
    to_configure_unit[unit_graphics.back().get_id()] = true;
  }
  read_single(file, '}');

  if (std::any_of(to_configure_unit.begin(), to_configure_unit.end(),
                  conf_done_fun)) {
    throw CorruptedFileException();
  }

  gui.set_map_background(to_code_colour_back(char_to_colour(map_colour)));

  const auto i_load = [&](const auto &item) { item.load(gui); };

  std::for_each(surf_graphics.begin(), surf_graphics.end(), i_load);
  std::for_each(unit_graphics.begin(), unit_graphics.end(), i_load);
  return 0;
}

std::string
GraphicConfigGenerator::underline_first(const std::string &line) const {
  if (line.empty()) {
    return 0;
  }
  std::string m_line{line};
  std::stringstream ss;
  ss << "\u001b[4m" << m_line.front() << "\u001b[0m";
  m_line.erase(0, 1);
  ss << m_line;
  return ss.str();
}