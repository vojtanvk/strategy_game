/**
 * @file materials.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../../exceptions/exception.hpp"
#include <string>

enum class Materials { none, wood, stone };

/**
 * @brief Get name of given Material
 *
 * @param material Material to name
 * @return std::string Name of Material
 * @throws IllegalArgumentException If unexpected Material is given
 */
std::string to_string(Materials material);

/**
 * @brief Get char of given Material
 *
 * @param material Material to translate
 * @return char Char of Material
 * @throws IllegalArgumentException If unexpected Material is given
 */
char to_char(Materials material);

/**
 * @brief Get Material from given char
 *
 * @param material Char to translate
 * @return Material Type of Material
 * @throws IllegalArgumentException If unexpected char is given
 */
Materials char_to_material(char material);