#ifndef RADIX_SORT_H
#define RADIX_SORT_H

// Internal dependencies
#include <structs/Metadata.hpp>
#include <structs/Record.hpp>
#include <classes/RadixEncoder.hpp>

// External dependencies
#include <vector>

/* -------------------------------------------------------------------------- */
/*                               Main functions                               */
/* -------------------------------------------------------------------------- */

void radixSort(std::vector<const Record *> &, RadixEncoder &);
Metadata radixSortWithMetadata(std::vector<const Record *> &, RadixEncoder &);

#endif
