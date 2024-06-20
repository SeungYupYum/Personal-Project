#include "register_allocation.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
#include <vector>
using namespace RA;

// assignRegisters
//
// This is where you implement the register allocation algorithm
// as mentioned in the README. Remember, you must allocate at MOST
// d(G) + 1 registers where d(G) is the maximum degree of the graph G.
// If num_registers is not enough registers to accomodate the passed in
// graph you should return an empty map. You MUST use registers in the
// range [1, num_registers] inclusive.

struct Node
{
  std::string vertex;
  int degree;
  bool operator<(const Node& other) const 
	{
			return degree < other.degree;
  }
};

RegisterAssignment RA::assignRegisters(const std::string &path_to_graph, int num_registers) noexcept 
{
  InterferenceGraph<Variable> ig = CSVReader::load(path_to_graph);

  // TODO: You implement this!
  /* 
  Back tracking problem
  Need : map, used vertex set, unused vertex set, used color set, unused color set

  get vertex list, and sorting as decsending order, set 'V'
  get number list (possible color), order does not really matter, set 'N'
  take out first vertex from the V, mapping with first element of N (need boolean function to check mapping is poissible or not)
  take out second vertex, try to mapping with first, if it is not posssible, then second
  the logical order of mapping second ~ end vertex :
  1. check currently taking out vertex is adjacent of used vertex set
  1 - 1 remove adjacent's color from available color list
  1 - 2 if it is possible color from used color, then mapp with it
  1 - 3 if it is not available, then assign new color

  *check the highest degree, and + 1. if it is more than num_registers, then return just empty map.
  */

  std::unordered_map <std::string, int> solution;
  std::unordered_set <std::string> Used_vertex_set;
  std::priority_queue <Node> pq; // priority queue to make list of  list
  std::vector <Node> Sorted_vertex_list; // need to be sorted, in terms of degree (max degree to min degree)
  std::vector <int> Sorted_color_list; // need to be sorted ascending order to only use back and pop to avoid interating
  struct Node Degree_mapping;

  for(auto element : ig.vertices()) // mapping vertex to its degree, put it in max heap
  {
    Degree_mapping.vertex = element;
    Degree_mapping.degree = ig.degree(element);
    pq.push(Degree_mapping);
  }

  if(((pq.top().degree + 1) > num_registers) || (num_registers == 0)) // if the max degree + 1 is greater than num_registers, then return empty map
  {
    return solution;
  }
  else
  {
    while(!pq.empty()) // push everything to Sorted_vertex_list, after this, Sorted_vertex_list = vertex list in terms of degree in decsending order
    {
      Sorted_vertex_list.push_back(pq.top());
      pq.pop();
    }

    for(int i = Sorted_vertex_list.front().degree + 1; i >= 1; i--) // put [max degree + 1 ~ 1] into sorted color list, reversed order since to avoid iterate
    {
      Sorted_color_list.push_back(i);
    }

    if(Sorted_vertex_list.size() == 1)
    {
      solution[Sorted_vertex_list[0].vertex] = Sorted_color_list.back();
      return solution;
    }
    else if(Sorted_vertex_list.size() == 0)
    {
      return solution;
    }
    else
    {
      for(unsigned i = 0; i < Sorted_vertex_list.size(); i++) // outer loop for current vertex, start from front
      {
        if(Used_vertex_set.count(Sorted_vertex_list[i].vertex) == 1)
        {
          continue;
        }
        else
        {
          solution[Sorted_vertex_list[i].vertex] = Sorted_color_list.back();
          Used_vertex_set.insert(Sorted_vertex_list[i].vertex);

          std::unordered_set <std::string> Current_vertex_set;
          Current_vertex_set.insert(Sorted_vertex_list[i].vertex);

          bool isAdjacent = false;

          for(unsigned j = i + 1; j < Sorted_vertex_list.size(); j++)
          {
            if(Used_vertex_set.count(Sorted_vertex_list[j].vertex) == 1)
            {
              continue;
            }
            else
            {
              for(auto element : Current_vertex_set) // mapping vertex to its degree, put it in max heap
              {
                if(ig.neighbors(element).count(Sorted_vertex_list[j].vertex) == 1)
                {
                  isAdjacent = true;
                  break;
                }
              }

              if(isAdjacent == false)
              {
                solution[Sorted_vertex_list[j].vertex] = Sorted_color_list.back();
                Used_vertex_set.insert(Sorted_vertex_list[j].vertex);
                Current_vertex_set.insert(Sorted_vertex_list[j].vertex);
                isAdjacent = false;
              }
              else
              {
                isAdjacent = false;
              }
            }
          }
          Current_vertex_set.clear();
        }
        Sorted_color_list.pop_back();
      }
      return solution;
    }
  }
}
      /* if(Used_vertex_set.count(Sorted_vertex_list[i].vertex) == 1) // if it is alreday mapped, skip
      {
        continue;
      }
      else // not mapped, then map 
      {
        solution[Sorted_vertex_list[i].vertex] = Sorted_color_list.back(); // mapping
        Used_vertex_set.insert(Sorted_vertex_list[i].vertex); //put it into used vertex set

        std::unordered_set <std::string> Current_vertex_set; // current vertex set for current outter loop
        Current_vertex_set.insert(Sorted_vertex_list[i].vertex);
        bool isAdjacent = false;

        if(Sorted_vertex_list.size() != 1)
        {
          for(unsigned j = i + 1; j < Sorted_vertex_list.size(); j++) // inner loop for coloring all vetex that is not adjacent, start from back to reduce time(failed)
          {
            if(Used_vertex_set.count(Sorted_vertex_list[j].vertex) == 0) //if it is not used vertex,
            {           
              for(auto element : Current_vertex_set) // mapping vertex to its degree, put it in max heap
              {
                if(ig.neighbors(element).count(Sorted_vertex_list[j].vertex) == 1)
                {
                  isAdjacent = true;
                  break;
                }
              }
              if(isAdjacent == false)
              {
                solution[Sorted_vertex_list[j].vertex] = Sorted_color_list.back(); //then map them
                Used_vertex_set.insert(Sorted_vertex_list[j].vertex);
                Current_vertex_set.insert(Sorted_vertex_list[j].vertex);
              }
              else
              {
                continue;
              }
            }
            else
            {
              continue;
            }
          }
        }
        else
        {
          return solution;
        }
      }
    Sorted_color_list.pop_back(); // pop the lowest integer since it was already used
    }
  return solution;
  }
}*/