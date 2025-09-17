# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Djikstra)

# Add an executable target
add_executable(Djikstra dijkstra.cpp)

add_executable(Graph graph.cpp)
 