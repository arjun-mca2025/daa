#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

// Internal dependencies
#include <structs/Metadata.hpp>
#include <structs/Record.hpp>
#include <classes/Encoder.hpp>

// External dependencies
#include <vector>
#include <functional>

/* -------------------------------------------------------------------------- */
/*                               Main functions                               */
/* -------------------------------------------------------------------------- */

void countingSort(std::vector<const Record *> &, const Encoder &);
Metadata countingSortWithMetadata(std::vector<const Record *> &, const Encoder &);

#endif