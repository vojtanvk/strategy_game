/**
 * @file cards_loader.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <sstream>

#include "../engine/player/cards/actions.hpp"
#include "../engine/player/cards/card.hpp"
#include "cards_loader.hpp"
#include "my_file.hpp"

void DeckLoader::save(const std::string &path, const std::string &filename,
                      const Deck &deck) const {
  MyFile file{path + "/" + filename, "w"};

  write_single(file, 'D');

  write_single(file, deck.get_draw_pile().size());
  write_single(file, deck.get_hand().size());
  write_single(file, deck.get_discard_pile().size());

  CardLoader c_loader;

  save_cards(file, path, filename, deck.get_draw_pile(), 'd', c_loader);
  save_cards(file, path, filename, deck.get_hand(), 'h', c_loader);
  save_cards(file, path, filename, deck.get_discard_pile(), 'x', c_loader);

  // TODO sum
}

Deck DeckLoader::load(const std::string &path, const std::string &filename,
                      GameInterface &game) const {
  MyFile file{path + "/" + filename, "r"};

  read_single(file, 'D');

  size_t draw_size{read_single<size_t>(file)};
  size_t hand_size{read_single<size_t>(file)};
  size_t discard_size{read_single<size_t>(file)};

  Deck out{{}};

  CardLoader c_loader;
  auto draw_lambda = [&](std::shared_ptr<CardInterface> card) {
    out.add_draw(card);
  };

  auto hand_lambda = [&](std::shared_ptr<CardInterface> card) {
    out.add_hand(card);
  };

  auto disc_lambda = [&](std::shared_ptr<CardInterface> card) {
    out.add_discard(card);
  };

  load_cards(file, path, draw_size, c_loader, game, draw_lambda);
  load_cards(file, path, hand_size, c_loader, game, hand_lambda);
  load_cards(file, path, discard_size, c_loader, game, disc_lambda);
  return out;
}

void DeckLoader::load_cards(
    FILE *file, const std::string &path, size_t amount,
    const CardLoader &c_loader, GameInterface &game,
    std::function<void(std::shared_ptr<CardInterface>)> fun) const {
  for (size_t i = 0; i < amount; ++i) {

    std::string c_filename(read_string(file));
    fun(c_loader.load(path, c_filename, game));
  }
}

void CardLoader::save(const std::string &path, const std::string &filename,
                      const std::shared_ptr<CardInterface> &card) const {

  MyFile file{path + "/" + filename, "w"};

  auto actions = card->get_actions();
  write_single(file, 'C');
  write_single(file, actions.size());
  std::for_each(actions.begin(), actions.end(), [&](const auto &a) {
    write_single(file, to_char(a->get_type()));
    write_single(file, a->get_value());
  });
}

std::shared_ptr<CardInterface> CardLoader::load(const std::string &path,
                                                const std::string &filename,
                                                GameInterface &game) const {
  MyFile file{path + "/" + filename, "r"};

  read_single(file, 'C');

  std::vector<std::shared_ptr<ActionInterface>> vect_actions;

  for (size_t a = read_single<size_t>(file); a > 0; --a) {
    auto type = read_single<char>(file);
    auto val = read_single<size_t>(file);
    vect_actions.push_back(action_factory(type, val, game));
  }

  return std::make_shared<Card>(vect_actions);
}

std::shared_ptr<ActionInterface>
CardLoader::action_factory(char type, size_t val, GameInterface &game) const {
  switch (char_to_action(type)) {
  case ActionType::build:
    return std::make_shared<Build>(val, game);
  case ActionType::draw:
    return std::make_shared<Draw>(val, game);
  case ActionType::harvest:
    return std::make_shared<Harvest>(val, game);
  case ActionType::movement:
    return std::make_shared<Movement>(val, game);
  default:
    throw IllegalArgumentException("Unknown action type");
  }
}