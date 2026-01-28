// External dependencies
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// Internal dependencies
#include <structs/Record.hpp>
#include <structs/Metadata.hpp>
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
    // Data file paths
    std::string datasetPath = "./input/data.csv"; // path relative to the CWD

    // Metadata file paths
    std::string metadataPath = "./output/meta.csv"; // When samples of varying size are used
    std::string reportPath = "./output/report.csv"; // "Report" is when the whole dataset is sorted

    // All the dataset read into a vector
    auto &dataset = read(datasetPath);

    std::cout << "Enter 0 for sorting the whole dataset, and anything else for sorting sample of varying sizes: " << std::endl;
    int choice;
    std::cin >> choice;

    /* --------------------- Flow 0: Sort the whole dataset --------------------- */
    /**
     * Write the output to ./output/data.csv
     * Write the metadata to ./output/report.csv
     */

    if (choice == 0)
    {
        // Sort the records in memory and record the metadata
        Metadata metadata = insertionSortWithMetadata(dataset, compareByTemperature);

        // Write the sorted records
        write(dataset, "./output/data.csv");

        // Write the metadata
        writeMetadata(metadata, "./output/report.csv");

        std::cout << "Wrote the sorted contents to the ./output/data.csv folder and the metadata (comparisons and assignments) to ./output/report.csv" << std::endl;

        return 0;
    }

    /* ------------------ Flow 1: Sort samples of varying sizes ----------------- */

    if (choice != 0)
    {
        for (int n = 10; n <= 100; n += 10)
        {
            Metadata sumMetadata{0, 0};
            for (int i = 0; i < 10; i++)
            {
                std::string inputPath = "./input/n" + std::to_string(n) + "/sample" + std::to_string(i) + ".csv";
                std::string outputPath = "./output/n" + std::to_string(n) + "/sample" + std::to_string(i) + ".csv";

                // Generate samples
                auto &sampleOfSizeN = sampleN(dataset, n);

                // Write samples to input files
                write(sampleOfSizeN, inputPath);

                // Sort the samples
                auto currentMetadata = insertionSortWithMetadata(sampleOfSizeN, compareByTemperature);
                write(sampleOfSizeN, outputPath);

                sumMetadata.assignments += currentMetadata.assignments;
                sumMetadata.comparisons += currentMetadata.comparisons;
            }

            // Compute average comparisons and assignments for this particular sample size
            Metadata averageMetadata = sumMetadata;
            averageMetadata.assignments = sumMetadata.assignments / 10;
            averageMetadata.comparisons = sumMetadata.comparisons / 10;

            // Write the metadata to file
            writeMetadata(averageMetadata, metadataPath);
        }

        std::cout << "Wrote the sorted contents to the ./output folder and the metadata (comparisons and assignments) to ./output/meta.csv" << std::endl;
        return 0;
    }
}

/* -------------------------------------------------------------------------- */
/*                            Comparator function                             */
/* -------------------------------------------------------------------------- */

bool compareByTemperature(const Record *rec1, const Record *rec2)
{
    // true means rec2 should come first, false means rec1 should come first
    return !(rec1->averageTemp < rec2->averageTemp); // rec1 will come first in the sorted array if its temperature is lower
}