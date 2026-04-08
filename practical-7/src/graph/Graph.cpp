// Header to be implemented
#include <graph/Graph.hpp>

// External dependencies
#include <vector>
#include <iostream>
#include <sstream>

// Internal dependencies
#include <data/Record.hpp>

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
    const Node<RecordType> *Graph<RecordType>::getNode(int i) const
    {
        return this->nodes[i];
    }

    template <typename RecordType>
    std::vector<const Node<RecordType> *> Graph<RecordType>::getNeighbours(const Node<RecordType> *node) const
    {
        std::vector<const Node<RecordType> *> neighbours;

        const std::vector<bool> &adjacencyRow = this->adjacencyMatrix[this->mapping.at(node)];

        for (int i = 0; i < adjacencyRow.size(); i++)
            if (adjacencyRow[i])
                neighbours.push_back(this->nodes[i]);

        return neighbours;
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

        this->adjacencyMatrix.push_back(std::vector<bool>(numNodes, false)); // new row
    }

    template <typename RecordType>
    void Graph<RecordType>::addEdge(const Node<RecordType> *src, const Node<RecordType> *dest)
    {
        this->adjacencyMatrix[this->mapping[src]][this->mapping[dest]] = true;
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
                ss << this->adjacencyMatrix[i][j] ? 1 : 0;
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