# Lewis Carroll Distance (Hash Map) - README

## Project Overview

This project implements the Lewis Carroll Distance problem using a hash map to solve the word ladder puzzle. In 1879, Lewis Carroll proposed the puzzle of transforming one English word into another by changing one letter at a time, with each intermediate step also being a valid English word. The solution involves determining the smallest number of substitutions needed to transform one word into another, known as the Lewis Carroll distance.

## Features

- **WordSet Implementation**: A custom hash map using cuckoo hashing to store and validate words.
- **Hash Function**: A polynomial hash function to map strings to integer indices.
- **Word Ladders**: Calculation of the shortest transformation sequence (word ladder) from one word to another.

## Project Structure

- **WordSet Class**: Implements the custom hash map with cuckoo hashing.
- **Polynomial Hash Function**: Maps strings to integers.
- **Word Ladder Conversion**: Uses breadth-first search to find the shortest transformation sequence.

## Files

- `WordSet.hpp`: Header file for the WordSet class.
- `WordSet.cpp`: Implementation of the WordSet class.
- `convert.hpp`: Header file for the word ladder conversion function.
- `convert.cpp`: Implementation of the word ladder conversion function.
- `main.cpp`: Entry point and test cases.

## Usage

### WordSet Class

The `WordSet` class is a custom hash map using cuckoo hashing to store strings. It includes the following methods:

- **Constructor**: Initializes the hash map with a specified capacity and eviction threshold.
  ```cpp
  WordSet::WordSet(unsigned initialCapacity, unsigned evictionThreshold);
