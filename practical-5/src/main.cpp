// External dependencies
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// Internal dependencies
#include <structs/Record.hpp>
#include <sorting/randomized_quick_sort.hpp>
#include <io.hpp>

/* -------------------------------------------------------------------------- */
/*                            Forward declarations                            */
/* -------------------------------------------------------------------------- */

bool compareByAge(const Record *rec1, const Record *rec2);
bool compareByName(const Record *rec1, const Record *rec2);

/* -------------------------------------------------------------------------- */
/*                                  Main Body                                 */
/* -------------------------------------------------------------------------- */

int main()
{
    std::cout << "Enter 1 to run the program on example data or anything else to run it on the generated input: " << std::endl;
    int choice;
    std::cin >> choice;

    /* -------------------------------------------------------------------------- */
    /*                           Flow 1: On example data                          */
    /* -------------------------------------------------------------------------- */

    if (choice == 1)
    {
        std::vector<const Record *> *records = new std::vector<const Record *>();
        records->push_back(new Record{"Reeta", 18.5});
        records->push_back(new Record{"Geet", 18.3});
        records->push_back(new Record{"Reeta", 17.8});

        auto &recordsRef = *records;

        // Copy of the same records
        auto recordsCopy = *records;

        quickSort(recordsRef, compareByAge);
        std::cout << "-----------------------------" << "\n";
        for (const Record *rec : recordsRef)
        {
            std::cout << "After sorting on age: " << "\n";
            std::cout << convertRecordToString(*rec) << "\n";
        }

        quickSort(recordsCopy, compareByName);
        std::cout << "-----------------------------" << "\n";
        for (const Record *rec : recordsCopy)
        {
            std::cout << "After sorting on only name: " << "\n";
            std::cout << convertRecordToString(*rec) << "\n";
        }

        std::cout << "-----------------------------" << "\n";
        quickSort(recordsRef, compareByName);
        for (const Record *rec : recordsRef)
        {
            std::cout << "After sorting on both the fields: " << "\n";
            std::cout << convertRecordToString(*rec) << "\n";
        }

        return 1;
    }

    std::vector<Metadata> report{}; // 10-sized vector for keeping average Metadata for each size of n
    std::vector<Metadata> reportAgeOnly{};
    std::vector<Metadata> reportNameOnly{};

    /* -------------------------------------------------------------------------- */
    /*                          Flow 2: On the input data                         */
    /* -------------------------------------------------------------------------- */

    /*
        Data generation is done by setup.py (either copies from the practical-1 directory or generates new random data, depending upon user choice)
    */

    /* ---------------------------- Read Input files ---------------------------- */
    std::string base = "./input";
    for (int n = 1; n <= 10; n++)
    {
        // Computing the metadata for the n-sized dataset

        Metadata sum{0, 0};
        Metadata sumAgeOnly{0, 0};
        Metadata sumNameOnly{0, 0};

        for (int d = 1; d <= 10; d++)
        {
            std::string dir =
                base + "/" +
                (d < 10 ? "00" : "0") + std::to_string(d);

            std::string file =
                dir + "/n" +
                (n * 10 < 100 ? "0" : "") +
                std::to_string(n * 10);

            // Now, file is the path to a file of n-sized datapoints
            auto &records = read(file);
            auto recordsCopy = records;
            auto recordsAnotherCopy = records;

            // Sort the vectors in memory
            Metadata onAge = randomizedQuickSortWithMetadata(records, compareByAge);
            Metadata onName = randomizedQuickSortWithMetadata(records, compareByName);
            Metadata combined{onAge.comparisons + onName.comparisons, onAge.assignments + onAge.assignments};

            Metadata onNameOnly = randomizedQuickSortWithMetadata(recordsCopy, compareByName);
            Metadata onAgeOnly = randomizedQuickSortWithMetadata(recordsAnotherCopy, compareByAge);

            // Write records to output folder
            std::string outputPath = "./output/" + ((d < 10 ? "00" : "0") + std::to_string(d)) + "/n" + (n * 10 < 100 ? "0" : "") + std::to_string(n * 10);

            write(records, outputPath);

            // Update metrics for age only sorting
            sumAgeOnly.comparisons += onAgeOnly.comparisons;
            sumAgeOnly.assignments += onAgeOnly.assignments;

            // Update metrics for name only sorting
            sumNameOnly.comparisons += onNameOnly.comparisons;
            sumNameOnly.assignments += onNameOnly.assignments;

            // Update metrics for both columns
            sum.comparisons += combined.comparisons;
            sum.assignments += combined.assignments;
        }

        Metadata average = {sum.assignments / 10, sum.comparisons / 10};
        report.push_back(average);

        Metadata averageAgeOnly = {sumAgeOnly.assignments / 10, sumAgeOnly.comparisons / 10};
        reportAgeOnly.push_back(averageAgeOnly);

        Metadata averageNameOnly = {sumNameOnly.assignments / 10, sumNameOnly.comparisons / 10};
        reportNameOnly.push_back(averageNameOnly);
    }

    /* --------------------- When sorted on both the fields --------------------- */

    std::ofstream out("./output/report.txt");
    if (!out)
        return 1;

    for (const Metadata &avg : report)
        out << avg.comparisons << "," << avg.assignments << "\n";

    /* ------------------------- When sorted on age only ------------------------ */

    std::ofstream out2("./output/report_age_only.txt");
    if (!out2)
        return 1;

    for (const Metadata &avg : reportAgeOnly)
        out2 << avg.comparisons << "," << avg.assignments << "\n";

    /* ------------------------ When sorted on name only ------------------------ */

    std::ofstream out3("./output/report_name_only.txt");
    if (!out3)
        return 1;

    for (const Metadata &avg : reportNameOnly)
        out3 << avg.comparisons << "," << avg.assignments << "\n";

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                            Comparator functions                            */
/* -------------------------------------------------------------------------- */

bool compareByAge(const Record *rec1, const Record *rec2)
{
    return rec1->age > rec2->age; // rec1 will come first in the sorted array
}

bool compareByName(const Record *rec1, const Record *rec2)
{
    return rec1->name > rec2->name;
}