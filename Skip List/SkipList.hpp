
#ifndef ___SKIP_LIST_HPP
#define ___SKIP_LIST_HPP

#include <cmath> // for log2
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include "runtimeexcept.hpp"

/**
 * flipCoin -- NOTE: Only read if you are interested in how the
 * coin flipping works.
 * 
 * @brief Uses the bitwise representation of the key to simulate
 * the flipping of a deterministic coin.
 * 
 * This function looks at the bitwise representation to determine
 * how many layers it occupies in the skip list. It takes the bitwise
 * XOR of each byte in a 32-bit unsigned number and uses the index `previousFlips`
 * to determine the truth value. It's best to look at an example and
 * to start with values that fit into one byte.
 * 
 * Let's start with the function call `flipCoin(0, 0)`. This call is
 * asking whether or not we should insert the key `0` into layer `1`
 * (because `previousFlips` represents the number of previous flips).
 * 
 * This function will get the bitwise representation of 0: 
 * 
 *        00000000 00000000 00000000 00000000
 * 
 * All bytes are XOR'd together: 
 * 
 * 
 *  c = 0 ^ 0 ^ 0 ^ 0
 * 
 * Then the index `previousFlips` is used to obtain the bit in the `previousFlips % 8` position.
 * 
 * So the return value is `0 & 1 = 0`, since the value in the zeroth position 
 * (obtained by bitmasking the value (1 << 0) at the bottom of the function
 * is 0.
 * Thus, this value `0` should never get added beyond the bottom-most layer.
 * 
 * Before:
 * 
 * S_1: -inf ----> inf
 * S_0: -inf ----> inf
 * 
 * And after 0 is inserted
 * 
 * S_1: -inf --------> inf
 * S_0: -inf --> 0 --> inf
 * 
 * Let's look at something more interesting, like the call `flipCoin(5, 0)`.
 * Remember the binary representation for 5 is 00000101.
 * 
 * c = 0 ^ 0 ^ 0 ^ 00000101 = 00000101
 * 
 * Now we get the bit at 0th position (from `previousFlips`).
 * 
 * 00000101 & 1 = 1. Thus, `5` DOES get inserted into the next layer,
 * layer 1.
 * 
 * So the skip list before this insertion might look like:
 * 
 * S_1: -inf ----> inf
 * S_0: -inf ----> inf
 * 
 * And after it would look like:
 * 
 * S_2: -inf --------> inf
 * S_1: -inf --> 5 --> inf
 * S_0: -inf --> 5 --> inf
 * 
 * Observe that a new layer had to get created, because there should always
 * be an empty layer at the top.
 * 
 * Since 5 got inserted into the next layer, we need to flip again to see if
 * it should get propagated once more.
 * 
 * `flipCoin(5, 1)` this will produce a result of `0`, since 00000101 & (1 << 1) = 0.
 * 
 * Thus, `5` will not be pushed up to the next layer.
 * 
 * @param key The integer key which will be added to the skip list
 * @param previousFlips The number of previous flips for this key
 * @return true simulates a "heads" from a coin flip
 * @return false simulates a "tails" from a coin flip
 */
inline bool flipCoin(unsigned key, unsigned previousFlips)
{
    char c;
    unsigned first8Bits = (key & 0xFF000000) / 0x01000000 ; 
    unsigned next8Bits =  (key & 0x00FF0000) / 0x00010000;
    unsigned andThen =   (key & 0x0000FF00) / 0x00000100;
    unsigned lastBits =   (key & 0x000000FF);
    c = first8Bits ^ next8Bits ^ andThen ^ lastBits;
    previousFlips = previousFlips % 8;
    return ( c & (1 << previousFlips) ) != 0;
}

/**
 * @brief Works the same as the integer version above, except
 * it XORs chars in a string instead of the first four
 * bytes of an integer.
 * 
 * @param key key that will be inserted into the skip list
 * @param previousFlips number of previous flips for this key 
 * @return true simulates a "heads" from a coin flip
 * @return false simulates a "tails" from a coin flip
 */
inline bool flipCoin(std::string key, unsigned previousFlips)
{
    char c = key[0];
    for(unsigned j = 1; j < key.length(); j++)
    {
        c = c ^ key[j];
    }
    previousFlips = previousFlips % 8;
    return ( c & (1 << previousFlips) ) != 0;   
}

