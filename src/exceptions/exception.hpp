/**
 * @file exception.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>

class Exception {
public:
  Exception(size_t, std::string);
  /**
   * @brief Get the code of exception
   *
   * @return size_t
   */
  size_t get_code() const;

  /**
   * @brief Get the message of exception
   *
   * @return std::string
   */
  std::string get_message() const;

private:
  size_t code;
  std::string message;
};

/**
 * @brief Thrown when program gets into an unexpected state
 *
 */
struct IllegalStateException : public Exception {
  IllegalStateException(std::string);
};

/**
 * @brief Throw when method recieves invalid argument
 *
 */
struct IllegalArgumentException : public Exception {
  IllegalArgumentException(std::string);
};

/**
 * @brief Thrown when program tries to write to a file unsuccessfully
 *
 */
struct FileWriteException : public IllegalStateException {
  FileWriteException();
};

/**
 * @brief Thrown when program tries to read from a file unsuccessfully
 *
 */
struct FileReadException : public IllegalStateException {
  FileReadException();
};

/**
 * @brief Thrown when file doesn't contain expected data
 *
 */
struct CorruptedFileException : public IllegalArgumentException {
  CorruptedFileException();
};

/**
 * @brief Thrown on input fail
 *
 */
struct InputException : public IllegalStateException {
  InputException();
};