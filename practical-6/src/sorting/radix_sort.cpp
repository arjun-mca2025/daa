// Header to be implemented
#include <sorting/radix_sort.hpp>

// Internal dependencies
#include <sorting/counting_sort.hpp>
#include <structs/Record.hpp>
#include <structs/Metadata.hpp>
#include <classes/RadixEncoder.hpp>

// External dependencies
#include <vector>
#include <cmath>

/* -------------------------------------------------------------------------- */
/*                               Main functions                               */
/* -------------------------------------------------------------------------- */

Metadata radixSortWithMetadata(std::vector<const Record *> &arr, RadixEncoder &encoder)
{
    int comparisons = 0;
    int assignments = 0;

    int numDigits = encoder.getNumberOfDigits();
    for (int d = 0; d < numDigits; d++)
    {
        Metadata m = countingSortWithMetadata(arr, encoder);
        comparisons += m.comparisons;
        assignments += m.assignments;

        encoder.updateCurrentDigitIndex(); // next time, pick a different digit for sorting
    }

    return Metadata{comparisons, assignments};
}

void radixSort(std::vector<const Record *> &arr, RadixEncoder &encoder)
{
    radixSortWithMetadata(arr, encoder);
}
