# Skip List

## Description

It is just simple implementation of Skip List. Since inserting, searching, removing process in skip list guarantees O(log n), the primary goal is inserting 200,000 integer keys in 6 seconds.

## Features

- **find(), height(), nextKey(), previousKey()** with 200,000 element take less than 1 second.
- **isLargestKey(), isSmallestKey(), size(), isEmpty(), numLayers()** with 200,000 element take 100 milliseconds.
  
- **flip coin**: This function looks at the bitwise representation to determine how many layers it occupies in the skip list. It takes the bitwise XOR of each byte in a 32-bit unsigned number and uses the index `previousFlips` to determine the truth value. If the function returns true, then newly instered element is propagated up, and if the function returns false, then it stops.
  ```cpp
  inline bool flipCoin(unsigned key, unsigned previousFlips), inline bool flipCoin(std::string key, unsigned previousFlips)

- **Constructor**: General constructor. It creates 2 empty layer, the bottom most layer that will contain every elemtn and the top most layer that will contain no element at all.
  ```cpp
  SkipList<Key, Value>::SkipList()

- **Destructor**: General destructor.
  ```cpp
  SkipList<Key, Value>::~SkipList()

- **Size**: Return the number of element that the skip list currently has.
  ```cpp
  size_t SkipList<Key, Value>::size() const noexcept

- **isEmpty**: Return true if the skip list has no elemnt, otherwise, return false.
  ```cpp
  bool SkipList<Key, Value>::isEmpty() const noexcept

- **Number of Layer**: Return the number of current layer including the top most laeyr (no element), and bottom most layer (every element).
  ```cpp
  unsigned SkipList<Key, Value>::numLayers() const noexcept

- **Height**: It returns the height of the key in the skip list. In other word, it returns the occupied max layer of the key.
  ```cpp
  unsigned SkipList<Key, Value>::height(const Key & k) const 

- **Next Key**: It returns the next largest key in the skip list. It gurantees O(log n).
  ```cpp
  Key SkipList<Key, Value>::nextKey(const Key & k) const 

- **Previous Key**: It returns the next smallest key in the skip list. It guarantees O(log n).
  ```cpp
  Key SkipList<Key, Value>::previousKey(const Key & k) const

- **Find**: It returns the value of element with key. There is two version of function, one is for modifiable, and the other one is for non-modifiable. Both guarantees O(log n).
  ```cpp
  const Value & SkipList<Key, Value>::find(Key k) const, Value & SkipList<Key, Value>::find(const Key & k) 

- **Finding**: It returns true if the element is already in the skip list, otherwise, return false.
  ```cpp
  bool SkipList<Key, Value>::finding(const Key & k) const

- **Insert**: If desired element is successfully inserted, return true. If the element or key is already in the skip list, then return false. First, it find the correct position at the bottom layer first, and then it flips the coin until it fails. As many times as successful, the new element moves up the layer. Whenever it goes up, it connects with the previous, next, and below element. The maximum number of layers in this is 16. Gurantees O(log n).
  ```cpp
  bool SkipList<Key, Value>::insert(const Key & k, const Value & v) 

- **All Keys in Order**: Return vector that contains ascending order of unique key in skip list. It just traverse the bottom layer to reach O(n).
  ```cpp
  std::vector<Key> SkipList<Key, Value>::allKeysInOrder() const 

- **Is Smallest Key**: Return true if the key is curretnly the smallest key in the skip list, otherwise, return false.
  ```cpp
  bool SkipList<Key, Value>::isSmallestKey(const Key & k) const 

- **Is Largest Key**: Return true if the key is currently the largest key in the skip list, otherwise, return false.
  ```cpp
  bool SkipList<Key, Value>::isLargestKey(const Key & k) const 
