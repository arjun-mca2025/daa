#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <vector>
#include <functional>

// Internal dependencies
#include <structs/Metadata.hpp>
#include <structs/Record.hpp>

// Forward declaration
struct Record;

// Comparator type
using Comparator = std::function<bool(const Record *, const Record *)>;

void quickSort(std::vector<const Record *> &input, Comparator comp);

Metadata quickSortWithMetadata(std::vector<const Record *> &input, Comparator comp);

#endif