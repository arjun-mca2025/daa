// External dependencies
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

// Internal dependencies
#include <structs/Record.hpp>
#include <classes/Encoder.hpp>
#include <classes/RadixEncoder.hpp>
#include <sorting/counting_sort.hpp>
#include <sorting/radix_sort.hpp>
#include <io.hpp>

/* -------------------------------------------------------------------------- */
/*                             Encoder definitions                            */
/* -------------------------------------------------------------------------- */

class AgeRadixEncoder : public RadixEncoder
{
public:
    // Default constructor that defines range [0 to 9], with 3 digits in total
    AgeRadixEncoder() : RadixEncoder(0, 9, 1, 3) {}

    int encode(const Record *record) const override
    {
        return AgeRadixEncoder::getNthDigit(record->age, this->getCurrentDigitIndex(), 1);
    }

    static int getNthDigit(float num, int n, int decimalPlaces)
    {
        int scaled = static_cast<int>(std::abs(num) * std::pow(10, decimalPlaces));

        for (int i = 0; i < n; i++)
            scaled /= 10;

        return scaled % 10;
    }
};

class NameRadixEncoder : public RadixEncoder
{
public:
    // Default constructor with null character, a-z and A-Z, step 1, 10 chars maximum
    NameRadixEncoder() : RadixEncoder(0, 52, 1, 10) {}

    int encode(const Record *record) const override
    {
        char ch = NameRadixEncoder::getNthChar(record->name, this->getCurrentDigitIndex(), this->getNumberOfDigits());

        if (ch == '\0')
            return 0;
        else if (ch >= 'a' && ch <= 'z')
            return ch - 'a';
        else if (ch >= 'A' && ch <= 'Z')
            return 27 + ch - 'A';
        else
            return -1;
    }

    static char getNthChar(std::string name, int n, int maxChars)
    {
        int leftIndex = maxChars - n - 1; // index required (starting from left)
        int size = name.size();           // size of the string

        if (leftIndex >= size)
            return '\0';

        return name[leftIndex];
    }
};

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
        records->push_back(new Record{"John", 76.1});
        records->push_back(new Record{"Reena", 21.6});
        records->push_back(new Record{"Jacob", 77.7});
        records->push_back(new Record{"Reena", 43.7});
        records->push_back(new Record{"Reena", 22.0});
        records->push_back(new Record{"Saumya", 31.9});
        records->push_back(new Record{"Jacob", 39.8});
        records->push_back(new Record{"Shreya", 80.8});
        records->push_back(new Record{"Aditya", 58.6});
        records->push_back(new Record{"Arjun", 70.7});

        auto &recordsRef = *records;

        // Copy of the same records
        auto recordsCopy = *records;

        std::cout << "Initial records: " << "\n";
        for (const Record *rec : recordsRef)
            std::cout << convertRecordToString(*rec) << "\n";

        /* ----------------------------- Sorting on Age ----------------------------- */
        std::cout << "-----------------------------" << "\n";
        std::cout << "Testing Radix Sort on age: " << "\n";
        AgeRadixEncoder ageEncoder{};
        radixSortWithMetadata(recordsRef, ageEncoder);
        for (const Record *rec : recordsRef)
            std::cout << convertRecordToString(*rec) << "\n";

        /* ----------------------------- Sorting on Name ---------------------------- */
        std::cout << "-----------------------------" << "\n";
        std::cout << "Testing Radix Sort on name: " << "\n";
        NameRadixEncoder nameEncoder{};
        radixSort(recordsCopy, nameEncoder);
        for (const Record *rec : recordsCopy)
        {
            std::cout << convertRecordToString(*rec) << "\n";
        }

        /* --------------------- Sorting on Age followed by Name -------------------- */
        // already sorted this on age above
        std::cout << "-----------------------------" << "\n";
        std::cout << "Testing Radix Sort on age followed by name: " << "\n";
        nameEncoder = NameRadixEncoder();
        radixSort(recordsRef, nameEncoder);
        for (const Record *rec : recordsRef)
        {
            std::cout << convertRecordToString(*rec) << "\n";
        }

        return 0;
    }

    /* -------------------------------------------------------------------------- */
    /*                          Flow 2: On the input data                         */
    /* -------------------------------------------------------------------------- */

    std::vector<Metadata> report{}; // 10-sized vector for keeping average Metadata for each size of n
    std::vector<Metadata> reportAgeOnly{};
    std::vector<Metadata> reportNameOnly{};
    /*
        Data generation is done by setup.py
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

            AgeRadixEncoder ageOnlyEncoder{};
            NameRadixEncoder nameOnlyEncoder{};
            AgeRadixEncoder combinedAgeEncoder{};
            NameRadixEncoder combinedNameEncoder{};

            // Sort the vectors in memory
            Metadata onAge = radixSortWithMetadata(records, combinedAgeEncoder);
            Metadata onName = radixSortWithMetadata(records, combinedNameEncoder);
            Metadata combined{onAge.comparisons + onName.comparisons, onAge.assignments + onAge.assignments};

            Metadata onNameOnly = radixSortWithMetadata(recordsCopy, nameOnlyEncoder);
            Metadata onAgeOnly = radixSortWithMetadata(recordsAnotherCopy, ageOnlyEncoder);

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

        Metadata average = {sum.comparisons / 10, sum.assignments / 10};
        report.push_back(average);

        Metadata averageAgeOnly = {sumAgeOnly.comparisons / 10, sumAgeOnly.assignments / 10};
        reportAgeOnly.push_back(averageAgeOnly);

        Metadata averageNameOnly = {sumNameOnly.comparisons / 10, sumNameOnly.assignments / 10};
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