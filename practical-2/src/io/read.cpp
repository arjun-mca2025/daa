// Header file to be (partially) implemented
#include <io.hpp>

// External dependencies
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

// Internal dependencies
#include <structs/Record.hpp>

/* -------------------------------------------------------------------------- */
/*                                  Constants                                 */
/* -------------------------------------------------------------------------- */
#define TOTAL_RECORDS 16743

/* -------------------------------------------------------------------------- */
/*                            Forward declarations                            */
/* -------------------------------------------------------------------------- */

/**
 * @brief Parse the given string into a const pointer to a Record on the heap
 *
 * The Record itself is modifiable, but the pointer to the Record cannot be modified.
 *
 * @param line The string to be parsed
 * @return const Record* Pointer to the parsed Record on the heap
 */
const Record *_parseRecord(const std::string &line);

/* -------------------------------------------------------------------------- */
/*                                  Main Body                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Read a text file's records and store them in the heap as a vector of const pointers (to other locations in the heap)
 *
 * @param relativePath Path to the file (relative to the CWD)
 * @return std::vector<const Record *> & Reference to a vector of const Record pointers
 */
std::vector<const Record *> &read(const std::string &relativePath)
{
    std::vector<const Record *> *records = new std::vector<const Record *>();

    std::ifstream file(relativePath);
    if (!file.is_open())
    {
        std::cerr << "The given path does not exist, so cannot read anything." << std::endl;
        return *(new std::vector<const Record *>()); // return a reference to an empty vector in the heap; there's probably a better way to do this
    }

    std::string line;         // temporary variable to hold a line
    std::getline(file, line); // skip the first line because it contains the header
    while (std::getline(file, line))
    {
        records->push_back(_parseRecord(line));
    }

    auto &recordsRef = *records;
    return recordsRef;
}

/**
 * @brief Generate n random samples from the given vector of Record pointers
 *
 * @param records Vector of Record pointers on the heap
 * @param n Number of samples to return
 * @return std::vector<const Record *>& Sample of size n from the given records
 */
std::vector<const Record *> &sampleN(std::vector<const Record *> &records, int n)
{
    std::vector<const Record *> *sample = new std::vector<const Record *>();
    for (int i = 0; i < n; i++)
    {
        int randomIndex = rand() % TOTAL_RECORDS;
        sample->push_back(records[randomIndex]);
    }

    auto &sampleRef = *sample;
    return sampleRef;
}

/* -------------------------------------------------------------------------- */
/*                            Utility function(s)                             */
/* -------------------------------------------------------------------------- */

const Record *_parseRecord(const std::string &line)
{
    std::vector<std::string> tokens;
    std::string current;
    bool inQuotes = false;

    for (char c : line)
    {
        if (c == '"')
        {
            inQuotes = !inQuotes; // toggle state
        }
        else if (c == ',' && !inQuotes)
        {
            tokens.push_back(current);
            current.clear();
        }
        else
        {
            current += c;
        }
    }
    // Last field
    tokens.push_back(current);

    return new Record{
        stof(tokens[0]),
        tokens[1],
        stoi(tokens[2]),
        stoi(tokens[3]),
        stoi(tokens[4]),
        tokens[5],
        tokens[6],
        tokens[7],
        tokens[8],
        stof(tokens[9]),
        stof(tokens[10]),
        stof(tokens[11]),
        stof(tokens[12]),
        stof(tokens[13])};
}