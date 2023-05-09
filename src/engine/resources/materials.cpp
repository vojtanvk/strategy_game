#include "../../exceptions/exception.hpp"
#include "materials.hpp"

std::string to_string(Materials mat) {
  switch (mat) {
  case Materials::wood:
    return "Wood";
  case Materials::stone:
    return "Stone";
  default:
    throw IllegalArgumentException("Unknown type");
  }
}

char to_char(Materials mat) {
  switch (mat) {
  case Materials::wood:
    return 'w';
  case Materials::stone:
    return 's';
  default:
    throw IllegalArgumentException("Unknown type");
  }
}

Materials char_to_material(char type) {
  switch (type) {
  case 'w':
    return Materials::wood;
  case 's':
    return Materials::stone;
  default:
    throw IllegalArgumentException("Unknown type");
  }
}