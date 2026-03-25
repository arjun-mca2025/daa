#ifndef RANDOMIZED_QUICK_SORT_HPP
#define RANDOMIZED_QUICK_SORT_HPP

#include <vector>
#include <functional>

// Internal dependencies
#include <structs/Metadata.hpp>
#include <structs/Record.hpp>

// Forward declaration
struct Record;

// Comparator type
using Comparator = std::function<bool(const Record *, const Record *)>;

void randomizedQuickSort(std::vector<const Record *> &input, Comparator comp);
void quickSort(std::vector<const Record *> &input, Comparator comp);

Metadata randomizedQuickSortWithMetadata(std::vector<const Record *> &input, Comparator comp);
Metadata quickSortWithMetadata(std::vector<const Record *> &input, Comparator comp);

#endif