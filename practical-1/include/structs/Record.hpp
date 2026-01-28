/**
 * @file Record.hpp
 * @author Arjun Singh
 * @brief Definition of the Record struct
 *
 */

#ifndef RECORD_H
#define RECORD_H

// External dependencies
#include <string>

/**
 * @brief A Record just holds the name and age together
 *
 * This probably has a size of 36 bytes, most of which is because of the string
 *
 */
struct Record
{
    std::string name; // 32 bytes most probably
    float age;        // 4 bytes
};

#endif