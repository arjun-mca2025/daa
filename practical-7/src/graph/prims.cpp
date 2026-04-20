// Header to be implemented
#include <graph/mst.hpp>

// Internal dependencies
#include <data/Record.hpp>
#include <graph/Graph.hpp>
#include <graph/Node.hpp>
#include <graph/Edge.hpp>

// External dependencies
#include <vector>
#include <limits>

namespace graph
{
    template <typename RecordType>
    Graph<RecordType> prims(const Graph<RecordType> &base)
    {
        Graph<RecordType> output;

        const auto &nodes = base.getNodes();
        int n = nodes.size();

        if (n == 0)
            return output;

        // Add all nodes to output
        for (auto *node : nodes)
            output.addNode(node);

        std::vector<double> key(n, std::numeric_limits<double>::infinity());

        // Parent indices
        std::vector<int> parent(n, -1);

        // Track nodes included in MST
        std::vector<bool> inMST(n, false);

        // Start from node 0
        key[0] = 0;

        for (int count = 0; count < n - 1; ++count)
        {
            // Pick minimum key vertex not yet included
            double minKey = std::numeric_limits<double>::infinity();
            int u = -1;

            for (int i = 0; i < n; ++i)
            {
                if (!inMST[i] && key[i] < minKey)
                {
                    minKey = key[i];
                    u = static_cast<int>(i);
                }
            }

            if (u == -1)
                break;

            inMST[u] = true;

            // Update adjacent vertices
            for (int v = 0; v < n; ++v)
            {
                double weight = base.getWeight(nodes[u], nodes[v]);

                if (!inMST[v] && weight != 0 && weight < key[v])
                {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }

        // Build MST
        for (int v = 1; v < n; ++v)
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

template graph::Graph<Record> graph::prims<Record>(const graph::Graph<Record> &);