#ifndef EDGE_H
#define EDGE_H

// Internal dependencies
#include <graph/Node.hpp>

namespace graph
{
    template <typename RecordType>
    struct Edge
    {
        const Node<RecordType> *src;
        const Node<RecordType> *dest;
        int weight = 1;
    };
}

#endif