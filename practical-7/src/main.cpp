// External dependencies
#include <iostream>
#include <vector>
#include <ctime>
#include <random>

// Internal dependencies
#include <data/Record.hpp>
#include <graph/Graph.hpp>
#include <graph/Node.hpp>
#include <graph/Edge.hpp>

#include <graph/traversal.hpp>
#include <graph/mst.hpp>
#include <graph/sssp.hpp>

/* -------------------------------------------------------------------------- */
/*                            Forward Declarations                            */
/* -------------------------------------------------------------------------- */

int randomIndex(int);

/* -------------------------------------------------------------------------- */
/*                                Main function                               */
/* -------------------------------------------------------------------------- */
int main()
{
    // Initialize the seed for random number generation
    std::srand(std::time(0));

    std::vector<std::string> names{"Arjun", "Aditya", "Aman", "Saumya", "Shreya", "Shruti", "Reeta", "Reena", "John", "Jacob"};

    int size = 5;
    auto sampleGraph = graph::Graph<Record>();
    for (int i = 0; i < size; i++)
        sampleGraph.addNode(new graph::Node<Record>{new Record{names[i % names.size()], static_cast<float>(rand()) / RAND_MAX * 30 + 10}});

    for (int i = 0; i < 30; i++)
        sampleGraph.addEdge(sampleGraph.getNode(randomIndex(size)), sampleGraph.getNode(randomIndex(size)), static_cast<int>(round(static_cast<float>(rand()) * 10 / RAND_MAX)));

    // Print the graph adjacency matrix
    std::cout << "Adjacency Matrix: " << std::endl;
    sampleGraph.print();

    std::cout << "BFS Traversal of the graph: \t";
    graph::bfs(sampleGraph, sampleGraph.getNode(0));

    std::cout << "DFS Traversal of the graph: \t";
    graph::dfs(sampleGraph, sampleGraph.getNode(0));

    std::cout << "MST using Kruskal's algorithm: \t";
    auto kruskalMst = graph::kruskal(sampleGraph);
    kruskalMst.print();

    std::cout << "MST using Prim's algorithm: \t";
    auto primsMst = graph::prims(sampleGraph);
    primsMst.print();

    std::cout << "SSSP using Dijkstra's algorithm from the first node: \t";
    auto spt = graph::dijkstra(sampleGraph, sampleGraph.getNode(0));
    spt.print();
}

/**
 * @brief Generate a random index for a size-sized vector/array
 *
 * @param size Size of the vector/array
 * @return int A random index
 */
int randomIndex(int size)
{
    return rand() % size;
}