template<typename Key, typename Value>
class SkipList
{

private:
    struct Node     // Eventually it is 2D doubly linked list.
    {
        Node* next;     // It seems that making node that contain 4 ponters is easier.
        Node* prev;
        Node* up;
        Node* down;
        Key key;        // key
        Value value;    // value
        unsigned int node_level; // curent node's level
    };

    size_t key_num;     // the total number of key in the list, 0 when created, so should be included in constructor
    unsigned int Max_layer;  // possible max level of the list. This variable is for insertion function to make limit of flip coin
    Node* head;         // Points base layer +inf = first vertical layer's head
    Node* tail;         // Points base layer -inf = last vertical layer's head
    Node* topright;     // Points top layer +inf = last vertical layer's tail
    Node* topleft;      // Points top layer -inf = last vertical layer's tail

    unsigned int layer_level; // Current skip list's level, number of total layer including base and top, base case = 2 (should be included in constructor) = largest current list's node_level + 1
public:

    SkipList();

    // You DO NOT need to implement a copy constructor or an assignment operator.

    ~SkipList();

    // How many distinct keys are in the skip list?
    size_t size() const noexcept;

    // Does the Skip List contain zero keys?
    bool isEmpty() const noexcept;

    // How many layers are in the skip list?
    // Note that an empty Skip List has two layers by default,
    // the "base" layer S_0 and the top layer S_1.
    //
    // [S_1: Top layer]    -inf ------> inf
    // [S_0: Bottom layer] -inf ------> inf
    //
    // This "empty" Skip List has two layers and a height of one.
    unsigned numLayers() const noexcept;

    // What is the height of this key, assuming the "base" layer S_0
    // contains keys with a height of 1?
    // For example, "0" has a height of 1 in the following skip list.
    //
    // [S_1]  -inf --------> inf
    // [S_0]  -inf --> 0 --> inf
    //
    // Throw an exception if this key is not in the Skip List.
    unsigned height(const Key & k) const;

    // If this key is in the SkipList and there is a next largest key
    // return the next largest key.
    // This function should throw a RuntimeException if either the key doesn't exist
    // or there is no subsequent key. 
    // A consequence of this is that this function will
    // throw a RuntimeException if *k* is the *largest* key in the Skip List.
    Key nextKey(const Key & k) const;

    // If this key is in the SkipList and a next smallest key exists,
    // return the next smallest key.
    // This function should throw a RuntimeException if either the key doesn't exist
    // or there is no previous key. 
    // A consequence of this is that this function will
    // throw a RuntimeException if *k* is the *smallest* key in the Skip List.
    Key previousKey(const Key & k) const;

    // These return the value associated with the given key.
    // Throw a RuntimeException if the key does not exist.
    Value & find(const Key & k);
    const Value & find(Key k) const;
	bool finding(const Key & k) const;
    // Return true if this key/value pair is successfully inserted, false otherwise.
    // See the project write-up for conditions under which the key should be "bubbled up"
    // to the next layer.
    // If the key already exists, do not insert one -- return false.
    bool insert(const Key & k, const Value & v);

    // Return a vector containing all inserted keys in increasing order.
    std::vector<Key> allKeysInOrder() const;

    // Is this the smallest key in the SkipList? Throw a RuntimeException
    // if the key *k* does not exist in the Skip List. 
    bool isSmallestKey(const Key & k) const;

    // Is this the largest key in the SkipList? Throw a RuntimeException
    // if the key *k* does not exist in the Skip List. 
    bool isLargestKey(const Key & k) const;

    // I am not requiring you to implement remove.

    
};

