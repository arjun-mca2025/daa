#ifndef TRAVERSAL_H
#define TRAVERSAL_H

// Internal dependencies
#include <graph/Graph.hpp>

namespace graph
{
    /**
     * @brief Perform BFS traversal on the graph
     *
     * @tparam RecordType Type of record data held by the graph
     * @param graph Graph which needs to be traversed
     * @param start Starting node
     */
    template <typename RecordType>
    void bfs(const Graph<RecordType> &graph, const Node<RecordType> *start);

    template <typename RecordType>
    void dfs(const Graph<RecordType> &graph, const Node<RecordType> *start);
}
#endif