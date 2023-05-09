
#include "../../../exceptions/exception.hpp"
#include "unit_type.hpp"

char to_char(UnitType type) {
  switch (type) {
  case UnitType::worker:
    return 'w';
  case UnitType::building:
    return 'b';
  default:
    throw IllegalArgumentException("Unknown type");
  }
}

UnitType char_to_unit(char type) {
  switch (type) {
  case 'w':
    return UnitType::worker;
  case 'b':
    return UnitType::building;
  default:
    throw IllegalArgumentException("Unknown unit type: " + type);
  }
}

std::string to_string(UnitType type) {
  switch (type) {
  case UnitType::building:
    return "building";
  case UnitType::worker:
    return "worker";
  default:
    throw IllegalArgumentException("Unknown type");
  }
}