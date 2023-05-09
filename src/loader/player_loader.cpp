/**
 * @file player_loader.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../engine/player/player.hpp"
#include "../engine/player/units/unit_factory.hpp"
#include "../engine/player/units/units.hpp"
#include "../exceptions/exception.hpp"
#include "cards_loader.hpp"
#include "my_file.hpp"
#include "player_loader.hpp"

void PlayerLoader::save(const std::string &path, const std::string &filename,
                        const std::shared_ptr<PlayerInterface> &player) const {
  MyFile file{path + "/" + filename, "w"};

  write_single(file, 'P');
  write_single(file, to_char(player->get_colour()));

  std::string d_filename{"D-" + filename};
  DeckLoader d_loader;
  d_loader.save(path, d_filename, player->get_deck());
  write_string(file, d_filename);

  write_material(file, player->get_resources());

  auto u_vect = player->get_units();
  write_single(file, u_vect.size());

  for (const auto &u : u_vect) {
    write_single(file, u->get_id());

    auto pos = u->get_position();
    write_single(file, pos.x);
    write_single(file, pos.y);
  }
}

std::shared_ptr<PlayerInterface> PlayerLoader::load(const std::string &path,
                                                    const std::string &filename,
                                                    GameInterface &game) const {
  MyFile file{path + "/" + filename, "r"};

  read_single(file, 'P');

  auto player = std::make_shared<Player>();

  player->set_colour(char_to_colour(read_single<char>(file)));
  player->dock_deck(DeckLoader().load(path, read_string(file), game));

  auto resources = read_material(file);
  for (const auto &r : resources) {
    player->add_material(r.first, r.second);
  }

  for (size_t i = read_single<size_t>(file); i > 0; --i) {
    size_t id{read_single<size_t>(file)};
    auto bp = game.get_blueprint(id);
    auto n_unit = UnitFactory().build(*player, bp);
    size_t x{read_single<size_t>(file)};
    size_t y{read_single<size_t>(file)};

    n_unit->set_position({x, y});
    player->add_unit(n_unit);
  }
  return player;
}
