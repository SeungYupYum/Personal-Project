#include "convert.hpp"
#include <string>
#include <sstream>
#include <unordered_set>
#include <string>

#include "MyPriorityQueue.hpp"
#include <stack>
#include <unordered_map>
#include <vector>

struct node
{
	std::string word;
	int LCD;
	int LetterDelta;
	int H;
    bool operator<(const node& other) const 
	{
		if(H == other.H)
		{
			return LCD < other.LCD;
		}
		else
		{
			return H < other.H;
		}
    }
};

// You should not need to change this function.
void loadWordsIntoTable(std::unordered_set<std::string> & words, std::istream & in)
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

int LetterDelta(const std::string& word1, const std::string& word2) 
{
    int distance = 0;
    for (size_t i = 0; i < word1.size(); i++) 
	{
        if (word1[i] != word2[i]) 
		{
            distance ++;
        }
    }
    return distance;
}

// You probably want to change this function.
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words)
{
	std::vector <std::string> solution;
	std::unordered_map <std::string, std::string> mapping;
	std::stack <std::string> reversed_solution;
	MyPriorityQueue<node> pq;
	struct node H_value;

	if(s1 == s2)
	{
		return solution;
	}
	else if(s1.length() != s2.length())
	{
		return solution;
	}
	else
	{
		H_value.word = s1;
		H_value.LCD = 0;
		H_value.H = 0 + LetterDelta(s1, s2);
		pq.insert(H_value);

		while (pq.isEmpty() == false)
		{
			size_t Queue_size = pq.size();
			int word_size = s1.size();
			
			for(size_t i = 0; i < Queue_size; i++)
			{
				std::string Current_word = pq.min().word;
				std::string Original_word = Current_word;
				int Current_LCD = pq.min().LCD;
				pq.extractMin();

				for(int j = 0; j < word_size; j++)
				{
					char Original_charactor = Current_word[j];

					for (char Current_charactor = 'a'; Current_charactor <= 'z'; Current_charactor ++)
					{
						Current_word[j] = Current_charactor;

						if(words.count(Current_word) == 1)
						{
							if(mapping.count(Current_word) == 1)
							{
								continue;
							}
							else
							{
								if(Current_word != Original_word)
								{
									H_value.word = Current_word;
									H_value.LCD = Current_LCD + 1;
									H_value.LetterDelta = LetterDelta(Current_word, s2);
									H_value.H = Current_LCD + 1 + LetterDelta(Current_word, s2);
									pq.insert(H_value);
									mapping[Current_word] = Original_word;
									
									if(Current_word == s2)
									{
										reversed_solution.push(s2);
										std::string parent = mapping[s2];

										while(parent != s1)
										{
											reversed_solution.push(parent);
											parent = mapping[parent];
										}

										reversed_solution.push(s1);

										while(reversed_solution.empty() != true)
										{
											std::string solution_word = reversed_solution.top();
											solution.push_back(solution_word);
											reversed_solution.pop();
										}
										
										return solution;
									
									}
								}
								else
								{
									continue;
								}
							}
						}
						else
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

