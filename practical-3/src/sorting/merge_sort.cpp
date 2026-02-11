// Header to be implemented
#include <sorting/merge_sort.hpp>

// Internal dependencies
#include <structs/Record.hpp>

// External dependencies
#include <iostream>
#include <vector>

/* -------------------------------------------------------------------------- */
/*                            Forward declarations                            */
/* -------------------------------------------------------------------------- */

void _mergeSort(std::vector<const Record *> &input, int left, int right, Comparator comp, int &comparisons, int &assignments);

bool compareByAge(const Record *rec1, const Record *rec2);
bool compareByName(const Record *rec1, const Record *rec2);

/* -------------------------------------------------------------------------- */
/*                                  Main Body                                 */
/* -------------------------------------------------------------------------- */

void mergeSort(std::vector<const Record *> &input, Comparator comp)
{
    int comparisons = 0;
    int assignments = 0;

    _mergeSort(input, 0, input.size() - 1, comp, comparisons, assignments);
}

Metadata mergeSortWithMetadata(std::vector<const Record *> &input, Comparator comp)
{
    int comparisons = 0;
    int assignments = 0;

    _mergeSort(input, 0, input.size() - 1, comp, comparisons, assignments);

    Metadata meta{comparisons, assignments};
    return meta;
}

/* -------------------------------------------------------------------------- */
/*                             Internal functions                             */
/* -------------------------------------------------------------------------- */

void _merge(std::vector<const Record *> &input,
            int left,
            int mid,
            int right,
            Comparator comp,
            int &comparisons,
            int &assignments)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<const Record *> L(n1);
    std::vector<const Record *> R(n2);

    // Copy data into temporary arrays
    for (int i = 0; i < n1; i++)
    {
        L[i] = input[left + i];
        assignments++;
    }

    for (int j = 0; j < n2; j++)
    {
        R[j] = input[mid + 1 + j];
        assignments++;
    }

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        comparisons++;

        if (comp(R[j], L[i]))
        {
            input[k] = L[i];
            i++;
        }
        else
        {
            input[k] = R[j];
            j++;
        }

        assignments++;
        k++;
    }

    // Copy remaining elements
    while (i < n1)
    {
        input[k++] = L[i++];
        assignments++;
    }

    while (j < n2)
    {
        input[k++] = R[j++];
        assignments++;
    }
}

void _mergeSort(std::vector<const Record *> &input,
                int left,
                int right,
                Comparator comp,
                int &comparisons,
                int &assignments)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    _mergeSort(input, left, mid, comp, comparisons, assignments);
    _mergeSort(input, mid + 1, right, comp, comparisons, assignments);

    _merge(input, left, mid, right, comp, comparisons, assignments);
}
