/**
 * @file harvest.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../../exceptions/exception.hpp"
#include "harvest.hpp"

Harvest::Harvest(size_t value, GameInterface &game_interface)
    : Action(value, game_interface) {}

bool Harvest::resolve() {

  auto &actor = *get_game_interface().get_active_player();
  auto &api = *actor.get_api();
  const auto &map = get_game_interface().get_map();

  const auto &viability = [&](const auto &unit) {
    return unit->can_harvest() && !map->harvest(unit->get_position()).empty();
  };

  // required negated viability
  // auto viable_units = actor.get_units();
  // auto er_from = remove_if(viable_units.begin(), viable_units.end(),
  // viability); viable_units.erase(er_from, viable_units.end());

  // decltype(actor.get_units()) viable_units{};
  std::vector<std::shared_ptr<UnitInterface>> viable_units;
  std::copy_if(actor.get_units().begin(), actor.get_units().end(),
               std::back_inserter(viable_units), viability);
  // for (const auto &u : actor.get_units()) {
  //   if ((u->get_type() == UnitType::worker &&
  //        !get_game_interface().get_map()->harvest(u->get_position()).empty())
  //        ||
  //       u->gather() != Materials::none) {
  //     viable_units.push_back(u);
  //   }
  // }

  std::shared_ptr<UnitInterface> active_unit;
  if (!api.select_unit(viable_units, active_unit)) {
    return false;
  }

  Materials harvested;
  std::vector<Materials> viable_to_harvest;

  const auto &harvest_list = active_unit->get_harvest_list();

  if (active_unit->can_harvest_anywhere()) {
    for (const auto &m : harvest_list) {
      viable_to_harvest.push_back(m.first);
    }

    // actor.add_material(active_unit->gather(), get_value());
    // get_game_interface().handler_action_stack().push_back(
    //     std::make_shared<InverseHarvest>(active_unit->gather(), get_value(),
    //                                      actor));
    // return true;
  } else {
    viable_to_harvest = map->harvest(active_unit->get_position());
  }
  if (!api.choose_material(viable_to_harvest, harvested)) {
    return false;
  }

  size_t harvest_bonus =
      harvest_list.count(harvested) ? harvest_list.at(harvested) : 0;

  actor.add_material(harvested, get_value() + harvest_bonus);
  get_game_interface().handler_action_stack().push_back(
      std::make_shared<InverseHarvest>(harvested, get_value() + harvest_bonus,
                                       actor));
  return true;
}

ActionType Harvest::get_type() const { return ActionType::harvest; }