#ifndef __WORD_SET___HPP
#define __WORD_SET___HPP


#include <string>

// You may assume, in writing this function, that the given
// string consists solely of lower-case letters.

// To get the "number" that a letter-digit represents,
// subtract 'a' from it.
// e.g., (s[0]-'a') is the most significant "digit" of s.
// That would give you a 0 for a, etc;  add one to get 'a' = 1, 'b' = 2, etc. 

// After every "digit" is processed, mod the current value by mod.
// This will keep you from having overflow.
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod);


class WordSet
{
public: 
	explicit WordSet(unsigned initialCapacity, unsigned evictionThreshold = DEFAULT_EVICT_THRESHOLD);
	~WordSet();

	// adds the given string to the WordSet, so that any 
	// future calls to contains(s) will return true.
	// Note that we are not implementing remove in this
	// project.
	// 
	void insert(const std::string & s);

	bool contains(const std::string & s) const;

	// return how many distinct strings are in the set
	unsigned getCount() const; 

	// return how large the underlying array is.
	unsigned getCapacity() const;

	unsigned square (unsigned a, unsigned b);
	unsigned Num_conversion(const std::string & s, unsigned base, unsigned mod);
	bool isPrime(unsigned n);
	unsigned Next_prime(unsigned n);

private:
	static constexpr unsigned BASE_H1 = 37;
	static constexpr unsigned BASE_H2 = 41; 
	// You may declare private functions and member variables here.
	static constexpr unsigned DEFAULT_EVICT_THRESHOLD = 5; 

	int word_num;
	std::string* T1;
	std::string* T2;
	unsigned Current_capacity;
	unsigned limit;
};


#endif
