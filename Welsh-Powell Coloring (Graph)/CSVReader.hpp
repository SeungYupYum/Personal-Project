#ifndef CSV_READER_H
#define CSV_READER_H

#include "InterferenceGraph.hpp"
#include "register_allocation.hpp"
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace RA;

class CSVReader {
public:
  // It's used to read an edge in graph file.
  static std::vector<std::string> readRow(std::string &csv_line);

  //
  // This function iterates through the file at `graph_path`
  // line by line, adding each edge to this InterferenceGraph.

  static InterferenceGraph<Variable> load(const std::string &graph_path);
};

#endif