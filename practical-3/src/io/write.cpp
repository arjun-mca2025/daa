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
 * @brief Convert a Record pointer to a CSV line string
 *
 * @param record Pointer to the Record
 * @return std::string
 */
std::string _recordToLine(const Record *record);

/* -------------------------------------------------------------------------- */
/*                                  Main Body                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Write a vector of const Record pointers to the given file path
 *
 * @param records Vector of const Record pointers
 * @param relativePath Output file path relative to CWD
 */
void write(const std::vector<const Record *> &records, const std::string &relativePath)
{
    std::ofstream file(relativePath);
    if (!file.is_open())
    {
        std::cerr << "Cannot open file for writing: " << relativePath << std::endl;
        return;
    }

    for (const Record *r : records)
    {
        file << _recordToLine(r) << "\n";
    }
}

/**
 * @brief Convert a record to a string representation
 *
 * @param record Reference to the record
 * @return std::string String representation of the record
 */
std::string convertRecordToString(const Record &record)
{
    std::string tupleString = "";
    tupleString += "(" + record.name + ", " + std::to_string(record.age) + ")";
    return tupleString;
}

/* -------------------------------------------------------------------------- */
/*                            Utility function(s)                             */
/* -------------------------------------------------------------------------- */

std::string _recordToLine(const Record *record)
{
    return record->name + "," + std::to_string(record->age);
}
