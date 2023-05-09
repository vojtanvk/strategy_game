/**
 * @file colour.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-06-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "colour.hpp"
#include "exceptions/exception.hpp"

std::string to_code_colour_front(Colour colour) {
  switch (colour) {
  case Colour::cyan:
    return "\u001b[36m";
  case Colour::green:
    return "\u001b[32m";
  case Colour::magenta:
    return "\u001b[35m";
  case Colour::red:
    return "\u001b[31m";
  case Colour::yellow:
    return "\u001b[33m";
  case Colour::black:
    return "\u001b[30m";
  case Colour::white:
    return "\u001b[37m";
  default:
    throw IllegalArgumentException("Unknown colour type");
  }
}

std::string to_code_colour_back(Colour colour) {
  switch (colour) {
  case Colour::cyan:
    return "\u001b[46m";
  case Colour::green:
    return "\u001b[42m";
  case Colour::magenta:
    return "\u001b[45m";
  case Colour::red:
    return "\u001b[41m";
  case Colour::yellow:
    return "\u001b[43m";
  case Colour::black:
    return "\u001b[40m";
  case Colour::white:
    return "\u001b[47m";
  default:
    throw IllegalArgumentException("Unknown colour type");
  }
}

std::string name_colour(Colour colour) {
  switch (colour) {
  case Colour::cyan:
    return "Cyan";
  case Colour::green:
    return "Green";
  case Colour::magenta:
    return "Magenta";
  case Colour::red:
    return "Red";
  case Colour::yellow:
    return "Yellow";
  case Colour::black:
    return "Black";
  case Colour::white:
    return "White";
  default:
    throw IllegalArgumentException("Unknown colour type");
  }
}

Colour char_to_colour(char colour) {
  switch (colour) {
  case 'c':
    return Colour::cyan;
  case 'g':
    return Colour::green;
  case 'm':
    return Colour::magenta;
  case 'r':
    return Colour::red;
  case 'y':
    return Colour::yellow;
  case 'b':
    return Colour::black;
  case 'w':
    return Colour::white;
  default:
    throw IllegalArgumentException("Unknown colour type");
  }
}

char to_char(Colour colour) {
  switch (colour) {
  case Colour::cyan:
    return 'c';
  case Colour::green:
    return 'g';
  case Colour::magenta:
    return 'm';
  case Colour::red:
    return 'r';
  case Colour::yellow:
    return 'y';
  case Colour::black:
    return 'b';
  case Colour::white:
    return 'w';
  default:
    throw IllegalArgumentException("Unknown colour type");
  }
}

std::vector<Colour> list_colours() {
  return {Colour::black, Colour::cyan,   Colour::green, Colour::magenta,
          Colour::red,   Colour::yellow, Colour::white};
}
std::string reset_colour() { return "\u001b[0m"; }