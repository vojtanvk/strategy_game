/**
 * @file forest.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "space.hpp"

class Forest : public Space {
public:
  Forest(const Coords &);
  /**
   * @return false
   */
  bool walkable() const override;
  /**
   * @return Materials::wood
   */
  Materials get_material() const override;
  /**
   * @return Surface::forest
   */
  Surface get_surface() const override;
};
