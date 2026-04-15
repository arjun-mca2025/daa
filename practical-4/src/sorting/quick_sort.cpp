// Header to be implemented
#include <sorting/quick_sort.hpp>

// Internal dependencies
#include <structs/Record.hpp>

// External dependencies
#include <iostream>
#include <vector>

/* -------------------------------------------------------------------------- */
/*                            Forward declarations                            */
/* -------------------------------------------------------------------------- */

void _quickSort(std::vector<const Record *> &input,
                int left,
                int right,
                Comparator comp,
                int &comparisons,
                int &assignments);

int _partition(std::vector<const Record *> &input,
               int left,
               int right,
               Comparator comp,
               int &comparisons,
               int &assignments);

/* -------------------------------------------------------------------------- */
/*                                  Main Body                                 */
/* -------------------------------------------------------------------------- */

void quickSort(std::vector<const Record *> &input, Comparator comp)
{
    int comparisons = 0;
    int assignments = 0;

    _quickSort(input, 0, input.size() - 1, comp, comparisons, assignments);
}

Metadata quickSortWithMetadata(std::vector<const Record *> &input, Comparator comp)
{
    int comparisons = 0;
    int assignments = 0;

    _quickSort(input, 0, input.size() - 1, comp, comparisons, assignments);

    Metadata meta{comparisons, assignments};
    return meta;
}

/* -------------------------------------------------------------------------- */
/*                             Internal functions                             */
/* -------------------------------------------------------------------------- */

int _partition(std::vector<const Record *> &input,
               int left,
               int right,
               Comparator comp,
               int &comparisons,
               int &assignments)
{
    // Lomuto partition scheme
    const Record *pivot = input[right];
    assignments++;

    int i = left - 1;

    for (int j = left; j < right - 1; j++)
    {
        comparisons++;

        // If input[j] should come before pivot
        if (comp(input[j], pivot))
        {
            i++;

            std::swap(input[i], input[j]);
            assignments += 3; // swap = 3 assignments
        }
    }

    std::swap(input[i + 1], input[right]);
    assignments += 3;

    return i + 1;
}

void _quickSort(std::vector<const Record *> &input,
                int left,
                int right,
                Comparator comp,
                int &comparisons,
                int &assignments)
{
    if (left >= right)
        return;

    int pivotIndex = _partition(input, left, right, comp, comparisons, assignments);

    _quickSort(input, left, pivotIndex - 1, comp, comparisons, assignments);
    _quickSort(input, pivotIndex + 1, right, comp, comparisons, assignments);
}