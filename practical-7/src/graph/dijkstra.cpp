// Header to be implemented
#include <graph/sssp.hpp>

// Internal dependencies
#include <data/Record.hpp>
#include <graph/Graph.hpp>
#include <graph/Node.hpp>

// External dependencies
#include <vector>
#include <limits>

namespace graph
{
    template <typename RecordType>
    Graph<RecordType> dijkstra(
        const Graph<RecordType> &base,
        const Node<RecordType> *start)
    {
        Graph<RecordType> output;

        const auto &nodes = base.getNodes();
        int n = nodes.size();

        if (n == 0 || start == nullptr)
            return output;

        // Add all nodes to output
        for (auto *node : nodes)
            output.addNode(node);

        // Find start index
        int startIndex = -1;
        for (int i = 0; i < n; ++i)
        {
            if (nodes[i] == start)
            {
                startIndex = static_cast<int>(i);
                break;
            }
        }

        if (startIndex == -1)
            return output;

        // Distance, parent, visited
        std::vector<double> dist(n, std::numeric_limits<double>::infinity());
        std::vector<int> parent(n, -1);
        std::vector<bool> visited(n, false);

        dist[startIndex] = 0.0;

        for (int count = 0; count < n; ++count)
        {
            // Pick closest unvisited node
            double minDist = std::numeric_limits<double>::infinity();
            int u = -1;

            for (int i = 0; i < n; ++i)
            {
                if (!visited[i] && dist[i] < minDist)
                {
                    minDist = dist[i];
                    u = static_cast<int>(i);
                }
            }

            // No reachable node left
            if (u == -1)
                break;

            // If unreachable, stop early
            if (dist[u] == std::numeric_limits<double>::infinity())
                break;

            visited[u] = true;

            // Relax neighbors
            for (int v = 0; v < n; ++v)
            {
                if (u == (int)v || visited[v])
                    continue;

                double weight = base.getWeight(nodes[u], nodes[v]);

                if (weight <= 0 || weight == std::numeric_limits<double>::infinity())
                    continue;

                // Relaxation
                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }

        // Build SPT
        for (int v = 0; v < n; ++v)
        {
            if (parent[v] != -1)
            {
                double weight = base.getWeight(nodes[parent[v]], nodes[v]);
                output.addEdge(nodes[parent[v]], nodes[v], weight);
            }
        }

        return output;
    }
}

/* -------------------------------------------------------------------------- */
/*                       Explicit template instantiation                      */
/* -------------------------------------------------------------------------- */

template graph::Graph<Record> graph::dijkstra<Record>(
    const graph::Graph<Record> &,
    const graph::Node<Record> *);