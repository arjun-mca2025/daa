// External dependencies
#include <iostream>
#include <vector>
#include <ctime>
#include <random>

// Internal dependencies
#include <data/Record.hpp>
#include <graph/Graph.hpp>
#include <graph/traversal.hpp>

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
        sampleGraph.addEdge(sampleGraph.getNode(randomIndex(size)), sampleGraph.getNode(randomIndex(size)));

    // Print the graph adjacency matrix
    std::cout << "Adjacency Matrix: " << std::endl;
    sampleGraph.print();

    std::cout << "BFS Traversal of the graph: \t";
    graph::bfs(sampleGraph, sampleGraph.getNode(0));

    std::cout << "DFS Traversal of the graph: \t";
    graph::dfs(sampleGraph, sampleGraph.getNode(0));
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