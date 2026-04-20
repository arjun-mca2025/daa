// Header to be implemented
#include <graph/Graph.hpp>

// External dependencies
#include <vector>
#include <iostream>
#include <sstream>

// Internal dependencies
#include <data/Record.hpp>
#include <graph/Edge.hpp>

namespace graph
{
    /* ------------------------------- Constructor ------------------------------ */

    template <typename RecordType>
    Graph<RecordType>::Graph()
    {
        this->numNodes = 0;
    }

    /* --------------------------------- Getters -------------------------------- */

    template <typename RecordType>
    int Graph<RecordType>::getNumNodes() const
    {
        return this->numNodes;
    }

    template <typename RecordType>
    std::vector<const Node<RecordType> *> Graph<RecordType>::getNodes() const
    {
        return this->nodes;
    }

    template <typename RecordType>
    std::vector<const Edge<RecordType> *> Graph<RecordType>::getEdges() const
    {
        std::vector<const Edge<RecordType> *> edges;

        for (int i = 0; i < this->adjacencyMatrix.size(); i++)
        {
            auto &src = this->nodes[i];
            auto &row = this->adjacencyMatrix[i];

            for (int j = 0; j < row.size(); j++)
            {
                auto &dest = this->nodes[j];
                int weight = this->adjacencyMatrix[i][j];

                Edge<RecordType> *edge = new Edge<RecordType>{src, dest, weight};
                edges.push_back(edge);
            }
        }

        return edges;
    }

    template <typename RecordType>
    const Node<RecordType> *Graph<RecordType>::getNode(int i) const
    {
        return this->nodes[i];
    }

    template <typename RecordType>
    std::vector<const Node<RecordType> *> Graph<RecordType>::getNeighbours(const Node<RecordType> *node) const
    {
        std::vector<const Node<RecordType> *> neighbours;

        const std::vector<int> &adjacencyRow = this->adjacencyMatrix[this->mapping.at(node)];

        for (int i = 0; i < adjacencyRow.size(); i++)
            if (adjacencyRow[i])
                neighbours.push_back(this->nodes[i]);

        return neighbours;
    }

    template <typename RecordType>
    int Graph<RecordType>::getWeight(const Node<RecordType> *src, const Node<RecordType> *dest) const
    {
        return this->adjacencyMatrix[this->mapping.at(src)][this->mapping.at(dest)];
    }

    /* --------------------------------- Setters -------------------------------- */

    template <typename RecordType>
    void Graph<RecordType>::addNode(const Node<RecordType> *node)
    {
        // insert a new node to the mapping
        this->mapping.insert({node, this->numNodes++});
        this->nodes.push_back(node);

        // increase the size of the adjacency matrix
        for (auto &vec : this->adjacencyMatrix)
            vec.push_back(false); /** @todo check why the type isn't being inferred here */

        this->adjacencyMatrix.push_back(std::vector<int>(numNodes, 0)); // new row
    }

    template <typename RecordType>
    void Graph<RecordType>::addEdge(const Node<RecordType> *src, const Node<RecordType> *dest)
    {
        this->adjacencyMatrix[this->mapping[src]][this->mapping[dest]] = 1;
        this->adjacencyMatrix[this->mapping[dest]][this->mapping[src]] = 1;
    }

    template <typename RecordType>
    void Graph<RecordType>::addEdge(const Node<RecordType> *src, const Node<RecordType> *dest, int weight)
    {
        this->adjacencyMatrix[this->mapping[src]][this->mapping[dest]] = weight;
        this->adjacencyMatrix[this->mapping[dest]][this->mapping[src]] = weight;
    }

    /* ---------------------------- General functions --------------------------- */

    template <typename RecordType>
    void Graph<RecordType>::print() const
    {
        std::ostringstream ss;
        ss << "[\n";
        for (int i = 0; i < this->numNodes; i++)
        {

            ss << "[";

            for (int j = 0; j < this->numNodes; j++)
            {
                ss << this->adjacencyMatrix[i][j];
                if (j != this->numNodes - 1)
                    ss << " ";
            }

            ss << "]";

            if (i != this->numNodes - 1)
                ss << ",";

            ss << "\n";
        }
        ss << "]";

        std::cout << ss.str() << std::endl;
    }
}

/* -------------------------------------------------------------------------- */
/*                       Explicit template instantiation                      */
/* -------------------------------------------------------------------------- */
template class graph::Graph<Record>;