template<typename Key, typename Value>
SkipList<Key, Value>::SkipList() 
{
	
    Node* Bottom_positive_inf = new Node; // INT_MIN
		Bottom_positive_inf -> key = Key();
    Node* Bottom_negatvie_inf = new Node;
       Bottom_negatvie_inf -> key = Key();
    Node* Top_positive_inf = new Node;
        Top_positive_inf -> key = Key();
    Node* Top_negative_inf = new Node;
        Top_negative_inf -> key = Key();

    head = Bottom_negatvie_inf;
    tail = Bottom_positive_inf;
    topleft = Top_negative_inf;
    topright = Top_positive_inf;

    Bottom_negatvie_inf -> next = Bottom_positive_inf;          
    Bottom_negatvie_inf -> prev = nullptr;         
    Bottom_negatvie_inf -> down = nullptr;         
    Bottom_negatvie_inf -> up = Top_negative_inf;           

    Bottom_positive_inf -> next = nullptr;
    Bottom_positive_inf -> prev = Bottom_negatvie_inf;
    Bottom_positive_inf -> down = nullptr;
    Bottom_positive_inf -> up = Top_positive_inf;

    Top_negative_inf -> next = Top_positive_inf;
    Top_negative_inf -> prev = nullptr;
    Top_negative_inf -> up = nullptr;
    Top_negative_inf -> down = Bottom_negatvie_inf;
                                    
    Top_positive_inf -> next = nullptr;
    Top_positive_inf -> prev = Top_negative_inf;
    Top_positive_inf -> up = nullptr;       
    Top_positive_inf -> down = Bottom_positive_inf;
    
    layer_level = 2;
	key_num = 0;
}

template<typename Key, typename Value>
SkipList<Key, Value>::~SkipList() 
{   
    Node * temp_down = topleft;
    Node * temp_next = topleft;
	Node * temp_temp;
	
    while (temp_down != nullptr) 
    {
		temp_down = temp_down -> down;

        while (temp_next != nullptr)     //Delete top latyer first, move to next layer, until base layer
        {
			temp_temp = temp_next;
			temp_next = temp_next -> next;
			delete temp_temp;
        }
		temp_next = temp_down;
    }

	head = nullptr;
	tail = nullptr;
	topright = nullptr;
	topleft = nullptr;
    key_num = 0;
    layer_level = 0; // maybe 2?
}

template<typename Key, typename Value>
size_t SkipList<Key, Value>::size() const noexcept 
{
    return key_num;
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::isEmpty() const noexcept 
{
    return (key_num == 0);
}

template<typename Key, typename Value>
unsigned SkipList<Key, Value>::numLayers() const noexcept 
{
    return layer_level;
}

template<typename Key, typename Value>
unsigned SkipList<Key, Value>::height(const Key & k) const 
{
    Node* current = topleft;        // Tracker for start
    Node* temp_right = topright;
    Node* temp_left = topleft;
    if(isEmpty() == true)
    {
        throw RuntimeException ("List Empty");
    }
    while (current != tail)         // until tracker points tail
    {
        if (current != temp_left && current != temp_right && current-> key == k)         // if tracker's key = k
        {
            return current -> node_level;
        }
        if (current -> next -> key > k && current -> down != nullptr) // if next node's key of tracker is greater than k
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down;
        }
        if (current -> next == temp_right && current -> down != nullptr)
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down; 
        }
        else
        {
            current = current -> next; // otherwise, move right
        }
    }
    throw RuntimeException ("Not found");
}

template<typename Key, typename Value>
Key SkipList<Key, Value>::nextKey(const Key & k) const 
{
    Node* current = topleft;        // Tracker for start
    Node* temp_right = topright;
    Node* temp_left = topleft;
    if(isEmpty() == true)
    {
        throw RuntimeException ("List Empty");
    }
    while (current != tail)         // until tracker points tail
    {
        if (current != temp_left && current != temp_right && current-> key == k && current -> down == nullptr)         // if tracker's key = k
        {
            if(current -> next == tail)
            {
                throw RuntimeException ("This is the largest");
            }
            else if(current -> next != tail)
            {
                return current -> next -> key;
            }
        }
        if (current -> key == k && current != temp_left && current != temp_right && current -> down != nullptr)
        {
            current = current -> down;
            temp_right = temp_right -> down;
            temp_left = temp_left -> down;
        }
        if (current -> key != k &&current -> next -> key > k && current -> next != temp_right && current -> down != nullptr) // if next node's key of tracker is greater than k
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down;
        }
        if (current -> next == temp_right && current != temp_left && current -> down != nullptr && current -> key < k)
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down; 
        }
        if (current -> next == temp_right && current == temp_left && current -> down != nullptr)
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down;             
        }
        else
        {
            current = current -> next; // otherwise, move right
        }
    }
    throw RuntimeException ("Not found");
}

