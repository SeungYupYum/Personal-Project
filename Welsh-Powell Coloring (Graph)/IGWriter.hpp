#ifndef IG_WRITER_H
#define IG_WRITER_H

#include "InterferenceGraph.hpp"
#include "register_allocation.hpp"
#include <string>

using namespace RA;

class IGWriter {
public:
  static void write(const InterferenceGraph<Variable> &IG,
                    const std::string &path,
                    const RegisterAssignment &registerAssignment);
};

#endif