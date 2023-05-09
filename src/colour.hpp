/**
 * @file colour.hpp
 * @author novakvo8 (novakvo8@fit.cvut.cz)
 * @brief
 * @version 0.1
 * @date 2022-05-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <string>
#include <vector>

enum class Colour { red, green, yellow, magenta, cyan, black, white };

/**
 * @brief Get code for letter colour
 *
 * @param colour Colour to translate
 *
 * @return std::string ANSII escape sequence
 */
std::string to_code_colour_front(Colour colour);

/**
 * @brief Get code for terminal colour
 *
 * @param colour Colour to translate
 *
 * @return std::string ANSII escape sequence
 */
std::string to_code_colour_back(Colour colour);

/**
 * @brief Get colour name
 *
 * @param colour Colour to translate
 *
 * @return std::string
 * @throws IllegalArgumentException If unknown Colour is given
 */
std::string name_colour(Colour colour);

/**
 * @brief Get Colour by char
 *
 * @param colour Colour to translate
 *
 * @return Colour
 * @throws IllegalArgumentException If unknown char is given
 */
Colour char_to_colour(char colour);

/**
 * @brief Get chat by colour
 *
 * @param colour Colour to translate
 *
 * @return std::string ANSII escape sequence
 * @throws IllegalArgumentException If unknown Colour is given
 */
char to_char(Colour colour);

/**
 * @brief Lists all Colours
 *
 * @return std::vector<Colour>
 */
std::vector<Colour> list_colours();

/**
 * @brief Returns ANSII sequence for reseting ANSII codes
 *
 * @return std::string ANSII escape sequence
 */
std::string reset_colour();