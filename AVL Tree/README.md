# AVL Tree

## Description

This project implements an AVL Tree, a type of self-balancing binary search tree. The AVL Tree ensures that the heights of the two child subtrees of any node differ by no more than one, which guarantees O(log n) time complexity for search, insertion, and deletion operations.

## Features

- **Insertion**: Adds a new node to the AVL tree while maintaining its balanced property.
- **Deletion**: Removes a node from the AVL tree and rebalances it if necessary.
- **Search**: Finds and retrieves a node from the AVL tree.
- **Size**: Return the number of nodes (key).
- **Contains**: Check if the AVL Tree contains corresponding key.
- **Height**: Return the height of the tree.
- **Traversal**: Return in vector form.
  - **Pre-order Traversal**: Visits nodes in the order: root, left subtree, right subtree.
  - **In-order Traversal**: Visits nodes in the order: left subtree, root, right subtree.
  - **Post-order Traversal**: Visits nodes in the order: left subtree, right subtree, root.
