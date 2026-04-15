#ifndef SSSP_H
#define SSSP_H

// Internal dependencies
#include <graph/Graph.hpp>
#include <graph/Node.hpp>

namespace graph
{
    /**
     * @brief Compute shortest paths from a start node using Dijkstra's algorithm
     *
     * @tparam RecordType The type of record being operated on by the graph
     * @param base Base Graph
     * @param start Starting node
     * @return Graph<RecordType> Shortest Path Tree (SPT)
     */
    template <typename RecordType>
    Graph<RecordType> dijkstra(
        const Graph<RecordType> &base,
        const Node<RecordType> *start);
}

#endif