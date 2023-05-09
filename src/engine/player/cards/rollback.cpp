/**
 * @file rollback.cpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "rollback.hpp"

#include <iostream>

void ActionStack::push_back(std::shared_ptr<InverseAction> action) {
  stack.emplace_back(action);
}

void ActionStack::rollback() {
  while (!stack.empty()) {
    stack.front()->rollback();
    stack.pop_front();
  }
}

void ActionStack::clear() { stack.clear(); }

InverseBuild::InverseBuild(const std::map<Materials, size_t> cost,
                           SpaceInterface &built)
    : cost(cost), built(built) {}

void InverseBuild::rollback() {
  auto building = built.get_occupant();
  auto &builder = building->get_owner();
  for (const auto &mat : cost) {
    builder.add_material(mat.first, mat.second);
  }
  built.remove_occupant();
  auto &units = builder.handle_units();
  for (auto it = units.begin(); it != units.end(); it++) {
    if (*it == building) {
      units.erase(it);
      return;
    }
  }
}

InverseHarvest::InverseHarvest(Materials harvested, size_t amount,
                               PlayerInterface &actor)
    : harvested(harvested), amount(amount), actor(actor) {}

void InverseHarvest::rollback() { actor.pay_cost({{harvested, amount}}); }

InverseMovement::InverseMovement(SpaceInterface &start, SpaceInterface &end)
    : start(start), end(end) {}

void InverseMovement::rollback() {
  auto occupant = end.get_occupant();
  end.remove_occupant();
  start.place_occupant(occupant);
  occupant->set_position(start.get_pos());
}