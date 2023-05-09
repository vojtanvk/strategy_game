/**
 * @file file_loader.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <algorithm>

#include "../exceptions/exception.hpp"
#include "file_loader.hpp"

void FileLoader::write_string(FILE *file, const std::string &to_write) const {
  size_t s_size = to_write.size();
  if (fwrite(&s_size, sizeof(s_size), 1, file) != 1 ||
      fwrite(to_write.data(), sizeof(char), to_write.size(), file) !=
          to_write.size()) {
    throw FileWriteException();
  }
}

std::string FileLoader::read_string(FILE *file) const {
  size_t s_size;
  if (fread(&s_size, sizeof(s_size), 1, file) != 1) {
    throw FileReadException();
  }
  std::string out(s_size, ' ');
  if (fread(out.data(), sizeof(char), s_size, file) != s_size) {
    throw FileReadException();
  }
  return out;
}

void FileLoader::write_material(
    FILE *file, const std::map<Materials, size_t> &material) const {
  write_single(file, '[');
  std::for_each(material.begin(), material.end(), [&](const auto &mat) {
    write_single(file, to_char(mat.first));
    write_single(file, mat.second);
  });
  write_single(file, ']');
}

void FileLoader::write_blueprint(FILE *file, const Blueprint &bp) const {
  write_single(file, 'i');
  write_single(file, bp.get_id());
  write_single(file, 't');
  write_single(file, to_char(bp.get_type()));
  write_single(file, 'p');
  write_single(file, bp.get_points());
  write_single(file, 'm');
  write_single(file, bp.get_move());

  write_single(file, 'c');
  write_material(file, bp.get_cost());

  write_single(file, 'h');
  write_material(file, bp.get_harvest_list());

  write_single(file, 'l');
  write_single(file, '[');
  const auto &id_list{bp.get_build_list()};
  write_single(file, id_list.size());

  std::for_each(id_list.begin(), id_list.end(),
                [&](const auto &id) { write_single(file, id); });

  write_single(file, ']');
}

void FileLoader::write_win_con(FILE *file, const WinCon &condition) const {

  write_single(file, 'p');
  write_single(file, condition.get_points());

  write_single(file, 'u');
  write_single(file, condition.get_unit_count());

  write_single(file, 'm');
  write_material(file, condition.get_materials());
}

std::map<Materials, size_t> FileLoader::read_material(FILE *file) const {
  std::map<Materials, size_t> out;
  char mat{read_single(file, '[')};
  while ((mat = read_single<char>(file)) != ']') {
    out[char_to_material(mat)] = read_single<size_t>(file);
  }
  return out;
}

Blueprint FileLoader::read_blueprint(FILE *file) const {
  Blueprint bp;
  read_single(file, 'i');
  bp.set_id(read_single<size_t>(file));
  read_single(file, 't');
  bp.set_type(char_to_unit(read_single<char>(file)));
  read_single(file, 'p');
  bp.set_points(read_single<size_t>(file));
  read_single(file, 'm');
  bp.set_move(read_single<size_t>(file));

  read_single(file, 'c');
  bp.set_cost(read_material(file));
  read_single(file, 'h');
  bp.set_harvest_list(read_material(file));

  read_single(file, 'l');
  read_single(file, '[');

  for (size_t id_count{read_single<size_t>(file)}; id_count > 0; --id_count) {
    bp.add_build_list(read_single<size_t>(file));
  }
  read_single(file, ']');
  return bp;
}

WinCon FileLoader::read_win_con(FILE *file) const {
  WinCon condition;
  read_single(file, 'p');
  condition.set_points(read_single<size_t>(file));
  read_single(file, 'u');
  condition.set_unit_count(read_single<size_t>(file));
  read_single(file, 'm');
  condition.set_materials(read_material(file));
  return condition;
}