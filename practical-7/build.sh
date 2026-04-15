#!/usr/bin/bash

g++ ./src/graph/Graph.cpp ./src/graph/traversal.cpp ./src/graph/kruskal.cpp ./src/graph/prims.cpp ./src/graph/dijkstra.cpp ./src/utils/DisjointSet.cpp ./src/main.cpp -I./include -o ./build/graphs