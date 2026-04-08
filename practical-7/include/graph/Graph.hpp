#ifndef GRAPH_H
#define GRAPH_H

// External dependencies
#include <vector>
#include <unordered_map>

namespace graph
{
    template <typename RecordType>
    struct Node
    {
        /** @todo I can probably add some metadata here so that it's not just an unncessary wrapper **/
        const RecordType *record;
    };

    template <typename RecordType>
    class Graph
    {
    private:
        int numNodes;                                              // number of nodes currently in the graph
        std::vector<const Node<RecordType> *> nodes;               // nodes in the graph (int -> const Node<RecordType>*)
        std::unordered_map<const Node<RecordType> *, int> mapping; // a mapping between node pointers and integers (const Node<RecordType>* -> int)
        std::vector<std::vector<bool>> adjacencyMatrix;            // adjacency matrix for the graph

    public:
        /* ------------------------------- Constructor ------------------------------ */
        Graph();

        /* --------------------------------- Getters -------------------------------- */

        /**
         * @brief Get the number of nodes in the graph
         *
         * @return int The number of nodes in the graph
         */
        int getNumNodes() const;

        /**
         * @brief Get the i-th Node
         *
         * @return const Node<RecordType>* i-th Node as a pointer
         */
        const Node<RecordType> *getNode(int) const;

        /**
         * @brief Get the neighbours of a node
         *
         * @return std::vector<const Node<RecordType>*> Neighbours of the node
         */
        std::vector<const Node<RecordType> *> getNeighbours(const Node<RecordType> *) const;

        /* --------------------------------- Setters -------------------------------- */

        void addNode(const Node<RecordType> *);
        void addEdge(const Node<RecordType> *, const Node<RecordType> *);

        /* ---------------------------- General functions --------------------------- */
        void print() const;
    };
}

#endif