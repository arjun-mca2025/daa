// Header file to be (partially) implemented
#include <io.hpp>

// External dependencies
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

// Internal dependencies
#include <structs/Record.hpp>

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

    std::string line; // temporary variable to hold a line
    while (std::getline(file, line))
    {
        records->push_back(_parseRecord(line));
    }

    auto &recordsRef = *records;
    return recordsRef;
}

/* -------------------------------------------------------------------------- */
/*                            Utility function(s)                             */
/* -------------------------------------------------------------------------- */

const Record *_parseRecord(const std::string &line)
{
    int nameStart = 0;
    int nameEnd = line.find(',', nameStart);

    std::string name = line.substr(nameStart, nameEnd - nameStart);

    int ageStart = nameEnd + 1;
    std::string ageToken = line.substr(ageStart);
    float age = std::stof(ageToken);

    Record *record = new Record{name, age};

    return record;
}