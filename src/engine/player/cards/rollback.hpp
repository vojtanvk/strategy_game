/**
 * @file rollback.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <list>
#include <map>
#include <memory>

class ActionStack;

#include "../../mapping/coords.hpp"
#include "../../resources/materials.hpp"

#include "../../mapping/space_interface.hpp"

class InverseAction {
public:
  virtual ~InverseAction() {}
  virtual void rollback() = 0;
};

class ActionStack {
public:
  void push_back(std::shared_ptr<InverseAction>);
  void rollback(); // TODO whole or single action
  void clear();

private:
  std::list<std::shared_ptr<InverseAction>> stack;
};

class InverseBuild : public InverseAction {
public:
  InverseBuild(const std::map<Materials, size_t>, SpaceInterface &);
  virtual ~InverseBuild() = default;

  void rollback() override;

private:
  std::map<Materials, size_t> cost;
  SpaceInterface &built;
};

class InverseMovement : public InverseAction {
public:
  InverseMovement(SpaceInterface &, SpaceInterface &);
  virtual ~InverseMovement() = default;

  void rollback() override;

private:
  SpaceInterface &start;
  SpaceInterface &end;
};

class InverseHarvest : public InverseAction {
public:
  InverseHarvest(Materials, size_t, PlayerInterface &);
  virtual ~InverseHarvest() = default;

  void rollback() override;

private:
  Materials harvested;
  size_t amount;
  PlayerInterface &actor;
};