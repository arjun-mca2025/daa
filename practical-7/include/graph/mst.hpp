#ifndef MST_H
#define MST_H

// Internal dependencies
#include <graph/Graph.hpp>

namespace graph
{
    /**
     * @brief Get the minimum spanning graph for the given graph
     *
     * @tparam RecordType The type of record being operated on by the graph
     * @param base Base Graph
     * @return Graph<RecordType> Minimum Spanning Tree/Graph
     */
    template <typename RecordType>
    Graph<RecordType> kruskal(const Graph<RecordType> &base);

    /**
     * @brief Get the minimum spanning graph for the given graph using the Prim's algorithm
     *
     * @tparam RecordType The type of record being operated on by the graph
     * @param base Base Graph
     * @return Graph<RecordType> Minimum Spaning Tree/Graph
     */
    template <typename RecordType>
    Graph<RecordType> prims(const Graph<RecordType> &base);
}

#endif