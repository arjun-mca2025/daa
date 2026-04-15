// Header to be implemented
#include <graph/mst.hpp>

// Internal dependencies
#include <data/Record.hpp>
#include <graph/Graph.hpp>
#include <graph/Node.hpp>
#include <graph/Edge.hpp>
#include <utils/DisjointSet.hpp>

// External dependencies
#include <vector>
#include <algorithm>

/* ------------------------------- Comparator ------------------------------- */

namespace graph
{
    template <typename RecordType>
    Graph<RecordType> kruskal(const Graph<RecordType> &base)
    {
        Graph<RecordType> output;

        for (auto *node : base.getNodes())
            output.addNode(node);

        std::vector<const Edge<RecordType> *> edges = base.getEdges();

        // Sort all edges in terms of their weights
        std::sort(edges.begin(), edges.end(), [](const Edge<RecordType> *first, const Edge<RecordType> *second)
                  { return first->weight < second->weight; });

        DisjointSet<RecordType> djs{base.getNodes()};

        for (const Edge<RecordType> *edge : edges)
        {
            if (djs.find(edge->src) != djs.find(edge->dest))
            {
                // this edge connects a node from two non-connected components
                output.addEdge(edge->src, edge->dest, edge->weight);
                djs.join(edge->src, edge->dest);
            }
        }

        return output;
    }
}

/* -------------------------------------------------------------------------- */
/*                       Explicit template instantiation                      */
/* -------------------------------------------------------------------------- */

template graph::Graph<Record> graph::kruskal<Record>(const graph::Graph<Record> &);