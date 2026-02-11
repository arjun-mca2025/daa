#ifndef MERGE_SORT_H
#define MERGE_SORT_H

// External dependencies
#include <vector>

// Internal dependencies
#include <structs/Record.hpp>

struct Metadata
{
    int comparisons;
    int assignments;
};

using Comparator = bool (*)(const Record *, const Record *);

void mergeSort(std::vector<const Record *> &input, Comparator comp);

Metadata mergeSortWithMetadata(std::vector<const Record *> &input, Comparator comp);

#endif