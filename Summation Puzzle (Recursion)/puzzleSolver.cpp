#include "puzzleSolver.hpp"
#include <deque>
// PART 1 - Summation Puzzle Verifier. See project write-up for details.

bool puzzleVerifier(const std::string& s1, const std::string& s2, const std::string& s3, const std::unordered_map<char, unsigned> &mapping)
{
	std::string str1 = "";
	std::string str2 = "";
	std::string str3 = "";
	unsigned int a = 0;
	unsigned int b = 0;
	unsigned int c = 0;

	for(size_t i = 0; i < s1.size(); i++)
	{
		a = mapping.at(s1[i]);
		str1 += std::to_string(a);
	}

	unsigned int x = atoi(str1.c_str());

	for(size_t i = 0; i < s2.size(); i++)
	{
		b = mapping.at(s2[i]);
		str2 += std::to_string(b);
	}

	unsigned int y = atoi(str2.c_str());

	for(size_t i = 0; i < s3.size(); i++)
	{
		c = mapping.at(s3[i]);
		str3 += std::to_string(c);
	}

	unsigned int z = atoi(str3.c_str());
	unsigned int w = x + y;
	return (w == z);
}


bool Recursion(const std::string &s1, const std::string &s2, const std::string &s3, std::unordered_map<char, unsigned> &mapping, std::deque <unsigned int> &Unused_num, std::deque <char> &Unused_letter, std::deque <unsigned int> &Used_num, std::deque <char> &Used_letter)
{
	if(Unused_letter.empty() == true) // if mapping size is same as used letter set and used number set,
	{
		if (puzzleVerifier(s1, s2, s3, mapping) == true) // then do verifier, if it is true, 
		{
			return true;	// return true
		}
		else
		{
			return false; // otherwise, false
		}
	}

	
	for (long unsigned int i = 0; i < Unused_num.size(); i++) // It represent going thorugh all unused number deque
	{   
		mapping[Unused_letter.front()] = Unused_num.front(); // mapping first letter of unused_letter to first digit of unused_number

		Used_num.push_back(Unused_num.front()); // put right-before-used number in unused set to used number set
		Used_letter.push_back(Unused_letter.front()); // put right-before-used letter in unused set to used letter set

		Unused_num.pop_front(); //pop right-before-used number from unused set since it was just mapped
		Unused_letter.pop_front(); //pop right-before-used letter from unused set since it was just mapped

		if(Recursion(s1, s2, s3, mapping, Unused_num, Unused_letter, Used_num, Used_letter) == false)
		{
			Unused_num.push_back(Used_num.back()); // put last assgiend number to last deque of unused number set
			Unused_letter.push_front(Used_letter.back()); // NOTE: Twist order for the case where # of unique letter = # of possible digits
			Used_num.pop_back(); // delete last letter from used set since we put it back
			Used_letter.pop_back(); // delete last number from used set since we put it back
		}
		else
		{
			return true;
		}
	}
	return false;
}


bool puzzleSolver(const std::string &s1, const std::string &s2, const std::string &s3, std::unordered_map<char, unsigned> &mapping)
{
    std::string result = s1 + s2 + s3; // Delete duplicate letter to assign value, store at s4
    std::string s4;
    for (char ch : s1 + s2 + s3) 
	{
        if (s4.find(ch) == std::string::npos) 
		{
            s4 += ch; //s4 contains unique letter
        }
    }

    if (s4.size() > 10) // Exit case : if the number of type of letter is greater than 10, than number cannot be assigned. (Number = 0 ~ 9)
    {
        return false;
    }

	if (s4.size() == 0) //Exit case : if 3 strings are empty, then return false for just in case
	{
		return false;
	}

    std::deque<unsigned int> Number_deque = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // for intial unused number set.
	std::deque<char> Letter_deque; // for unused letter set
	std::deque<unsigned int> Initial_used_number; // for used number set.
	std::deque<char> Initial_used_letter; // for used letter set.

	for(size_t i = 0; i < s4.size(); i++) // put s4's charaters to Letter_deque.
	{
		Letter_deque.push_back(s4[i]);
	}

    return Recursion(s1, s2, s3, mapping, Number_deque, Letter_deque, Initial_used_number, Initial_used_letter);
}
