/**
 * @file game_loader.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <filesystem>
#include <iostream>
#include <sstream>

#include "../exceptions/exception.hpp"
#include "game_loader.hpp"
#include "map_loader.hpp"
#include "my_file.hpp"
#include "player_loader.hpp"

void GameLoader::save(const std::string &path, const std::string &filename,
                      const GameInterface &game) const {
  std::string save_path{path + "/" + filename};
  // std::string save_path{path};
  std::filesystem::path p{save_path};
  if (!std::filesystem::exists(p) && !std::filesystem::create_directories(p)) {
    throw IllegalStateException("Unable to create directory");
  }
  std::filesystem::permissions(p, std::filesystem::perms::all);

  MyFile file{save_path + "/" + filename, "w"};

  write_single(file, 'G');

  std::string m_filename{"M-" + filename};
  MapLoader().save(save_path, m_filename, game.get_map());
  write_string(file, m_filename);

  write_single(file, game.get_blueprints().size());
  std::for_each(
      game.get_blueprints().begin(), game.get_blueprints().end(),
      [&](const auto &id_bp) { write_blueprint(file, id_bp.second); });

  write_single(file, game.get_players().size());

  save_players(file, filename, save_path, game.get_players(), 'p',
               PlayerLoader{});

  write_single(file, game.get_active_player_index());

  write_single(file, game.get_win_cons().size());
  std::for_each(game.get_win_cons().begin(), game.get_win_cons().end(),
                [&](const auto &win_con) { write_win_con(file, win_con); });

  // TODO sum
}

void GameLoader::load(const std::string &path, const std::string &filename,
                      GameInterface &game) const {
  std::string save_path(path + "/" + filename);
  // std::string save_path(path);
  std::filesystem::path p(save_path);
  if (!std::filesystem::exists(p)) {
    throw IllegalArgumentException("Save does not exist");
  }

  MyFile file{save_path + "/" + filename, "r"};

  read_single(file, 'G');
  game.dock_map(MapLoader().load(save_path + "/" + read_string(file)));

  for (size_t i = read_single<size_t>(file); i > 0; --i) {
    game.add_blueprint(read_blueprint(file));
  }

  PlayerLoader p_loader;
  for (size_t i = read_single<size_t>(file); i > 0; --i) {
    std::string p_filename{read_string(file)};
    game.add_player(p_loader.load(save_path, p_filename, game));
  }

  game.set_active_player(read_single<size_t>(file));

  for (size_t i = read_single<size_t>(file); i > 0; --i) {
    game.add_win_con(read_win_con(file));
  }
}
