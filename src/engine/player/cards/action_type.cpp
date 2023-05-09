#include "../../../exceptions/exception.hpp"
#include "action_type.hpp"

std::string to_string(ActionType action) {
  switch (action) {
  case ActionType::build:
    return "build";
  case ActionType::draw:
    return "draw";
  case ActionType::harvest:
    return "harvest";
  case ActionType::movement:
    return "movement";
  default:
    throw IllegalArgumentException("Unknown action");
  }
}

char to_char(ActionType action) {
  switch (action) {
  case ActionType::build:
    return 'b';
  case ActionType::draw:
    return 'd';
  case ActionType::harvest:
    return 'h';
  case ActionType::movement:
    return 'm';
  default:
    throw IllegalArgumentException("Unknown action");
  }
}

ActionType char_to_action(char type) {
  switch (type) {
  case 'B':
  case 'b':
    return ActionType::build;
  case 'D':
  case 'd':
    return ActionType::draw;
  case 'H':
  case 'h':
    return ActionType::harvest;
  case 'M':
  case 'm':
    return ActionType::movement;
  default:
    throw IllegalArgumentException("Unknown action");
  }
}