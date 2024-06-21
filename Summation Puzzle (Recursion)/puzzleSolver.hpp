#ifndef __PUZZLE_SOLVER__HPP
#define __PUZZLE_SOLVER__HPP

#include <unordered_map>
#include <string>

// PART 1 - Summation Puzzle Verifier. See project write-up for details.
bool puzzleVerifier(const std::string& s1, const std::string& s2, const std::string& s3, const std::unordered_map<char, unsigned> & mapping);

// PART 2 - Summation Puzzle Solver. See project write-up for details.
bool puzzleSolver(const std::string& s1, const std::string& s2, const std::string& s3, std::unordered_map<char, unsigned> & mapping);


#endif