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

    // Node(Object new_data, Node* new_next) : data(new_data), next(new_next) { }
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

  // We have two top() functions.  The first gets called if your LLStack is not
  // a const, while the latter gets called on a const LLStack
  // (the latter might occur via const reference parameter, for instance).
  // Be sure to test both!  It is important when testing to ensure that
  // EVERY funtion gets called and tested!
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

  // TODO: Fill in your constructor implementation here.
}

template <typename Object> 
LLStack<Object>::LLStack(const LLStack &st) 
{
  // TODO: Fill in your copy constructor implementation here.
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
  // TODO: Fill in your assignment operator implementation here.
  // return *this; // Stub so this function compiles without implementation.
}

template <typename Object> 
LLStack<Object>::~LLStack() 
{ // clear
  Node * temp = head;
  while (temp != NULL) 
  {
    head = head -> next;
    delete temp;
    temp = head;
  }

  head = NULL;
  sizenode = 0;
  // TODO: Fill in your destructor implementation here.
}

template <typename Object> 
size_t LLStack<Object>::size() const noexcept 
{
  // TODO: Fill in your size() implementation here.
  // return 0; // Stub so this function compiles without an implementation.
  return sizenode;
}

template <typename Object> 
bool LLStack<Object>::isEmpty() const noexcept 
{ // clear
  // TODO: Fill in your isEmpty() implementation here.
  // return true; // Stub so this function compiles without an implementation.
  return (head == NULL);
}

template <typename Object> 
Object &LLStack<Object>::top() 
{ // clear
  // TODO: Fill in your top() implementation here.
  // The following is a stub just to get the template project to compile.
  // You should delete it for your implementation.
  // return DELETE_ME;
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
  // TODO: Fill in your const top() implementation here.
  // The following is a stub just to get the template project to compile.
  // You should delete it for your implementation.
  // return DELETE_ME;
  if (isEmpty()==1) 
  {
    throw StackEmptyException ("EMPTY");
  }
  else
  {
    //const Object temp = head -> data;
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
  // TODO: Fill in your push() implementation here.
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

  // TODO: Fill in your pop() implementation here.
}

#endif
