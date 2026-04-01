// Header to be implemented
#include <sorting/counting_sort.hpp>

// Internal dependencies
#include <structs/Record.hpp>
#include <structs/Metadata.hpp>
#include <classes/Encoder.hpp>

// External dependencies
#include <vector>
#include <map>
#include <utility>
#include <cmath>

/* -------------------------------------------------------------------------- */
/*                            Forward Declarations                            */
/* -------------------------------------------------------------------------- */

void _countingSort(std::vector<const Record *> &arr, const Encoder &encoder, int &comparisons, int &assignments);

/* -------------------------------------------------------------------------- */
/*                               Main functions                               */
/* -------------------------------------------------------------------------- */

Metadata countingSortWithMetadata(std::vector<const Record *> &arr, const Encoder &encoder)
{
    int comparisons = 0;
    int assignments = 0;
    _countingSort(arr, encoder, comparisons, assignments);
    return Metadata{comparisons, assignments};
}

void countingSort(std::vector<const Record *> &arr, const Encoder &encoder)
{
    countingSortWithMetadata(arr, encoder);
}

void _countingSort(std::vector<const Record *> &arr, const Encoder &encoder, int &comparisons, int &assignments)
{
    /**
     * @brief For now, I am explicitly specifiying age as the attribute upon which the sorting needs to take place
     * @todo Make the sorting criterion taken as input via a parameter
     *
     * Need a function that maps a record to its age, and also a struct that contains the range step and scale
     */

    // Keep track of frequencies of records for a particular age

    int min = encoder.getMin();
    int max = encoder.getMax();
    int step = encoder.getStep();

    auto frequencies = std::map<int, std::pair<int, std::vector<const Record *>>>();

    // Initialize the frequencies with 0
    for (int i = min; i <= max; i += step)
    {
        assignments++;
        frequencies[i] = {0, {}};
    }

    for (auto *record : arr)
    {
        int key = encoder.encode(record);
        frequencies[key].first++;
        frequencies[key].second.push_back(record);
        assignments++;
    }

    auto cumulativeFrequencies = frequencies;
    for (int i = min + step; i <= max; i += step)
    {
        // Update the frequencies only
        cumulativeFrequencies[i].first = cumulativeFrequencies[i].first + cumulativeFrequencies[i - 1].first;
    }

    // Overwrite the original array
    for (int i = max; i >= min; i -= step)
    {
        int correctLocation = cumulativeFrequencies[i].first - 1;
        while (frequencies[i].first > 0)
        {
            assignments += 2;
            arr[correctLocation] = cumulativeFrequencies[i].second.back();
            cumulativeFrequencies[i].second.pop_back();
            frequencies[i].first--;
            correctLocation--;
        }
    }
}