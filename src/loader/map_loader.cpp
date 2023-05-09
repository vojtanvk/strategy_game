/**
 * @file map_loader.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../engine/mapping/mapping.hpp"
#include "../exceptions/exception.hpp"
#include "map_loader.hpp"
#include "my_file.hpp"

#include <iostream>

void MapLoader::save(const std::string &path, const std::string &filename,
                     const std::shared_ptr<MapInterface> &map) const {
  MyFile file{path + "/" + filename, "w"};

  write_single(file, 'M');

  auto dim = map->get_dimensions();
  write_single(file, dim.y);
  write_single(file, dim.x);

  auto mp = map->get_map();

  for (const auto &line : mp) {
    for (const auto &sp : line) {
      write_single(file, to_char(sp->get_surface()));
    }
  }
}

std::shared_ptr<MapInterface>
MapLoader::load(const std::string &filename) const {
  MyFile file{filename, "r"};

  read_single(file, 'M');

  size_t dim_y = read_single<size_t>(file);
  size_t dim_x = read_single<size_t>(file);
  if (dim_x > MapInterface::MAX_SIZE || dim_y > MapInterface::MAX_SIZE) {
    throw IllegalArgumentException("Map too big");
  }

  std::vector<std::vector<std::shared_ptr<SpaceInterface>>> map_vectors;
  std::list<Coords> starting_points;

  for (size_t y = 0; y < dim_y; ++y) {
    map_vectors.push_back({});
    for (size_t x = 0; x < dim_x; ++x) {
      char c = read_single<char>(file);
      if (starting_points.size() < MapInterface::MAX_PLAYERS && c == 'x') {
        starting_points.push_back({x, y});
      }
      map_vectors[y].push_back(space_factory(c, x, y));
    }
  }

  return std::make_shared<Map>(Map{map_vectors, starting_points});
}

std::shared_ptr<SpaceInterface> MapLoader::space_factory(char c, size_t x,
                                                         size_t y) const {
  if (c == 'x') {
    return std::make_shared<Plains>(Plains({x, y}));
  }

  switch (char_to_surface(c)) {
  case Surface::plains:
    return std::make_shared<Plains>(Plains({x, y}));
  case Surface::forest:
    return std::make_shared<Forest>(Forest({x, y}));
  case Surface::mountain:
    return std::make_shared<Mountain>(Mountain({x, y}));
  case Surface::water:
    return std::make_shared<Water>(Water({x, y}));
  default:
    throw CorruptedFileException();
  }
}
