/**
 * @file surface.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>
#include <vector>

enum class Surface { undefined, plains, forest, mountain, water };

/**
 * @brief Get char by Surface
 *
 * @param surface To translate
 * @return char
 * @throws IllegalArgumentException If unknown surface is given
 */
char to_char(Surface surface);

/**
 * @brief Get name of Surface
 *
 * @param surface To translate
 * @return std::string
 * @throws IllegalArgumentException If unknown surface is given
 */
std::string to_string(Surface surface);

/**
 * @brief Get Surface by char
 *
 * @param surface To translate
 * @return cSurface
 * @throws IllegalArgumentException If unknown surface is given
 */
Surface char_to_surface(char surface);

/**
 * @brief Lists all known Surfaces
 *
 * @return std::vector<Surface>
 */
std::vector<Surface> list_surface();