template<typename Key, typename Value>
Key SkipList<Key, Value>::previousKey(const Key & k) const // cannot do find(k) since there is a case where k does not exist in list
{                                                          
    Node* current = topleft;        // Tracker for start
    Node* temp_right = topright;
    Node* temp_left = topleft;
    if(isEmpty() == true)
    {
        throw RuntimeException ("List Empty");
    }
    while (current != tail)         // until tracker points tail
    {
        if (current != temp_left && current != temp_right && current-> key == k && current -> down == nullptr)         // if tracker's key = k
        {
            if(current -> prev == head)
            {
                throw RuntimeException ("This is the largest");
            }
            else if(current -> prev != head)
            {
                return current -> prev -> key;
            }
        }
        if (current -> key == k && current != temp_left && current != temp_right)
        {
            current = current -> down;
            temp_right = temp_right -> down;
            temp_left = temp_left -> down;
        }
        if (current -> next -> key == k && current -> next != temp_right && current -> down != nullptr)
        {
            current = current -> next;
        }
        if (current -> next -> key > k && current -> next != temp_right && current -> down != nullptr) // if next node's key of tracker is greater than k
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down;
        }
        if (current -> next == temp_right && current -> down != nullptr)
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down; 
        }
        else
        {
            current = current -> next; // otherwise, move right
        }
    }
    throw RuntimeException ("Not found");
}

template<typename Key, typename Value>
const Value & SkipList<Key, Value>::find(Key k) const 
{
    Node* current = topleft;        // Tracker for start
    Node* temp_right = topright;
    Node* temp_left = topleft;
    if(isEmpty() == true)
    {
        throw RuntimeException ("List Empty");
    }
    while (current != tail)         // until tracker points tail
    {
        if (current != temp_left && current != temp_right && current-> key == k)         // if tracker's key = k
        {
            return current -> value;               // then return tracker's key
        }
        if (current -> next -> key > k && current -> down != nullptr) // if next node's key of tracker is greater than k
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down;
        }
        if (current -> next == temp_right && current -> down != nullptr)
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down; 
        }
        else
        {
            current = current -> next; // otherwise, move right
        }
    }
    throw RuntimeException ("Not found");
}

template<typename Key, typename Value>
Value & SkipList<Key, Value>::find(const Key & k) 
{

    Node* current = topleft;        // Tracker for start
    Node* temp_right = topright;
    Node* temp_left = topleft;
    if(isEmpty() == true)
    {
        throw RuntimeException ("List Empty");
    }
    while (current != tail)         // until tracker points tail
    {
        if (current != temp_left && current != temp_right && current-> key == k)         // if tracker's key = k
        {
            return current -> value;               // then return tracker's key
        }
        if (current -> next -> key > k && current -> down != nullptr) // if next node's key of tracker is greater than k
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down;
        }
        if (current -> next == temp_right && current -> down != nullptr)
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down; 
        }
        else
        {
            current = current -> next; // otherwise, move right
        }
    }
    throw RuntimeException ("Not found");
}


template<typename Key, typename Value>
bool SkipList<Key, Value>::finding(const Key & k) const
{
    Node* current = topleft;        // Tracker for start
    Node* temp_right = topright;
    Node* temp_left = topleft;
    while (current != tail)         // until tracker points tail
    {
        if (current != temp_left && current != temp_right && current-> key == k)         // if tracker's key = k
        {
            return true;               // then return tracker's key
        }
        if (current -> next == tail)
        {
            return false;
        }
        if (current -> next -> key > k && current -> down != nullptr && current -> next != temp_right) // if next node's key of tracker is greater than k
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down;
        }
        if (current -> next == temp_right && current -> down != nullptr)
        {
            current = current -> down;  // then move down
            temp_right = temp_right -> down;
            temp_left = temp_left -> down; 
        }
        else
        {
            current = current -> next; // otherwise, move right
        }
    }
    return false;
}



