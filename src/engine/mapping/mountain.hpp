/**
 * @file mountain.hpp
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

class Mountain : public Space {
public:
  Mountain(const Coords &);
  /**
   * @return false
   */
  bool walkable() const override;
  /**
   * @return Materials::stone
   */
  Materials get_material() const override;
  /**
   * @return Surface::mountain
   */
  Surface get_surface() const override;
};