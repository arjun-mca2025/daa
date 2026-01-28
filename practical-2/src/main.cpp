// External dependencies
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// Internal dependencies
#include <structs/Record.hpp>
#include <sorting/insertion_sort.hpp>
#include <io.hpp>

/* -------------------------------------------------------------------------- */
/*                            Forward declarations                            */
/* -------------------------------------------------------------------------- */

bool compareByTemperature(const Record *rec1, const Record *rec2);

/* -------------------------------------------------------------------------- */
/*                                  Main Body                                 */
/* -------------------------------------------------------------------------- */

int main()
{

    /* ---------------------------- Read Input file  ---------------------------- */

    std::string path = "./input/data.csv"; // path relative to the CWD
    auto &records = read(path);

    Metadata metadata = insertionSortWithMetadata(records, compareByTemperature);

    /* ------------------------ Write the sorted records ------------------------ */

    write(records, "./output/data.csv");

    /* --------------------------- Write the metadata --------------------------- */

    std::ofstream out("./output/report.txt");

    out << "Comparisons: " << metadata.comparisons << "\n";
    out << "Assignments: " << metadata.assignments << "\n";

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                            Comparator function                             */
/* -------------------------------------------------------------------------- */

bool compareByTemperature(const Record *rec1, const Record *rec2)
{
    // true means rec2 should come first, false means rec1 should come first
    return !(rec1->averageTemp < rec2->averageTemp); // rec1 will come first in the sorted array if its temperature is lower
}