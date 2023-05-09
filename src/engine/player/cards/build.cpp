/**
 * @file build.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../../exceptions/exception.hpp"
#include "../units/units.hpp"
#include "build.hpp"

Build::Build(size_t value, GameInterface &game_interface)
    : Action(value, game_interface) {}

bool Build::resolve() {
  auto actor = get_game_interface().get_active_player();
  const auto &map = get_game_interface().get_map();

  const auto viability = [&](const auto &unit) {
    return unit->can_build() &&
           !map->walkable_surroundings(unit->get_position()).empty();
  };

  std::vector<std::shared_ptr<UnitInterface>> viable_units;
  std::copy_if(actor->get_units().begin(), actor->get_units().end(),
               std::back_inserter(viable_units), viability);

  std::shared_ptr<UnitInterface> active_unit;

  Blueprint to_build;
  Coords where;
  if (!actor->get_api()->select_unit(viable_units, active_unit)) {
    return false;
  }
  const auto &id_list{active_unit->get_build_list()};
  std::vector<Blueprint> build_list;
  std::for_each(id_list.begin(), id_list.end(), [&](const auto &id) {
    build_list.push_back(get_game_interface().get_blueprint(id));
  });
  int val = actor->get_api()->build(
      build_list, active_unit->get_position(),
      map->walkable_surroundings(active_unit->get_position()),
      actor->get_resources(), to_build, where);

  if (val == -1) {
    return false;
  } else if (val == 0) {
    return true;
  }

  std::shared_ptr<UnitInterface> n_unit;
  switch (to_build.get_type()) {
  case UnitType::building:
    n_unit = std::make_shared<Building>(*actor, where, to_build);
    break;
  case UnitType::worker:
    n_unit = std::make_shared<Worker>(*actor, where, to_build);
    break;
  default:
    throw IllegalArgumentException("Unknown unit type");
  }
  actor->pay_cost(to_build.get_cost());
  get_game_interface().add_unit(n_unit);
  get_game_interface().handler_action_stack().push_back(
      std::make_shared<InverseBuild>(to_build.get_cost(),
                                     *map->get_space(where)));
  return true;
}

ActionType Build::get_type() const { return ActionType::build; }