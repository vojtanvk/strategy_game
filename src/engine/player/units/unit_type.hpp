/**
 * @file unit_type.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../../exceptions/exception.hpp"

enum class UnitType { worker, building };

/**
 * @brief Translate UnitType to char
 *
 * @param type To translate
 * @return char
 * @throws IllegalArgumentException If unknown type is given
 */
char to_char(UnitType type);

/**
 * @brief Translate char to UnitType
 *
 * @param type To translate
 * @return UnitType
 * @throws IllegalArgumentException If unknown type is given
 */
UnitType char_to_unit(char type);
/**
 * @brief Translate names UnitType
 *
 * @param type To translate
 * @return std::srting Name of UnitType
 * @throws IllegalArgumentException If unknown type is given
 */
std::string to_string(UnitType type);