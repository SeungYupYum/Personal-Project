#ifndef __PROJ_FOUR_AVL_HPP
#define __PROJ_FOUR_AVL_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>

class ElementNotFoundException : public RuntimeException 
{
public:
	ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};


template<typename Key, typename Value>
class MyAVLTree
{
private:
		struct Node 
		{
			Key key;
			Value value;
			Node* left;
			Node* right;
			// Node* parent; // Not gonna use it if recursive approach work
			unsigned int height; //will be updated after one insertion
		};
		
		Node* root; // pointer that points root always.
		size_t key_num;

	// fill in private member data here
	// If you need to declare private functions, do so here too.

public:
	MyAVLTree();

	// The destructor is, however, required. 
	~MyAVLTree();

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const noexcept; 

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const MyAVLTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the AVL re-balance
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);

	// Returns the height of given key in the tree
	unsigned height(const Key& k) const;

	// in general, a "remove" function would be here
	// It's a little trickier with an AVL tree
	// and I am not requiring it for this quarter's ICS 46.
	// You should still read about the remove operation
	// in your textbook. 

	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;

	void Recursive_deletion(Node* n);

	void In(Node* n, std::vector<Key> & list) const; // for recursive call to put in - order
	void Post(Node* n, std::vector<Key> & list) const; // for recurisve call to put post - order
	void Pre(Node* n, std::vector<Key> & list) const; // for recursive call to put pre - order
		
	//for rotation
	Node* Case1(Node* n); // straight to the left
	Node* Case2(Node* n); // straight to the right
	Node* Case3(Node* n); // diamond left
	Node* Case4(Node* n); // diamond right

	int get_height(Node* n); // to get height of that node
	int get_height_max(int a, int b); // to get max of left child and right child
	Node* Recursive_insertion(Node* n, const Key & k, const Value & v); // to call recuresive insertion call
};

template<typename Key, typename Value>
MyAVLTree<Key,Value>::MyAVLTree()
{
	key_num = 0;
	root = nullptr;
}

template<typename Key, typename Value>
void MyAVLTree<Key,Value>::Recursive_deletion(Node* n)	//for destructor, it seems much easier to do it with recursive, 
{														//and I have no idea if it is possible to cll destructor recursively.
	/* if (n -> left != nullptr) 							//NOTE : CHECK 200,000 element
	{
		Rcuresive_deletion(n -> left);
	}
	if (n -> right != nullptr) 
	{
		Rcuresive_deletion(n -> right);
	}
	delete n; */
	if (n != nullptr)
	{
		Recursive_deletion(n -> left);
		Recursive_deletion(n-> right);
		delete n;
	}
}

template<typename Key, typename Value>
MyAVLTree<Key,Value>::~MyAVLTree()
{
	Recursive_deletion(root);
}

template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{
	return key_num;
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
	return key_num == 0;; // root = nullptr might be dangerous.
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key &k) const noexcept
{
	Node* temp = root; // starting from the root
	
	while (temp != nullptr) // until reaches to bottom (leaf)
	{
		if (temp -> key == k) // if key is same as target, then return true
		{
			return true;
		}
		else if (temp -> key < k) // if key is greater than current key, then move right
		{
			temp = temp -> right;
		}
		else if (temp -> key > k) // if key is smaller than current key, then move left
		{
			temp = temp -> left;
		}
	}
	return false; // if it does not found from the path, then it's guaranteed that key does not exist
	 // stub
}

template<typename Key, typename Value>
Value & MyAVLTree<Key, Value>::find(const Key & k)
{
	Node* temp = root; // starting from the root

	while (temp != nullptr) // until it reach bottom (leaf)
	{
		if (temp -> key == k) // if key is target, then return value
		{
			return temp -> value;
		}
		else if (temp -> key < k) // if key is greater than current key, then move right
		{
			temp = temp -> right;
		}
		else if (temp -> key > k) // if key is smaller than current key, then move left
		{
			temp = temp -> left;
		}
	}
	throw ElementNotFoundException("KEY NOT FOUND"); // after finish path, not found, throw exception
}

template<typename Key, typename Value>
const Value & MyAVLTree<Key, Value>::find(const Key & k) const
{
	Node* temp = root; // starting from the root

	while (temp != nullptr) // until it reach bottom (leaf)
	{
		if (temp -> key == k) // if key is target, then return value
		{
			return temp -> value;
		}
		else if (temp -> key < k) // if key is greater than current key, then move right
		{
			temp = temp -> right;
		}
		else if (temp -> key > k) // if key is smaller than current key, then move left
		{
			temp = temp -> left;
		}
	}
	throw ElementNotFoundException("KEY NOT FOUND"); // after finish path, not found, throw exception
}

