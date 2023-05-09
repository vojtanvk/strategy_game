/**
 * @file file_loader.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <map>
#include <string>

#include "../engine/player/units/blueprint.hpp"
#include "../engine/resources/materials.hpp"
#include "../engine/win_con.hpp"
#include "../exceptions/exception.hpp"

class FileLoader {
public:
protected:
  /**
   * @brief Writes string as expected by program into given file (size of
   * string, string's chars)
   *
   * @param file Where to write
   * @param line What to write
   *
   * @throws FileWriteException If write fails
   */
  void write_string(FILE *file, const std::string &line) const;

  /**
   * @brief Writes materials as expected by program into given file
   * ([mat:count])
   *
   * @param file Where to write
   * @param materials What to write
   *
   * @throws FileWriteException If write fails
   */
  void write_material(FILE *file,
                      const std::map<Materials, size_t> &materials) const;

  /**
   * @brief Writes blueprint as expected by program into given file
   *
   * @param file Where to write
   * @param bp What to write
   *
   * @throws FileWriteException If write fails
   */
  void write_blueprint(FILE *file, const Blueprint &bp) const;

  /**
   * @brief Writes win condition as expected by program into given file
   *
   * @param file Where to write
   * @param condition What to write
   *
   * @throws FileWriteException If write fails
   */
  void write_win_con(FILE *file, const WinCon &condition) const;

  /**
   * @brief Reads string from file if written by write_string method
   *
   * @return std::string Read string
   * @throws FileReadException If read fails
   */
  std::string read_string(FILE *) const;

  /**
   * @brief Write single simple object
   *
   * @tparam Type To be written
   * @param file Where to write
   * @param to_write What to write
   *
   * @throws FileWriteException If write fails
   */
  template <typename Type> void write_single(FILE *file, Type to_write) const {
    if (fwrite(&to_write, sizeof(to_write), 1, file) != 1) {
      throw FileWriteException();
    }
  }

  /**
   * @brief Read materials from file if written by write_material method
   *
   * @param file From where
   *
   * @return std::map<Materials, size_t> Read materials
   * @throws FileReadException If read fails
   */
  std::map<Materials, size_t> read_material(FILE *file) const;

  /**
   * @brief Read blueprint from file if written by write_blueprint method
   *
   * @param file From where
   *
   * @return Blueprint Read blueprint
   * @throws FileReadException If read fails
   */
  Blueprint read_blueprint(FILE *file) const;

  /**
   * @brief Read condition from file if written by write_win_con method
   *
   * @param file From where
   *
   * @return WinCon Read condition
   * @throws FileReadException If read fails
   */
  WinCon read_win_con(FILE *file) const;

  /**
   * @brief Read single simple object of given type
   *
   * @tparam Type To be read
   * @param file From where
   * @return Type Read object
   * @throws FileReadException If read fails
   */
  template <typename Type> Type read_single(FILE *file) const {
    Type out;
    if (fread(&out, sizeof(out), 1, file) != 1) {
      throw FileReadException();
    }
    return out;
  }

  /**
   * @brief Calls read_single(FILE*) and checks result
   *
   * @tparam Type To be read
   * @param file From where
   * @param check Excpected object
   * @return Type Read obejct
   * @throws CorruptedFileException If result and check don't match
   */
  template <typename Type> Type read_single(FILE *file, Type check) const {
    Type out{read_single<Type>(file)};
    if (out != check) {
      throw CorruptedFileException();
    }
    return out;
  }
};