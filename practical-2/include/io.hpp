/**
 * @file io.hpp
 * @author Arjun Singh
 * @brief The header file that defines an interface to read the input data into an array of in-memory structs
 *
 */

#ifndef IO_HPP
#define IO_HPP

// External dependencies
#include <string>
#include <vector>

// Internal dependencies
#include <structs/Record.hpp>
#include <structs/Metadata.hpp>

/**
 * @brief Read a text file's records, store them in the heap as an array of pointers (to other locations in the heap)
 *
 * @param relativePath Path to the file
 * @return std::vector<const Record *>& Reference to a vector of const Record pointers on the heap
 */
std::vector<const Record *> &read(const std::string &relativePath);

/**
 * @brief Write a vector of const Record pointers to the given file path
 *
 * @param records Vector of const Record pointers
 * @param relativePath Output file path relative to CWD
 */
void write(const std::vector<const Record *> &records, const std::string &relativePath);

/**
 * @brief Write metadata to a file in append mode
 *
 * @param meta The metadata struct to be written to file
 * @param relativePath Relative path of the file
 */
void writeMetadata(Metadata meta, const std::string &relativePath);

/**
 * @brief Generate n random samples from the given vector of Record pointers
 *
 * @param records Vector of Record pointers on the heap
 * @param n Number of samples to return
 * @return std::vector<const Record *>& Sample of size n from the given records
 */
std::vector<const Record *> &sampleN(std::vector<const Record *> &records, int n);

#endif