#ifndef __INTERFERENCE_GRAPH__HPP
#define __INTERFERENCE_GRAPH__HPP

#include <exception>
#include <string>
#include <unordered_set>
#include <stdexcept>

#include <vector>
#include <unordered_map>

class UnknownVertexException : public std::runtime_error {
public:
  UnknownVertexException(const std::string &v)
      : std::runtime_error("Unknown vertex " + v) {}
};

class UnknownEdgeException : public std::runtime_error {
public:
  UnknownEdgeException(const std::string &v, const std::string &w)
      : std::runtime_error("Unknown edge " + v + " - " + w) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file. Though this class is templated, because of the usage of exceptions
// UnknownVertexException and UnknownEdgeException it will
// ONLY be tested with strings.
template <typename T> class InterferenceGraph {
public:
  // Custom type used to represent edges. This is mainly
  // used in the utility function for reading and writing
  // the graph structure to/from files. You don't need to use it.
  using EdgeTy = std::pair<T, T>;

  InterferenceGraph();

  ~InterferenceGraph();

  void addEdge(const T &v, const T &w);

  void addVertex(const T &vertex);

  void removeEdge(const T &v, const T &w);

  void removeVertex(const T &vertex);

  std::unordered_set<T> vertices() const noexcept;

  std::unordered_set<T> neighbors(const T &vertex) const;

  unsigned numVertices() const noexcept;

  unsigned numEdges() const noexcept;

  bool interferes(const T &v, const T &w) const;

  unsigned degree(const T &v) const;

private:
  // Private member variables here.
  std::unordered_map <T, std::unordered_set<T>> adjacent_list;
  std::unordered_set <T> vertex_set;
  unsigned int num_vertex;
  unsigned int num_edge;
  //map<T, set<T> >
};

template <typename T> InterferenceGraph<T>::InterferenceGraph() 
{
  num_edge = 0;
  num_vertex = 0;
}

template <typename T> InterferenceGraph<T>::~InterferenceGraph() 
{

}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const 
{
  if(vertex_set.count(vertex) == 0)
  {
    throw UnknownVertexException ("No Vertex");
  }
  else
  {
    return adjacent_list.at(vertex);
  }
}


template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept 
{
  return vertex_set;
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept 
{
  return num_vertex;
}

template <typename T> 
unsigned InterferenceGraph<T>::numEdges() const noexcept 
{
  return num_edge;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &v, const T &w) 
{
  if((vertex_set.count(v) == 0) || (vertex_set.count(w) == 0))
  {
    throw UnknownVertexException ("No Vertex");
  }
  else
  {
    adjacent_list.at(v).insert(w); //[]
    adjacent_list.at(w).insert(v); //[]
    num_edge ++;
  }
}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &v, const T &w) 
{
  if((vertex_set.count(v) == 0) || (vertex_set.count(w) == 0))
  {
    throw UnknownVertexException ("No Vertex");
  }
  else
  {
    //go check map[v] and map[w], it would return set, and check if opposite vertex exist
    if (adjacent_list.at(v).find(w) != adjacent_list.at(v).end())  //[]
    {
      adjacent_list.at(v).erase(w); // []
    }
    else 
    {
      throw UnknownEdgeException ("No edge", "v");
      return;
    }

    if(adjacent_list.at(w).find(v) != adjacent_list.at(w).end()) // []
    {
      adjacent_list.at(w).erase(v); // []
      num_edge --;
    }
    else
    {
      throw UnknownEdgeException ("No edge", "w");
      return;
    }
  }

}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) 
{
  if(vertex_set.count(vertex) == 1)
  {
    return;
  }
  else
  {
    vertex_set.insert(vertex);
    std::unordered_set <T> empty;
    adjacent_list[vertex] = empty;
    num_vertex ++;
  }
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex) 
{
  if(vertex_set.count(vertex) == 0)
  {
    throw UnknownVertexException ("No Vertex");
  }
  else
  {
    vertex_set.erase(vertex);
    adjacent_list.erase(vertex);

    //go through all sets(value) and then remove vertex if it exists.
    for (const auto& element : vertex_set)
    {
      adjacent_list.at(element).erase(vertex);
      num_edge --;
    }

    num_vertex --;
  }
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &v, const T &w) const 
{
  if((vertex_set.count(v) == 0) || (vertex_set.count(w) == 0))
  {
    throw UnknownVertexException ("No Vertex");
  }
  else
  {
    if((adjacent_list.at(v).count(w) == 1) && (adjacent_list.at(w).count(v) == 1))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}

template <typename T> 
unsigned InterferenceGraph<T>::degree(const T &v) const 
{
  if(vertex_set.count(v) == 0)
  {
    throw UnknownVertexException ("No Vertex");
  }
  else
  {
    return adjacent_list.at(v).size();
  }
}

#endif
