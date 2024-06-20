#include "convert.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>


// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}

// You probably want to change this function.
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const WordSet & words)
{
	std::vector <std::string> solution;
	std::unordered_map <std::string, std::string> mapping;
	std::stack <std::string> reversed_solution;
	std::queue <std::string> word;

	if(s1 == s2)
	{
		solution.push_back(s1);
		return solution;
	}
	else if(s1.length() != s2.length())
	{
		return solution;
	}
	else // when s1.length and s2.length same, and s1 is not equal to s2
	{
		word.push(s1);

		while (word.empty() == false)
		{
			int Queue_size = word.size();
			int word_size = s1.size();
			
			for(int i = 0; i < Queue_size; i++)
			{
				std::string Current_word = word.front(); // current word is child (1 letter diff)
				std::string Original_word = Current_word; //original word is parent
				word.pop(); // take out the parent word from the queue

				for(int j = 0; j < word_size; j++)
				{
					char Original_charactor = Current_word[j];

					for (char Current_charactor = 'a'; Current_charactor <= 'z'; Current_charactor ++)
					{
						Current_word[j] = Current_charactor;

						if(words.contains(Current_word) == true) // if it is in the dictionary, 1. then check I already visited, 2. check it is original word
						{
							if(mapping.count(Current_word) == 1) // if it is already mapped, then skip
							{
								continue;
							}
							else // if it is not mapped, then check current word is different with original word,
							{
								if(Current_word != Original_word) // if it is different, map thenm, push, if the word is equal to s2 then stop.
								{
									word.push(Current_word);
									mapping[Current_word] = Original_word;
									if(Current_word == s2)
									{
										/* break; */
										reversed_solution.push(s2);
										std::string parent = mapping[s2];

										while(parent != s1)
										{
											reversed_solution.push(parent);
											parent = mapping[parent];
										}

										reversed_solution.push(s1); //at beginning, s1 didn't mapped due do original word thing.

										while(reversed_solution.empty() != true)
										{
											std::string solution_word = reversed_solution.top();
											solution.push_back(solution_word);
											reversed_solution.pop();
										}
										
										return solution;
									}
								}
								else // not mapped, but current_word = original, then skip
								{
									continue;
								}
							}
						}
						else // if it is not in the dictionary, skip it
						{
							continue;
						}
					}
					Current_word[j] = Original_charactor;
				}
			}
		}
		return solution;
	}
}