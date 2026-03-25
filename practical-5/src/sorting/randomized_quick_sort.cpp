// Header to be implemented
#include <sorting/randomized_quick_sort.hpp>

// Internal dependencies
#include <structs/Record.hpp>

// External dependencies
#include <iostream>
#include <vector>
#include <random>
#include <utility>

/* -------------------------------------------------------------------------- */
/*                            Forward declarations                            */
/* -------------------------------------------------------------------------- */

void _quickSort(std::vector<const Record *> &input,
                int left,
                int right,
                Comparator comp,
                int &comparisons,
                int &assignments);

void _randomizedQuickSort(std::vector<const Record *> &input,
                          int left,
                          int right, Comparator comp,
                          int &comparisons,
                          int &assignments);

int _partition(std::vector<const Record *> &input,
               int left,
               int right,
               Comparator comp,
               int &comparisons,
               int &assignments);

bool compareByAge(const Record *rec1, const Record *rec2);
bool compareByName(const Record *rec1, const Record *rec2);

/* -------------------------------------------------------------------------- */
/*                                  Main Body                                 */
/* -------------------------------------------------------------------------- */

void randomizedQuickSort(std::vector<const Record *> &input, Comparator comp)
{
    int comparisons = 0;
    int assignments = 0;

    _randomizedQuickSort(input, 0, input.size() - 1, comp, comparisons, assignments);
}

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

Metadata randomizedQuickSortWithMetadata(std::vector<const Record *> &input, Comparator comp)
{
    int comparisons = 0;
    int assignments = 0;

    _randomizedQuickSort(input, 0, input.size() - 1, comp, comparisons, assignments);

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

    for (int j = left; j < right; j++)
    {
        comparisons++;

        // If input[j] should come before pivot
        if (comp(pivot, input[j]))
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

void _randomizedQuickSort(std::vector<const Record *> &input,
                          int left,
                          int right, Comparator comp,
                          int &comparisons,
                          int &assignments)
{
    if (left >= right)
        return;

    int length = right - left + 1;

    // Select a random index
    int chosen_index = left + rand() % length;

    std::swap(input[chosen_index], input[right]);
    assignments += 3;

    int pivotIndex = _partition(input, left, right, comp, comparisons, assignments);

    _quickSort(input, left, pivotIndex - 1, comp, comparisons, assignments);
    _quickSort(input, pivotIndex + 1, right, comp, comparisons, assignments);
}