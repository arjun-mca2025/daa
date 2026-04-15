#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

// Internal dependencies
#include <graph/Node.hpp>

// External dependencies
#include <unordered_map>
#include <vector>

template <typename RecordType>
class DisjointSet
{
private:
    std::unordered_map<const graph::Node<RecordType> *, const graph::Node<RecordType> *> parent;
    std::unordered_map<const graph::Node<RecordType> *, int> rank;

public:
    /* ------------------------------- Constructor ------------------------------ */
    DisjointSet<RecordType>(std::vector<const graph::Node<RecordType> *>);

    /* ---------------------------------- Find ---------------------------------- */
    const graph::Node<RecordType> *find(const graph::Node<RecordType> *curr);

    /* ---------------------------------- Union --------------------------------- */
    void join(const graph::Node<RecordType> *first, const graph::Node<RecordType> *second);
};

#endif