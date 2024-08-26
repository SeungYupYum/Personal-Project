# Welsh-Powell Coloring (Graph)

## Description

It is combined with two parts: Interference Graph and Register Allocation. The main concept of this project is implementing graph and solving problem called Welsh-Powell Coloring with using graph.
This is the problem of finding the least number of colors needed to color all vertices so that the vertices in adjaceont relation are not the same color.

### Environmental Setup
- **CSVReader**: This is simply a utility for creating an InterferenceGraph type from a graph file.
- **IGWriter**: This file contains functionality for writing a colored InterferenceGraph to a file in the DOT format. The utility `dot` can be used to view the corresponding file.
  ```cpp
     Example use from a GTest:

    const std::string GRAPH = "gtest/graphs/four.csv";

    InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);

    const RegisterMapping& mapping =  assignRegisters(ig,
   3);

    IGWriter::write(ig, "gtest/graphs/four.dot", mapping);

    Then you can use the command:

      dot gtest/graphs/four.dot -o gtest/graphs/four.png -Tpng

    Which will output a PNG of your colored graph that you can open. Note this
   requires the graphviz package:

      `sudo apt install graphviz` (note you made need to run `sudo apt update`
   first.)

     You can view the PNG in VS Code.

## Feature of Interference Graph

In order to achieve efficiency, the form of graph is adjacent list. It is done by using **std::unordered_map <T, std::unordered_set<T>>** and **adjacent_list;std::unordered_set <T> vertex_set**.

- **Constructor**: General Constructor.
  ```cpp
  template <typename T> InterferenceGraph<T>::InterferenceGraph()

- **Destructor**: General Destructor. Since it uses built-in unordered map, which has automatical destructor, it does not strictly required.
  ```cpp
  template <typename T> InterferenceGraph<T>::~InterferenceGraph()

- **Neighbors**: Returns a set containing all the neighbors of a given vertex. If the vertex is not present in the graph, it throws an UnknownVertexException.
  ```cpp
  std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const 

- **Verticies**: Returns the set of unique verticies.
  ```cpp
  std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept 

- **Number of Verticies**: Returns the number of unique verticies.
  ```cpp
  unsigned InterferenceGraph<T>::numVertices() const noexcept

- **Number of Edges**: Returns the number of edges.
  ```cpp
  unsigned InterferenceGraph<T>::numEdges() const noexcept 

- **Add Edge**: This function will be called in the load() function, once for each line in the corresponding CSV file. This function should add an undirected edge between `v` and `w`, representing an interference between the variable `v` and 
  variable `w`. If either `v` or `w` is not present in the graph, it throws an UnknownVertexException.
  ```cpp
  void InterferenceGraph<T>::addEdge(const T &v, const T &w) 

- **Remove Edge**: This function should remove an undirected edge from your interference graph. If the edge doesn't exist it throws an UnknownEdgeException. If either of the vertices aren't in the graph it throws an UnknownVertexException.
  ```cpp
  void InterferenceGraph<T>::removeEdge(const T &v, const T &w) 

- **Add Vertex**: Called in the load() function once for each vertex in a given row of the CSV. That is, if the row indicates an edge like x,y then addVertex("x") and addVertex("y") will both be called. If the line is a lone vertex like x then just addVertex("x") will be called. This function simply adds a vertex with no neighbors to the graph. The contract with the caller is that `vertex` will exist in the graph after the call.
  ```cpp
  void InterferenceGraph<T>::addVertex(const T &vertex) 

- **Remove Vertex**: Removes a vertex from interference graph. After this function is run the vertex should be completely removed from the graph. If the vertex already does not exist it throws an UnknownVertexException.
  ```cpp
  void InterferenceGraph<T>::removeVertex(const T &vertex)

- **Interferes**: Returns true if there is an interference (adjacent relation) between vertex v and vertex w. If either v or w are not in the graph it throws an UnknownVertexException.
  ```cpp
  bool InterferenceGraph<T>::interferes(const T &v, const T &w) const 

- **Degree**: Return the degree of vertex v. If it doesn't exist in the graph it throws an UnknownVertexException.
  ```cpp
  unsigned InterferenceGraph<T>::degree(const T &v) const

## Welsh-Powell Coloring Problem

The approach is quite simple. After loadindg, get the vertices list and sort them as descending order by their degree. From the sorted list, try to color first vertex that has max degree, and then color all the vertices with the same color that are not in the adjacent relation with the first max degree vertex. After finish, color second vertex that is 1. not colored yet, 2. next max degree with the different color, and color all vertext that is not adjacent list with the second vertex. The number of color that it can be used in this problem is at most d(G) + 1, which means if the maximum degree of verticies list is 5, then the number of color that it can be used in this problem is 6. If it is possible, then return the solution, if it is not possible then return empty unordered_map.

 ```cpp
 RegisterAssignment RA::assignRegisters(const std::string &path_to_graph, int num_registers) noexcept 

