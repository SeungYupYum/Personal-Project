# Summation Puzzle (Recursion)

## Description

The goal of this project is solving summation puzzle with using the concept of recursion. The summation puzzle is to complete by substituting numbers in each letter so that the expression holds in the form of word 1 + word 2 = word 3. For example, **WEB + CAT = BAD** can be solved where **W = 4, E = 0, B = 7, C = 3, A = 2, T = 1, D = 8**. Then the equation is **407 + 321 = 728**.

## Features

- **puzzleVerifier**: s1 and s2 is words that will be left side of the equation, and s3 is a word that will be the right side of the equation. The unordered_map, mapping, contains letters and numbers for the solution. This function checkes the solution works. If it works, then return true, otherwise, return false.
  ```cpp
  bool puzzleVerifier(const std::string& s1, const std::string& s2, const std::string& s3, const std::unordered_map<char, unsigned> &mapping)

- **Recursion**: It named as recursion since it is the core function to find the acutal solution.. It will be used in the other function by call this function so that work as recursive function. For effectiveness, It uses <deque> to push and pop from both front and end. The base case is when there is no more unused letter. When there is no more unused letter, then puzzleVerifier returns true/false. Through recursive call and call-stack, it keep realign <deque> to fine the solution.
  ```cpp
  bool Recursion(const std::string &s1, const std::string &s2, const std::string &s3, std::unordered_map<char, unsigned> &mapping, std::deque <unsigned int> &Unused_num, std::deque <char> &Unused_letter, std::deque <unsigned int> &Used_num, std::deque <char> &Used_letter)

- **puzzleSolver**: It extracts all the unique letters from the s1, s2 and s3, and then call the Recursion function with appropriate pre-made data. This function returns the Recursion function.
  ```cpp
  bool puzzleSolver(const std::string &s1, const std::string &s2, const std::string &s3, std::unordered_map<char, unsigned> &mapping)

