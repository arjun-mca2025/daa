// Header to be implemented
#include <utils/DisjointSet.hpp>

// Internal dependencies
#include <data/Record.hpp>

// External dependencies
#include <vector>

template <typename RecordType>
DisjointSet<RecordType>::DisjointSet(std::vector<const graph::Node<RecordType> *> nodes)
{
    for (auto *node : nodes)
    {
        this->parent[node] = node;
        this->rank[node] = 1;
    }
}

template <typename RecordType>
const graph::Node<RecordType> *DisjointSet<RecordType>::find(const graph::Node<RecordType> *curr)
{
    if (this->parent[curr] != curr)
        return this->find(this->parent[curr]);
    else
        return this->parent[curr];
}

template <typename RecordType>
void DisjointSet<RecordType>::join(const graph::Node<RecordType> *first, const graph::Node<RecordType> *second)
{
    if (this->rank[first] > this->rank[second])
    {
        this->parent[first] = this->parent[second];
        this->rank[first]++;
    }
    else
    {
        this->parent[second] = this->parent[first];
        this->rank[second]++;
    }
}

/* -------------------------------------------------------------------------- */
/*                       Explicit template instantiation                      */
/* -------------------------------------------------------------------------- */

template class DisjointSet<Record>;