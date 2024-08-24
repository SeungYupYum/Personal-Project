# Postfix Calculator (Stack)

## Description

Postfix Calculator is one of the most famous data structure project. After implementing Stack, postfix calculator is done by using it. **LLStack.hpp** contains the actual data structure of stack, and **postfixCalc.cpp** contains the postfix calculator part.

## Feature

### Implementation of Stack

- **Constructor**: Constructor.
  ```cpp
  LLStack<Object>::LLStack()

- **Copy Constructor**: Deep copy constructor.
  ```cpp
  LLStack<Object>::LLStack(const LLStack &st)

- **Assignment Operator**: Deep copy. It will be called when an existing LLStack object is assigned to a new one.
  ```cpp
  LLStack<Object> &LLStack<Object>::operator=(const LLStack &st)
  
- **Destructor**: Destructor.
  ```cpp
  LLStack<Object>::~LLStack() 

- **Size**: It returns the size of stack. In other words, return the number of element in current stack.
  ```cpp
  size_t LLStack<Object>::size() const noexcept 

- **Is Empty**: It returns true if the stack is empty, otherwise, return false.
  ```cpp
  bool LLStack<Object>::isEmpty() const noexcept 

- **Top**: It returns the top element.
  ```cpp
  Object &LLStack<Object>::top(), const Object &LLStack<Object>::top() const

- **Push**: It inserts the new element at the top.
  ```cpp
  void LLStack<Object>::push(const Object &elem) 

- **Pop**: It removes the top element.
  ```cpp
  void LLStack<Object>::pop(const Object &elem) 

### Postfix Calculator

- **Postfix Calculator**: The entry is vector that consist with two categories: std::string operator (“+”, “-”, “*”, “/”) and std::string integer ("1", "2", "3" etc). Simply, with the vector input, read it first to last. If the input is std::string integer, push it into stack, if the input is std::string operator, apply the operator to the top two elements in the stack, and then push back the result into stack. If the operator is not associative, then the very top element is the second parameter to the operator. After finish calculating, if there is only one element in the stack, then that is the final answer, so this function will return that final answer. Otherwise, throw a CannotEvaluateException.
  ```cpp
  unsigned postfixCalculator(const std::vector<std::string> & entries)
