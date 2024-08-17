# Word Ladder (Prioirty Queue)

## Description

It consists with two combined parts; Implementation of Priority Queue and Solving Word Ladder Problem Using Priority Queue. The word ladder problem is simply calcaulating lowest Lewis Carroll distance. With the given dictionary data set, it should caclulate the lowest number of steps te reach from **WORD A** to **WORD B**. Each step is only one letter apart, for example, **CAT - BAT - BAD - DAD**. It requires both two words should be in the given dictionary data set, and if there is no path/solution, then it returns empty vector. To solve this problem effectively, it uses min priority queue.

## Features

### Implementation of Priority Queue

- **size**: Simply return the size of priority queue.
- **isEmpty**: Simply return boolean value. Return true if priority queue is empty, otherwise return false.
- **isEqual**: Simply return boolean value. Return treu if two objects are equal, otherwise return false.
- **insert**: Insert object into priority queue.
- **min**: Simply return the current minimum object in the priority queue. If priority queue is currently empty, then throw exeption.
- **extractMin**: It extacts the current minimum object in the priority queue and realign the priority queue after.

### Word Ladder with using Prioirity Queue

- **loadWordsIntoTable**: Load word dictionary file into unordered_set.
- **LetterDelta**: Given two words, calculating how many letters are different. For exmaple, **LetterDelta("CAT", "BAD")** returns **2**.
- **convert**: Two words and unordered_set are given. If two words are already identical or their length is not identical, then return empty vector. The node is made at the top of convert.cpp, and put the first word into node. Calculate LCD, letterDelta, and H between the first word and the second word, and put all of them into the node. Put this node into the priority queue, and through the while loop, it caluclates all the words that are one letter apart from the unordered_set that it just loaded before. Calucalte same process that it did for the first word, and put them into the priority queue. Since the goal of this problem is get the lowest nubmer of steps between the two words, the standard that it will compare within the pirority queue is letterDelta. After fine the second word, it return the reversed stack.
