#include "Wordset.hpp"
#include <string>
#include <iostream>

unsigned square (unsigned a, unsigned b)
{
	unsigned result = 1;
	
	for(unsigned i = 0; i < b ; i++)
	{
		result = result * a;
	}
	return result;
}

unsigned Num_conversion(const std::string & s, unsigned base, unsigned mod)
{
	unsigned Number = 0;

	for(unsigned i = 0; i < s.length(); i++)
	{
		unsigned num1 = s[i] - 'a' + 1;
		unsigned exp = s.length() - i - 1;
		unsigned num2 = square(base, exp);
		unsigned result = (num1 * num2) % mod;
		Number = Number + result;
	}
	return Number;
}
// returns s, as a number in the given base, mod the given modulus
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod)
{
	//return 0; // this is probably not correct.
	unsigned Num = Num_conversion(s, base, mod);
	unsigned key = Num % mod;
	
	return key;
}

WordSet::WordSet(unsigned initialCapacity, unsigned evictionThreshold)
{
	Current_capacity = initialCapacity;
	T1 = new std::string[Current_capacity];
	T2 = new std::string[Current_capacity];
	word_num = 0;
	limit = evictionThreshold;
}

WordSet::~WordSet()
{
	delete [] T1;
	delete [] T2;
}

bool WordSet::isPrime(unsigned n)
{
    if (n <= 1)
	{
		return false;
	}
    if (n <= 3)
	{
		return true;
	}

    if (n % 2 == 0 || n % 3 == 0)
	{
		return false;
	}
   
    for (int i = 5; i * i <= n; i = i + 6)
	{
        if (n % i == 0 || n % (i + 2) == 0)
		{
			return false;
		}
	}
    return true;
}

unsigned WordSet::Next_prime(unsigned n)
{
    if (n <= 1)
	{
        return 2;
	}
 
    unsigned prime = 2 * n;
    bool found = false;

    while (found == false) 
	{
        prime++;
 
        if (isPrime(prime) == true)
		{
            found = true;
		}
    }
    return prime;
}

void WordSet::insert(const std::string & s)
{
	unsigned key_1 = polynomialHashFunction(s, BASE_H1, Current_capacity);

	if(T1[key_1] == "")
	{
		T1[key_1] = s;
		word_num ++;
		return;
	}
	else
	{
		std::string temp_T1 = T1[key_1]; // Always starting point, kicked out string from T1, get key_2 WITH BASE_H2
		std::string temp_T2 = ""; // kicked out string from T2, get key_1 WITH BASE_H1
		T1[key_1] = s;
		unsigned count = 0;

		while(count != limit)
		{
			if(temp_T1 != "" && temp_T2 == "")
			{
				unsigned temp_key_2 = polynomialHashFunction(temp_T1, BASE_H2, Current_capacity);
				if(T2[temp_key_2] != "")
				{
					temp_T2 = T2[temp_key_2];
					T2[temp_key_2] = temp_T1;
					temp_T1 = "";
					count ++;
				}
				else
				{
					temp_T2 = "";
					T2[temp_key_2] = temp_T1;
					temp_T1 = "";
					word_num ++;
					break;
				}
			}
			else if(temp_T2 != "" && temp_T1 == "")
			{
				unsigned temp_key_1 = polynomialHashFunction(temp_T2, BASE_H1, Current_capacity);
				if(T1[temp_key_1] != "")
				{
					temp_T1 = T1[temp_key_1];
					T1[temp_key_1] = temp_T2;
					temp_T2 = "";
					count ++;
				}
				else
				{
					temp_T1 = "";
					T1[temp_key_1] = temp_T2;
					temp_T2 = "";
					word_num ++;
					break;
				}				
			}
		}

		if(count != 1 && count < limit)
		{
			count = 0;
			return;
		}

		if(count == limit)
		{
			unsigned temp_capacity = Current_capacity;
			Current_capacity = Next_prime(Current_capacity);

			std::string* New_T1 = new std::string [Current_capacity];
			std::string* New_T2 = new std::string [Current_capacity];

			std::string* temp_1 = T1;
			std::string* temp_2 = T2;

			T1 = New_T1;
			T2 = New_T2;

			int Current_word_num = word_num;

			for(unsigned i = 0; i < temp_capacity; i++) // iteratring T1
			{
				if(temp_1[i] != "")
				{
					insert(temp_1[i]);
				}
			}

			for(unsigned j = 0; j < temp_capacity; j++) // iterating T2
			{
				if(temp_2[j] != "")
				{
					insert(temp_2[j]);
				}
			}

			word_num = Current_word_num;
			if(temp_T1 != "")
			{
				insert(temp_T1);
			}
			else if(temp_T2 != "")
			{
				insert(temp_T2);
			}
			
			delete [] temp_1;
			delete [] temp_2;

			New_T1 = nullptr;
			New_T2 = nullptr;
			temp_1 = nullptr;
			temp_2 = nullptr;


			count = 0;
			return;
		}
	}
	return;
}


bool WordSet::contains(const std::string & s) const
{
	//return false;  // stub, not correct.
	unsigned key_1 = polynomialHashFunction(s, BASE_H1, Current_capacity);
	unsigned key_2 = polynomialHashFunction(s, BASE_H2, Current_capacity);

	if(T1[key_1] == s)
	{
		return true;
	}
	else if(T2[key_2] == s)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// return how many distinct strings are in the set
unsigned WordSet::getCount() const
{
	// return BASE_H1 + BASE_H2; // this is not the right answer. 
	return word_num;
}

// return how large the underlying array is.
unsigned WordSet::getCapacity() const
{
	// return 1729; // that isn't even a prime number!
	return Current_capacity;
}
