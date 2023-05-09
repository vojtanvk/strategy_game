/**
 * @file my_file.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../exceptions/exception.hpp"
#include "my_file.hpp"

MyFile::MyFile(const std::string &filename, const std::string &modes)
    : file(fopen(filename.data(), modes.data())) {
  if (!file) {
    throw IllegalArgumentException("Unable to open file: " + filename);
  }
}

MyFile::~MyFile() {
  if (file) {
    fclose(file);
  }
}

MyFile::operator FILE *() const { return file; }