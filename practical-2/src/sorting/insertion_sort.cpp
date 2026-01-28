// Header to be implemented
#include <sorting/insertion_sort.hpp>

// Internal dependencies
#include <structs/Record.hpp>

// External dependencies
#include <iostream>
#include <vector>

/* -------------------------------------------------------------------------- */
/*                            Forward declarations                            */
/* -------------------------------------------------------------------------- */

void _insertionSort(std::vector<const Record *> &input, Comparator comp, int &comparisons, int &assignments);

bool compareByAge(const Record *rec1, const Record *rec2);
bool compareByName(const Record *rec1, const Record *rec2);

/* -------------------------------------------------------------------------- */
/*                                  Main Body                                 */
/* -------------------------------------------------------------------------- */

void insertionSort(std::vector<const Record *> &input, Comparator comp)
{
    int comparisons = 0;
    int assignments = 0;

    _insertionSort(input, comp, comparisons, assignments);
}

/**
 * @brief Sort using insertion sort and return metadata
 *
 * @param input The vector of Record pointers to be sorted
 * @param comp Comparator function
 * @return Metadata Comparisons and assignments performed
 */
Metadata insertionSortWithMetadata(std::vector<const Record *> &input, Comparator comp)
{
    int comparisons = 0;
    int assignments = 0;

    _insertionSort(input, comp, comparisons, assignments);

    Metadata meta{comparisons, assignments};
    return meta;
}

/* -------------------------------------------------------------------------- */
/*                             Internal functions                             */
/* -------------------------------------------------------------------------- */

/**
 * @brief Find the correct location for the i-th element in the vector
 *
 * @param input Reference to vector of const pointers to Records
 * @param i The index of the element whose correct position is to be ascertained
 * @param comp Function pointer to a comparator function defined on const Record*
 * @param comparisons Reference variable to keep track of comparisons
 * @param assignments Reference variable to keep track of the assignments
 * @return int The correct index of the element
 */
int _findLocation(std::vector<const Record *> &input, int i, Comparator comp, int &comparisons, int &assignments)
{
    const Record *keyRecord = input[i];

    int j = i - 1;
    while (j >= 0 && comp(input[j], input[i]))
    {
        comparisons++;
        j--;
    }

    comparisons++;

    return j + 1;
}

void _insert(std::vector<const Record *> &input, int current, int correct, int &comparisons, int &assignments)
{
    const Record *keyRecord = input[current];

    for (int i = current - 1; i >= correct; i--)
    {
        assignments++;
        input[i + 1] = input[i];
    }

    input[correct] = keyRecord;
}

/**
 * @brief Sort the vector of Record pointers using insertion sort while keeping track of comparisons and assignments
 *
 * @param input
 * @param comp
 * @param comparisons
 * @param assignments
 */
void _insertionSort(std::vector<const Record *> &input, Comparator comp, int &comparisons, int &assignments)
{
    for (int i = 1; i < input.size(); i++)
    {
        int correct = _findLocation(input, i, comp, comparisons, assignments);
        _insert(input, i, correct, comparisons, assignments);
    }
}