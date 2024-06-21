#ifndef __ICS46_LL_STACK_HPP
#define __ICS46_LL_STACK_HPP

#include <stdexcept>

class StackEmptyException : std::runtime_error 
{
public:
  StackEmptyException(const std::string &err) : std::runtime_error(err) 
  {

  }
};

// This is the LLStack class you will be implementing for this project.
// Remember to see the write-up for more details!
template <typename Object> 
class LLStack 
{
private:
  struct Node
  {
    Node* next;
    Object data;
  };
  size_t sizenode;
  Node* head;

public:
  // constructor
  LLStack();

  // copy constructor (remember, deep copy!)
  LLStack(const LLStack &st);

  // assignment operator (remember, deep copy!)
  LLStack &operator=(const LLStack &st);

  // destructor
  ~LLStack();

  size_t size() const noexcept;
  bool isEmpty() const noexcept;

  Object &top();
  const Object &top() const;

  void push(const Object &elem);
  void pop();
};

template <typename Object> 
LLStack<Object>::LLStack() 
{
  sizenode = 0;
  head = NULL;
}

template <typename Object> 
LLStack<Object>::LLStack(const LLStack &st) 
{
  if(st.head == NULL)
  {
    head = NULL;
    sizenode = 0;
  }
  else
  {
    sizenode = st.sizenode;
    head = new Node;
    head -> data = st.head->data;
    Node* current = head;

    for(Node *old_node = st.head->next; old_node != NULL; old_node=old_node->next)
    {
      current -> next = new Node;
      current = current -> next;
      current -> data = old_node -> data;
    }
    current->next = NULL;
  }
}

template <typename Object>
LLStack<Object> &LLStack<Object>::operator=(const LLStack &st) 
{
  if (this == &st)
  {
    return *this; //if it is same, just retrun same thing.
  }
  else if (this != &st) //if it is not same, then make it empty if it is not empty.
  {
    if (head != NULL)
    {
      Node * current = head;
      while(current != NULL)
      {
        Node * temp = current;
        current = current -> next;
        delete temp;
      }
      head = NULL;
    }
  }

  if (st.head == NULL) //if it is empty, then make head is null, and size is 0.
  {
    head = NULL;
    sizenode = 0;
    return *this;
  }
  else // After make it empty, copy all st to new stack. Same as Copy Constructor (maybe)
  {
    sizenode = st.sizenode;
    head = new Node;
    head -> data = st.head->data;
    Node* current = head;

    for(Node *old_node = st.head->next; old_node != NULL; old_node=old_node->next)
    {
      current -> next = new Node;
      current = current -> next;
      current -> data = old_node -> data;
    }
    current->next = NULL;
  }
  return *this;
}

template <typename Object> 
LLStack<Object>::~LLStack() 
{ 
  Node * temp = head;
  while (temp != NULL) 
  {
    head = head -> next;
    delete temp;
    temp = head;
  }

  head = NULL;
  sizenode = 0;
}

template <typename Object> 
size_t LLStack<Object>::size() const noexcept 
{
  return sizenode;
}

template <typename Object> 
bool LLStack<Object>::isEmpty() const noexcept 
{ 
  return (head == NULL);
}

template <typename Object> 
Object &LLStack<Object>::top() 
{ 
  if (isEmpty()==1) 
  {
    throw StackEmptyException ("EMPTY");
  }
  else
  {
    return head -> data;
  }

}

template <typename Object> 
const Object &LLStack<Object>::top() const 
{
  if (isEmpty()==1) 
  {
    throw StackEmptyException ("EMPTY");
  }
  else
  {
    return head->data; //temp might change if above works
  }
}

template <typename Object> 
void LLStack<Object>::push(const Object &elem) 
{
  Node* newNode = new Node;
  newNode->data = elem;
  newNode->next = head;
  head = newNode;

  sizenode ++;
}

template <typename Object> 
void LLStack<Object>::pop() 
{
  if (this->sizenode == 0) // clear
  {
    throw StackEmptyException ("EMPTY");
  }
  else
  {
    Node* temp = head;
    head = head->next;

    delete temp;
    sizenode --;
  }
}

#endif
