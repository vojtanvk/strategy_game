/**
 * @file my_file.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>

/**
 * @brief Struct for holding FILE * closing it on upon destruction
 *
 */
struct MyFile {
  /**
   * @brief Construct a new My File object
   *
   * @param filename Name of file to open
   * @param mode Mode of opening
   *
   * @throws IllegalArgumentException If file cannot be opened
   */
  MyFile(const std::string &filename, const std::string &mode);

  /**
   * @brief Closes given file if present
   *
   */
  ~MyFile();

  /**
   * @brief FILE * cast for easier use
   *
   * @return FILE *
   */
  operator FILE *() const;

private:
  FILE *file;
};