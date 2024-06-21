#ifndef _PRIORITY_QUEUE_HPP
#define _PRIORITY_QUEUE_HPP

#include <stdexcept>
#include <vector>
#include <cmath> //for swap

class PriorityQueueEmptyException : public std::runtime_error {
public:
  PriorityQueueEmptyException(const std::string &err) : std::runtime_error(err) {}
};

template <typename Object> 
class MyPriorityQueue {
  private:

  std::vector <Object> Min_heap;
  size_t word_num;

  public:
    MyPriorityQueue();
    ~MyPriorityQueue();

    size_t size() const noexcept;
    bool isEmpty() const noexcept;

    void insert(const Object &elem);

    // Note:  no non-const version of this one.  This is on purpose because
    // the interior contents should not be able to be modified due to the
    // heap property.  This isn't true of all priority queues
    // min and extractMin should throw PriorityQueueEmptyException if the queue is
    // empty.
    const Object &min() const;
    bool isEqual(Object First, Object Second);
    void extractMin();
};

template <typename Object> MyPriorityQueue<Object>::MyPriorityQueue() 
{
  word_num = 0;
}

template <typename Object> MyPriorityQueue<Object>::~MyPriorityQueue()
{

}

template <typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
  return word_num;
}

template <typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
  if(word_num == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename Object>
bool MyPriorityQueue<Object>::isEqual(Object First, Object Second)
{
  if(!(First < Second) && !(Second < First))
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename Object>
void MyPriorityQueue<Object>::insert(const Object &elem)
{
  if(Min_heap.size() == 0)
  {
    Min_heap.push_back(elem);
    word_num ++;
  }
  else
  {
    Min_heap.push_back(elem); // inserting at leaf position, elem's index is current_index
    size_t Current_index = Min_heap.size() - 1; // index for elem
    word_num ++; //increase number of element

    size_t Parent_index;
    while(Current_index != 0)
    {
      if(Current_index % 2 == 0) // right child
      {
        Parent_index = (Current_index - 2) / 2;
        if(Min_heap[Current_index] < Min_heap[Parent_index])
        {
          std::swap(Min_heap[Parent_index], Min_heap[Current_index]);
          Current_index = Parent_index;
        }
        else
        {
          break;
        }
      }
      else // left child
      {
        Parent_index = (Current_index - 1) / 2;
        if(Min_heap[Current_index] < Min_heap[Parent_index])
        {
          std::swap(Min_heap[Parent_index], Min_heap[Current_index]);
          Current_index = Parent_index;
        }
        else
        {
          break;
        }
      }
    }
  }
  return;
}

template <typename Object> const Object &MyPriorityQueue<Object>::min() const
{
  if(word_num == 0)
  {
    throw PriorityQueueEmptyException ("EMPTY");
  }
  else
  {
    return Min_heap.front();
  }
}

template <typename Object> void MyPriorityQueue<Object>::extractMin()
{
  if(Min_heap.size() == 0)
  {
    throw PriorityQueueEmptyException ("EMPTY");
  }
  else if(Min_heap.size() == 1)
  {
    Min_heap.pop_back();
    word_num --;
  }
  else
  {
    std::swap(Min_heap.front(), Min_heap.back()); // swap with leaf
    Min_heap.pop_back(); //delete leaf
    word_num --;

    size_t Current_index = 0; // Min_heap[0] is not minimimun
    size_t Right_child_index = (2 * Current_index) + 2;
    size_t Left_child_index = (2 * Current_index) + 1;

    while(Current_index != Min_heap.size() - 1)
    {
      if(Left_child_index == Min_heap.size() - 1) // only left child
      {
        if(Min_heap[Left_child_index] < Min_heap[Current_index])
        {
          std::swap(Min_heap[Current_index], Min_heap[Left_child_index]);
          break;
        }
        else
        {
          break;
        }
      }
      else if((Min_heap.size() -1 < Left_child_index) && (Min_heap.size() - 1 < Right_child_index)) // no child // should be already in the correct position
      {
        break;
      }
      else // two child
      {
        if((Min_heap[Current_index] < Min_heap[Left_child_index] || isEqual(Min_heap[Current_index], Min_heap[Left_child_index])) && 
           (Min_heap[Current_index] < Min_heap[Right_child_index] || isEqual(Min_heap[Current_index], Min_heap[Right_child_index])) )
        {
          break;
        }
        else
        {
          if(Min_heap[Right_child_index] < Min_heap[Left_child_index]) //if Left is bigger
          {
            std::swap(Min_heap[Current_index], Min_heap[Right_child_index]);
            Current_index = Right_child_index;
            Left_child_index = (2 * Current_index) + 1;
            Right_child_index = (2 * Current_index) + 2;
          }
          else if(Min_heap[Left_child_index] < Min_heap[Right_child_index]) //if Right is bigger
          {
            std::swap(Min_heap[Current_index], Min_heap[Left_child_index]);
            Current_index = Left_child_index;
            Left_child_index = (2 * Current_index) + 1;
            Right_child_index = (2 * Current_index) + 2;
          }
          else //if they are same
          {
            std::swap(Min_heap[Current_index], Min_heap[Right_child_index]);
            Current_index = Right_child_index;
            Left_child_index = (2 * Current_index) + 1;
            Right_child_index = (2 * Current_index) + 2;
          }
        }
      }
    }
  }
  return;
}

#endif
