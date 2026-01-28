#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

// External dependencies
#include <vector>

// Internal dependencies
#include <structs/Record.hpp>
#include <structs/Metadata.hpp>

using Comparator = bool (*)(const Record *, const Record *);

void insertionSort(std::vector<const Record *> &input, Comparator comp);

Metadata insertionSortWithMetadata(std::vector<const Record *> &input, Comparator comp);

#endif