/**
 * @file plains.hpp
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

class Plains : public Space {
public:
  Plains(const Coords &);
  /**
   * @brief Checks for unit
   *
   * @return true
   * @return false
   */
  bool walkable() const override;
  /**
   * @return Materials::none
   */
  Materials get_material() const override;
  /**
   * @return Surface::plains
   */
  Surface get_surface() const override;
};