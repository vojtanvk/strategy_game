/**
 * @file movement.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "movement.hpp"

#include <iostream>

Movement::Movement(size_t value, GameInterface &game_interface)
    : Action(value, game_interface) {}

bool Movement::resolve() {

  auto &actor = *get_game_interface().get_active_player();
  const auto &map = get_game_interface().get_map();

  const auto viability = [&](const auto &unit) {
    return unit->can_move() &&
           !get_game_interface()
                .get_map()
                ->walkable_surroundings(unit->get_position())
                .empty();
  };

  std::vector<std::shared_ptr<UnitInterface>> vialable_units;
  std::copy_if(actor.get_units().begin(), actor.get_units().end(),
               std::back_inserter(vialable_units), viability);

  std::shared_ptr<UnitInterface> active_unit;
  if (!actor.get_api()->select_unit(vialable_units, active_unit)) {
    return false;
  }

  auto start = map->get_space(active_unit->get_position());
  start->remove_occupant();

  Coords current_position = start->get_pos();

  for (auto moves = get_value() + active_unit->get_move(); moves > 0; --moves) {
    int val = actor.get_api()->read_movement(
        start->get_pos(), current_position,
        map->walkable_surroundings(current_position),
        map->movable_area(current_position, moves));

    if (val == 1) {
      continue;
    } else if (val == 0) {
      break;
    } else {
      start->place_occupant(active_unit);
      return false;
    }
  }
  auto end = map->get_space(current_position);

  active_unit->set_position(current_position);
  end->place_occupant(active_unit);
  get_game_interface().handler_action_stack().push_back(
      std::make_shared<InverseMovement>(*start, *end));
  return true;
}

ActionType Movement::get_type() const { return ActionType::movement; }