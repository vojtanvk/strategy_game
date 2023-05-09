/**
 * @file cards_loader.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <functional>
#include <memory>
#include <sstream>
#include <string>

#include "../engine/player/cards/action_interface.hpp"
#include "../engine/player/cards/deck.hpp"
#include "../exceptions/exception.hpp"
#include "file_loader.hpp"

class CardLoader : public FileLoader {
public:
  /**
   * @brief Creates card savefile at given path with given filename
   *
   * @param path Path to directory where to save
   * @param filename Name of file to be created
   * @param card Card to save
   *
   * @throws FileWriteException If write fails
   */
  void save(const std::string &path, const std::string &filename,
            const std::shared_ptr<CardInterface> &card) const;

  /**
   * @brief Loads card from given file at given path
   *
   * @param path Path to directory where savefile is located
   * @param filename Name of file to be read
   * @param game Interface for Actions
   * @return std::shared_ptr<CardInterface> Loaded card
   * @throws CorruptedFileException If file is in unexpected state
   */
  std::shared_ptr<CardInterface> load(const std::string &path,
                                      const std::string &filename,
                                      GameInterface &game) const;

private:
  /**
   * @brief Creates Action based on given char(ActionType)
   *
   * @param type Char that will be translated to ActionType
   * @param value Value of action to be created
   * @param game Interface for Action to have handler
   *
   * @return std::shared_ptr<ActionInterface> Created Action
   * @throws IllegalArgument If unexpected char is given
   */
  std::shared_ptr<ActionInterface> action_factory(char type, size_t value,
                                                  GameInterface &game) const;
};

class DeckLoader : public FileLoader {
public:
  /**
   * @brief Creates deck savefile with given name at given path
   *
   * @param path Path to directory where to save
   * @param filename Name of file to be created
   * @param deck Deck to save
   *
   * @throws FileWriteException If read fails
   */
  void save(const std::string &path, const std::string &filename,
            const Deck &deck) const;

  /**
   * @brief Loads deck from given file at given path
   *
   * @param path Path to directory where savefile is located
   * @param filename Name of savefile to be read
   * @param game Interface for Cards->Actions
   * @return Deck Loaded Deck
   * @throws FileReadException If read fails
   */
  Deck load(const std::string &path, const std::string &filename,
            GameInterface &game) const;

private:
  /**
   * @brief Load given amount of cards through callback function
   *
   * @param file From where
   * @param path Path to save directory
   * @param amount How many cards to load
   * @param c_loader Object capable of loading cards
   * @param game Interface for Actions
   * @param callback Function loading cards into deck (somwhere)
   *
   * @throws FileReadException If read fails
   * @throws CorruptedFileException If file is in unexpected state
   */
  void load_cards(
      FILE *file, const std::string &path, size_t amount,
      const CardLoader &c_loader, GameInterface &game,
      std::function<void(std::shared_ptr<CardInterface>)> callback) const;

  /**
   * @brief Create savefiles for given cards at given path
   *
   * @tparam Container STL container<CardInterface>
   * @param file Where to save
   * @param path Path to save directory
   * @param filename Savefile postfix
   * @param container Container of Cards to be saved
   * @param prefix Prefix for each savefile
   * @param c_loader Object capable of saving CardInterface
   *
   * @throws FileReadException If read fails
   * @throws CorruptedFileException If file is in unexpected state
   */
  template <typename Container>
  void save_cards(FILE *file, const std::string &path,
                  const std::string &filename, const Container &container,
                  char prefix, const CardLoader &c_loader) const {
    size_t index{0};
    for (const auto &c : container) {
      std::stringstream c_filename_ss;
      c_filename_ss << prefix << "_" << index << "_" << filename;
      std::string c_filename{c_filename_ss.str()};
      c_loader.save(path, c_filename, c);
      write_string(file, c_filename);
      ++index;
    }
  }
};
