/**
 * @file exception.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "exception.hpp"

Exception::Exception(size_t code, std::string message)
    : code(code), message(message) {}

size_t Exception::get_code() const { return code; }
std::string Exception::get_message() const { return message; }

IllegalArgumentException::IllegalArgumentException(std::string message)
    : Exception(11, message) {}

IllegalStateException::IllegalStateException(std::string message)
    : Exception(17, message) {}

FileWriteException::FileWriteException()
    : IllegalStateException("File couldn't be written") {}

FileReadException::FileReadException()
    : IllegalStateException("File couldn't be read") {}

CorruptedFileException::CorruptedFileException()
    : IllegalArgumentException("Bad or corrupted file") {}

InputException::InputException()
    : IllegalStateException("Bad or prematurely ended input") {}