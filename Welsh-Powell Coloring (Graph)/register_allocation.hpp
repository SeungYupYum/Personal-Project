#ifndef __PROJ_6__HPP
#define __PROJ_6__HPP

#include <string>
#include <unordered_map>

namespace RA {

using Variable = std::string;
using Register = int;
using RegisterAssignment = std::unordered_map<Variable, Register>;

RegisterAssignment assignRegisters(const std::string &path_to_graph,
                                   int num_registers) noexcept;

};

#endif