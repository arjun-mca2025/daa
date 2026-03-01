#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <vector>
#include <functional>

// Forward declaration
struct Record;

// Comparator type
using Comparator = std::function<bool(const Record *, const Record *)>;

// Metadata struct
struct Metadata
{
    int comparisons;
    int assignments;
};

void quickSort(std::vector<const Record *> &input, Comparator comp);

Metadata quickSortWithMetadata(std::vector<const Record *> &input, Comparator comp);

#endif