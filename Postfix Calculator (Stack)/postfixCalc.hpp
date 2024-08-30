#ifndef __PROJ_0_POSTFIX_CALCULATOR
#define __PROJ_0_POSTFIX_CALCULATOR

#include <stdexcept>
#include <string>
#include <vector>

// This exception should be thrown whenever the postfix equation
// cannot be evaluated.
class CannotEvaluateException : std::runtime_error {
public:
  CannotEvaluateException(const std::string &err) : std::runtime_error(err) {}
};

unsigned postfixCalculator(const std::vector<std::string> &entries);

#endif
