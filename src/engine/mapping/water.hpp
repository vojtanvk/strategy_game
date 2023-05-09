/**
 * @file water.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "space.hpp"

class Water : public Space {
public:
  Water(const Coords &);
  /**
   * @return false
   */
  bool walkable() const override;
  /**
   * @return Materials::none
   */
  Materials get_material() const override;
  /**
   * @return Surface::water
   */
  Surface get_surface() const override;
};