template<typename Key, typename Value>
int MyAVLTree<Key,Value>::get_height(Node* n) // it is helper function for only to get balance factor
{
	if (n == nullptr)
	{
		return -1;	// if null pointer then return -1, but it seems weird since height is unsigned.
	} 				// However, hopefully if key doesn't exist, then we throw exception, so this case will cover
	else 
	{
		return n -> height; // otherwise, get n's height
	}
}

template<typename Key, typename Value>
int MyAVLTree<Key,Value>::get_height_max(int a, int b)
{
	if(a > b)
	{
		return a; // if a is bigger than b, then return a,
	}
	else
	{
		return b; // if it's same -> doesn't matter, if b is bigger than a, then return b, so cover all case
	}
}

template<typename Key, typename Value>
typename MyAVLTree<Key, Value>::Node* MyAVLTree<Key,Value>::Case1(Node* n)
{
	Node* Y = n -> left;
	Node* T3 = Y -> right;					///     Z(n)                        Y
											///    Y       ->         X                   Z
	Y -> right = n;							///   X           unchange unchange     Y-right unchange
	n -> left = T3;

	n -> height = 1 + get_height_max(get_height(n -> left), get_height(n -> right));
	Y -> height = 1 + get_height_max(get_height(Y -> left), get_height(Y -> right));

	return Y;
}


template<typename Key, typename Value>
typename MyAVLTree<Key, Value>::Node* MyAVLTree<Key,Value>::Case2(Node* n)
{
	Node* Y = n -> right;
	Node* T2 = Y -> left;					/// Z(n)                        Y
											///   Y    ->          Z              X
	n -> right = T2;						///     X      unchagne Y-left unchage unchange
	Y -> left = n;

	n -> height = 1 + get_height_max(get_height(n -> left), get_height(n -> right));
	Y -> height = 1 + get_height_max(get_height(Y -> left), get_height(Y -> right));

	return Y;
}

template<typename Key, typename Value>
typename MyAVLTree<Key, Value>::Node* MyAVLTree<Key,Value>::Case3(Node* n)
{
	Node* Y = n -> left;					///   Z(n)                      Y 
	Node* X = Y -> right;					///  Y       ->			Z            	Y
	Node* T2 = X -> left;					///    X		unchagne X-left  X-right unchgane
	Node* T3 = X -> right;

	X -> left = Y;
	X -> right = n;
	Y -> right = T2;
	n -> left = T3;

	n -> height = 1 + get_height_max(get_height(n -> left), get_height(n -> right));
	Y -> height = 1 + get_height_max(get_height(Y -> left), get_height(Y -> right));
	X -> height = 1 + get_height_max(get_height(X -> left), get_height(X -> right));

	return X;
}

template<typename Key, typename Value>
typename MyAVLTree<Key, Value>::Node* MyAVLTree<Key,Value>::Case4(Node* n)
{
	Node* Y = n -> right;					///   Z(n)                      Y 
	Node* X = Y -> left;					///       Y  ->			Z            	Y
	Node* T2 = X -> left;					///    X		unchagne X-left  X-right unchgane
	Node* T3 = X -> right;

	X -> left = n;
	X -> right = Y;
	Y -> left = T3;
	n -> right = T2;

	n -> height = 1 + get_height_max(get_height(n -> left), get_height(n -> right));
	Y -> height = 1 + get_height_max(get_height(Y -> left), get_height(Y -> right));
	X -> height = 1 + get_height_max(get_height(X -> left), get_height(X -> right));

	return X;
}

