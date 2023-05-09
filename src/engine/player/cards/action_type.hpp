/**
 * @file action_type.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <string>

enum class ActionType { build, draw, harvest, movement };

/**
 * @brief Names ActionType
 *
 * @param type To translate
 * @return std::string Name of ActionType
 * @throws IllegalArgumentException If unknown type is given
 */
std::string to_string(ActionType type);

/**
 * @brief Translate ActionType to char
 *
 * @param type To translate
 * @return char
 * @throws IllegalArgumentException If unknown type is given
 */
char to_char(ActionType type);

/**
 * @brief Translate char to ActionType
 *
 * @param type To translate
 * @return ActionType
 * @throws IllegalArgumentException If unknown type is given
 */
ActionType char_to_action(char type);