template<typename Key, typename Value>
bool SkipList<Key, Value>::insert(const Key & k, const Value & v) 
{
    int counter;

    if (finding(k) == true) // if it is already there, return false
    {
        return false;
    }
    else // not exist
    {
		if(size() == 0)
		{
            Max_layer = 13;

            Node* Base_node = new Node; // create node that contains k and v
            Base_node -> key = k;
            Base_node -> value = v;
            Base_node -> node_level = 1;
            Base_node -> down = nullptr;
            Base_node -> up = nullptr;
            // find position -> must be next to head
			Base_node -> next = head -> next;
            head -> next = Base_node;
            Base_node -> prev = Base_node -> next -> prev;
            Base_node -> next -> prev = Base_node;
            //connect with head and tail, prove done
			Node* temp = Base_node;
            Node* temp_to_head;
            Node* temp_to_tail;

            counter = 0;
            for(unsigned int j = 0; j < Max_layer - 2; j++) // True when j = 0 -> layer 1, True when j = MAX_layer -2 -> MAX_layer -1 (since not include top layer)
            {   
                if(flipCoin(k, j) == false)
                {
                    break;
                }
                else
                {
                    counter ++;
                }
            }
            
            for(int i = 0; i < counter; i++) // iterate head up times
            {
                	Node* Added_node = new Node;
					Added_node -> key = k;                              //   X     - Added node - y 
					Added_node -> value = v;                            //   |          |
					Added_node -> node_level = 2 + i;                   //  prev   - Based node (temp)
					Added_node -> down = temp;
                    Added_node -> up = nullptr;
                    temp -> up = Added_node;
                    temp_to_head = topleft;
                    temp_to_tail = topright;
                    
                    Added_node -> next = temp_to_tail;
                    temp_to_head -> next = Added_node;
                    Added_node -> prev = temp_to_head;
                    temp_to_tail -> prev = Added_node;

                    if (Added_node -> prev == topleft) // if x == topleft (vertical tail), then add new layer // x = topleft, add new layer (only +inf, -inf, and update topleft and right)
			        {
				        Node* Added_negative_inf = new Node;
				        Node* Added_positive_inf = new Node;
				
                        Added_negative_inf -> key = Key();
				        Added_negative_inf -> down = topleft;
				        Added_negative_inf -> up = nullptr;
				        Added_negative_inf -> prev = nullptr;
				        Added_negative_inf -> next = Added_positive_inf;

				        Added_positive_inf -> key = Key();
				        Added_positive_inf -> down = topright;
				        Added_positive_inf -> up = nullptr;
				        Added_positive_inf -> prev = Added_negative_inf;
				        Added_positive_inf -> next = nullptr;
						
				        topleft -> up = Added_negative_inf;
				        topleft = Added_negative_inf;
				        topright -> up = Added_positive_inf;
				        topright = Added_positive_inf; // create new layer

			            layer_level ++;
			        }
                    
                    temp = Added_node;
            }
            key_num ++;
		}
        else if(size() > 0 && size() < 16)
        {
            Max_layer = 13;

            Node* Base_node = new Node; // create node that contains k and v
            Base_node -> key = k;
            Base_node -> value = v;
            Base_node -> node_level = 1;
            Base_node -> down = nullptr;
            Base_node -> up = nullptr;
            // find position
            Node* current = topleft; // Copy from prev key function, but it returns key, so cannot use function itself.
			Node* Right_tracker = topright;
            Node* temp;
            while (current != tail) // until reach bottom layer right -most sentinel node, go down 1. next node key is greater, 2. next node is sentinel
            {
                if(current -> next -> key > k && current -> next != Right_tracker && current -> down != nullptr)
                {
                    current = current -> down;
                    Right_tracker = Right_tracker -> down;
                }
                else if(current -> next == Right_tracker && Right_tracker != tail && current -> down != nullptr)
                {
                    current = current -> down;
                    Right_tracker = Right_tracker -> down;
                }
                else if(current -> next -> key < k && current -> next != Right_tracker)
                {
                    current = current -> next;
                }
                else if(current == head && current -> next -> key > k && current -> next != tail)
                {
                    break;
                }
                else if(current != head && current -> next != tail && current -> key < k && current -> next -> key > k)
                {
                    break;
                }
                else if(current != head && current -> next == tail && current -> key < k)
                {
                    break;
                }
            }
            temp = current;
            // temp points previous node of Base_node
            Base_node -> prev = temp;
            if(temp -> next == tail)
            {
                Base_node -> next = tail;
                tail -> prev = Base_node;
                temp -> next = Base_node;
            }
            else
            {
                Base_node -> next = temp -> next;
                temp -> next -> prev = Base_node;
                temp -> next = Base_node;
            }

            counter = 0;
            for(unsigned int j = 0; j < Max_layer - 2; j++) // True when j = 0 -> layer 1, True when j = MAX_layer -2 -> MAX_layer -1 (since not include top layer)
            {   
                if(flipCoin(k, j) == false)
                {
                    break;
                }
                else
                {
                    counter ++;
                }
            }
            Node* temp_base = Base_node;
            
            for(int i = 0; i < counter; i++) // iterate head up times
            {
                //creat above, temp points based node, temp travers previous node that has above node, if there is nothing it is top layer now, create top layer.
                 //create temporary pointer to point base node. It will be go up through looping
                Node* Added_node = new Node;
                Added_node -> key = k;                              //   X     - Added node - y 
                Added_node -> value = v;                            //   |          |
                Added_node -> node_level = 2 + i;                   //  prev   - Based node (temp)
                Added_node -> down = temp_base;
                Added_node -> up = nullptr;
                Added_node -> next = nullptr;
                Added_node -> prev = nullptr;
                Node* temp_add = Added_node;
                 // create new node, contains k and v, assign node level
                
                while(temp_base -> up == nullptr)
                {
                    temp_base = temp_base -> prev;
                }

                temp_base = temp_base -> up;
                Added_node -> next = temp_base -> next;        // Added node's next = current's up's next
                Added_node -> prev = temp_base;               // Added node's prev = current's up                               // Added node's up = NULL for now
                temp_base -> next -> prev = Added_node;        // y's prev = Added node
                temp_base -> next = Added_node;                // x's next = Added node
                temp_add -> down -> up = Added_node;

                if (temp_base == topleft) // if x == topleft (vertical tail), then add new layer // x = topleft, add new layer (only +inf, -inf, and update topleft and right)
			    {
				    Node* Added_negative_inf = new Node;
				    Node* Added_positive_inf = new Node;
				
                    Added_negative_inf -> key = Key();
				    Added_negative_inf -> down = topleft;
	    		    Added_negative_inf -> up = nullptr;
			        Added_negative_inf -> prev = nullptr;
			        Added_negative_inf -> next = Added_positive_inf;

				    Added_positive_inf -> key = Key();
				    Added_positive_inf -> down = topright;
				    Added_positive_inf -> up = nullptr;
				    Added_positive_inf -> prev = Added_negative_inf;
				    Added_positive_inf -> next = nullptr;
						
				    topleft -> up = Added_negative_inf;
				    topleft = Added_negative_inf;
				    topright -> up = Added_positive_inf;
				    topright = Added_positive_inf; // create new layer

			        layer_level ++;
			    }
                temp_base = Added_node;                      // update current pointer to added node, Added_node becomes based_node
            }
            key_num ++;
        }
        else if(size() >= 16)// size is more than 16
        {
            size_t n = size() + 1;
            Max_layer = 3 * ceil(log2(n)) + 1; // adding base take 1, top layer doesn't count, so possible max flip coin succeed is max_level -2

            Node* Base_node = new Node; // create node that contains k and v
            Base_node -> key = k;
            Base_node -> value = v;
            Base_node -> node_level = 1;
            Base_node -> down = nullptr;
            Base_node -> up = nullptr;
            // find position
            Node* current = topleft; // Copy from prev key function, but it returns key, so cannot use function itself.
			Node* Right_tracker = topright;
            Node* temp;
            while (current != tail) // until reach bottom layer right -most sentinel node, go down 1. next node key is greater, 2. next node is sentinel
            {
                if(current -> next -> key > k && current -> next != Right_tracker && current -> down != nullptr)
                {
                    current = current -> down;
                    Right_tracker = Right_tracker -> down;
                }
                else if(current -> next == Right_tracker && Right_tracker != tail && current -> down != nullptr)
                {
                    current = current -> down;
                    Right_tracker = Right_tracker -> down;
                }
                else if(current -> next -> key < k && current -> next != Right_tracker)
                {
                    current = current -> next;
                }
                else if(current == head && current -> next -> key > k && current -> next != tail)
                {
                    break;
                }
                else if(current != head && current -> next != tail && current -> key < k && current -> next -> key > k)
                {
                    break;
                }
                else if(current != head && current -> next == tail && current -> key < k)
                {
                    break;
                }
            }
            temp = current;
            // temp points previous node of Base_node
            Base_node -> prev = temp;
            if(temp -> next == tail)
            {
                Base_node -> next = tail;
                tail -> prev = Base_node;
                temp -> next = Base_node;
            }
            else
            {
                Base_node -> next = temp -> next;
                temp -> next -> prev = Base_node;
                temp -> next = Base_node;
            }

            counter = 0;
            for(unsigned int j = 0; j < Max_layer - 2; j++) // True when j = 0 -> layer 1, True when j = MAX_layer -2 -> MAX_layer -1 (since not include top layer)
            {   
                if(flipCoin(k, j) == false)
                {
                    break;
                }
                else
                {
                    counter ++;
                }
            }
            std::cout << counter;
            Node* temp_base = Base_node;
            
            for(int i = 0; i < counter; i++) // iterate head up times
            {
                //creat above, temp points based node, temp travers previous node that has above node, if there is nothing it is top layer now, create top layer.
                 //create temporary pointer to point base node. It will be go up through looping
                Node* Added_node = new Node;
                Added_node -> key = k;                              //   X     - Added node - y 
                Added_node -> value = v;                            //   |          |
                Added_node -> node_level = 2 + i;                   //  prev   - Based node (temp)
                Added_node -> down = temp_base;
                Added_node -> up = nullptr;
                Added_node -> next = nullptr;
                Added_node -> prev = nullptr;
                Node* temp_add = Added_node;
                 // create new node, contains k and v, assign node level
                
                while(temp_base -> up == nullptr)
                {
                    temp_base = temp_base -> prev;
                }           
                temp_base = temp_base -> up;
                Added_node -> next = temp_base -> next;        // Added node's next = current's up's next
                Added_node -> prev = temp_base;               // Added node's prev = current's up                               // Added node's up = NULL for now
                temp_base -> next -> prev = Added_node;        // y's prev = Added node
                temp_base -> next = Added_node;                // x's next = Added node
                temp_add -> down -> up = Added_node;

                if (temp_base == topleft) // if x == topleft (vertical tail), then add new layer // x = topleft, add new layer (only +inf, -inf, and update topleft and right)
			    {
				    Node* Added_negative_inf = new Node;
				    Node* Added_positive_inf = new Node;
				
                    Added_negative_inf -> key = Key();
				    Added_negative_inf -> down = topleft;
	    		    Added_negative_inf -> up = nullptr;
			        Added_negative_inf -> prev = nullptr;
			        Added_negative_inf -> next = Added_positive_inf;

				    Added_positive_inf -> key = Key();
				    Added_positive_inf -> down = topright;
				    Added_positive_inf -> up = nullptr;
				    Added_positive_inf -> prev = Added_negative_inf;
				    Added_positive_inf -> next = nullptr;
						
				    topleft -> up = Added_negative_inf;
				    topleft = Added_negative_inf;
				    topright -> up = Added_positive_inf;
				    topright = Added_positive_inf; // create new layer

			        layer_level ++;
			    }
                temp_base = Added_node;                      // update current pointer to added node, Added_node becomes based_node
                
            }
            key_num ++;
        }
        return true;
    }
}

template<typename Key, typename Value>
std::vector<Key> SkipList<Key, Value>::allKeysInOrder() const 
{
    std::vector<Key> Ascending_order;
    Node* track = head -> next; // tracking pointer that starts from next of head since haed always point dummy.
    
    while(track != tail)
    {
        Ascending_order.push_back(track -> key);
        track = track -> next;
    }
    return Ascending_order;
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::isSmallestKey(const Key & k) const 
{
    if (head -> next -> key == k && head -> next != tail)
    {
        return true;
    }
    else if (head -> next -> key != k && head -> next != tail)
    {
        return false;
    }
    else if (head -> next == tail)
    {
        return false;
    }
    else
    {
        return false;
    }
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::isLargestKey(const Key & k) const 
{
    if (tail -> prev -> key == k && tail -> prev != head)
    {
        return true;
    }
    else if (tail -> prev -> key != k && tail -> prev != head)
    {
        return false;
    }
    else if (tail -> prev == head)
    {
        return false;
    }
    else
    {
        return false;
    }
}


#endif