template<typename Key, typename Value>
typename MyAVLTree<Key, Value>::Node * MyAVLTree<Key,Value>::Recursive_insertion(Node* n, const Key & k, const Value & v) // must be recuresive like back tracking. 
{																														  // start root, reach bottom, go up until root																										
	if (n == nullptr) 
	{
		Node* Added_node = new Node;
		Added_node -> key = k;
		Added_node -> value = v;
		Added_node -> left = nullptr;
		Added_node -> right = nullptr;
		Added_node -> height = 0; // height is 0 since we always add node at leaf. Upper node's height will be updated thorugh recursive.
		return Added_node;
	}
	if (k < n -> key) 
	{
		n -> left = Recursive_insertion(n -> left, k, v); //move to left, function call again, making stack of the path
	}
	else if (k > n -> key) 
	{
		n -> right = Recursive_insertion(n -> right, k, v); //move to right, function call again, making stack of the path
	}
	else if(k == n -> key)
	{
		return n;
	} // reach bottom to insert node

	//check every node that is on the path to update height and to find rebalance point
	n -> height = 1 + get_height_max(get_height(n -> left), get_height(n -> right)); //updating height. Formula is same for all node including leaf node.
	int balance_factor = get_height(n -> right) - get_height(n -> left);	// balance factor for right - left
																			// B.F > 1 = right is taller, B.F< -1 = left is taller, else = balanced already.
	//right subtree is taller than left -> case 2 (right staright) or 4 (right diamond), 
	// *** n is Z  ***
	if (balance_factor > 1 && k < (n -> right -> key)) // if inserted key is smaller than Z's right, then it is right diamond (guranteed even if it's subtree)
	{
		return Case4(n);
	}
	else if (balance_factor > 1 && k > (n -> right -> key)) // if inserted key is greater than Z's right, then it is right straight (guranteed even if it's subtree)
	{
		return Case2(n);
	}
	//left subtee is taller than right -> case 1 or 3
	else if (balance_factor < -1 && k > (n -> left -> key)) //if inserted key is greater than Z's left, then it is left diamond (guranteed even if it's subtree)
	{
		return Case3(n);
	}
	else if (balance_factor < -1 && k < (n -> left -> key)) // if inseted key is smaller than Z's left, then it is left straight (guranteed even if it's subtree)
	{
		return Case1(n);
	}
	return n; // it looks like return node that is inserted, but it has to return all node that is in the stack (path from root to insert node)
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(const Key & k, const Value & v)
{
	root = Recursive_insertion(root, k, v); // since recursive call always take root node, root will be update accordingly
	key_num ++;
}

template<typename Key, typename Value>
unsigned MyAVLTree<Key, Value>::height(const Key & k) const
{
	Node* temp = root; // starting from root

	while (temp != nullptr) // until reach bottom (leaf)
	{
		if (temp -> key == k) // if current key is target, then return that node's height
		{
			return temp -> height;
		}
		else if (temp -> key < k)  // if currnet key is smaller than k, then move right
		{
			temp = temp -> right;
		}
		else 
		{
			temp = temp -> left; // if current key is greater than k, then move left
		}
	}
	throw ElementNotFoundException("KEY NOT FOUND");	
}

//helper function for In-order, Pre-order, Post-order // left is alwasy first, in(between), post(after), pre(before)
template<typename Key, typename Value>
void MyAVLTree<Key,Value>::In(Node* n, std::vector<Key> & vector) const
{
	if (n == nullptr) // since nothing return. might throw exception in inOrder function to fully cover error
	{	
		return;
	}
	else 
	{
		In(n -> left, vector); // always left first
		vector.push_back(n -> key); // between since in - order
		In (n -> right, vector); // always right second
	}
}

template<typename Key, typename Value>
void MyAVLTree<Key,Value>::Post(Node* n, std::vector<Key> & vector) const
{
	if (n == nullptr) 
	{
		return;
	}
	else 
	{
		Post(n -> left, vector); // always left first
		Post (n -> right, vector); // always right second
		vector.push_back(n -> key); // after since post- order
	}
}
	

template<typename Key, typename Value>
void MyAVLTree<Key,Value>::Pre(Node* n, std::vector<Key> & vector) const
{
	if (n == nullptr) 
	{
		return;
	}
	else 
	{
		vector.push_back(n -> key); // before since pre - order
		Pre(n -> left, vector); // always left first
		Pre(n -> right, vector); // always right first
	}
}
template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder() const
{
	/* if(isEmpty() == true)
	{
		throw ElementNotFoundException ("TREE IS EMPTY"); // to fully covoer, if it is empty, then just throw exception, might not tested this case
	}
	else
	{ */
	std::vector<Key> In_Order; // create vector for in - order
	In(root, In_Order); // call recursive call to get vector that is storing in - order
	return In_Order;  // return vector
	/* } */
}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder() const
{
	/* if(isEmpty() == true)
	{
		throw ElementNotFoundException ("TREE IS EMPTY"); // to fully covoer, if it is empty, then just throw exception, might not tested this case
	}
	else
	{ */
	std::vector<Key> Pre_Order; // create vector for pre - order
	Pre(root, Pre_Order); // call recursive call to get vector that is storing pre - order
	return Pre_Order;  // return vector
	/* } */
}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder() const
{
	/* if(isEmpty() == true)
	{
		throw ElementNotFoundException ("TREE IS EMPTY"); // to fully covoer, if it is empty, then just throw exception, might not tested this case
	}
	else
	{ */
	std::vector<Key> Post_Order; // create vector for post - order
	Post(root, Post_Order); // call recursive call to get vector that is storing post - order
	return Post_Order;  // return vector
	/* } */
}

#endif