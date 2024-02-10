# QVM (Virtual Quantum Machine)
Virtual Quantum Machine: This is a lofi implementation of simulation of Virtual Quantum Machine designed to solve the travelling salesman problem (TSP). The TSP is a classical optimization problem where the goal is to find the shortest possible path that visits a set of cities and returns to the starting city. This virtual machine uses cycles with different behaviors to explore and find optimal path in a graph.
Point Class (Point.h, Point.cpp):

- Represents a point in a two-dimensional space with x and y coordinates.
- Provides a method for calculating the relative measure (Euclidean distance) between two points.
- Includes a ToString method for converting a point to a string representation.
- Utils Class (Point.h, Point.cpp):

A utility class with static methods for converting integers, unsigned long integers, and doubles to strings.
Graph Class (Graph.h, Graph.cpp):

- Represents a graph, where each node is a point.
- Includes methods for calculating the number of possible paths, the length of the shortest path, and the overall --quality (measure) of the graph.
- Defines a Copy method for copying a graph.
  
Cycle Class (Cycle.h, Cycle.cpp):

- Represents a cycle in the quantum machine.
- Contains a Graph object, a measure of quality, and the number of visits.
- Defines methods for initializing, copying, and updating the cycle's memory.
- PointArray Class (PointArray.h, PointArray.cpp):

A specialization of the std::vector class for managing an array of points.
Includes methods for calculating the number of possible paths, the length of the shortest path, and the overall quality (measure) of the path.

MachineInstance Class (Machine.h, Machine.cpp):

The main class representing the virtual quantum machine.
Contains an array of cycles, a graph to solve (TSP), and methods for starting, stopping, and processing the cycles.
Implements a simulation where active cycles try to find better solutions, investigating cycles explore random solutions, and inactive cycles may be influenced by active cycles.
