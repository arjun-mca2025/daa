// Header to be implemented
#include <graph/traversal.hpp>

// External dependencies
#include <queue>
#include <stack>
#include <unordered_map>
#include <iostream>

// Internal dependencies
#include <graph/Graph.hpp>
#include <data/Record.hpp>

namespace graph
{
    template <typename RecordType>
    void bfs(const Graph<RecordType> &graph, const Node<RecordType> *start)
    {
        std::queue<const Node<RecordType> *> q;
        int size = graph.getNumNodes();

        std::unordered_map<const Node<RecordType> *, bool> visited;

        q.push(start);

        while (!q.empty())
        {
            auto *curr = q.front();
            q.pop();

            // Visit the node
            std::cout << curr->record->getStringRepresentation() << " ";
            visited[curr] = true;

            for (auto *neighbour : graph.getNeighbours(curr))
                if (!visited[neighbour])
                    q.push(neighbour);
        }

        std::cout << std::endl;
    }

    template <typename RecordType>
    void dfs(const Graph<RecordType> &graph, const Node<RecordType> *start)
    {
        std::stack<const Node<RecordType> *> s;
        int size = graph.getNumNodes();

        std::unordered_map<const Node<RecordType> *, bool> visited;

        s.push(start);

        while (!s.empty())
        {
            auto *curr = s.top();
            s.pop();

            // Visit the node
            std::cout << curr->record->getStringRepresentation() << " ";
            visited[curr] = true;

            for (auto *neighbour : graph.getNeighbours(curr))
                if (!visited[neighbour])
                    s.push(neighbour);
        }

        std::cout << std::endl;
    }
}

/* -------------------------------------------------------------------------- */
/*                       Explicit template instantiation                      */
/* -------------------------------------------------------------------------- */

template void graph::bfs<Record>(const graph::Graph<Record> &, const Node<Record> *);
template void graph::dfs<Record>(const graph::Graph<Record> &, const Node<Record> *);