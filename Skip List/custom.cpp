#include "SkipList.hpp"
#include "catch_amalgamated.hpp"

namespace {

	/* TEST_CASE("SimpleInteger", "[skip-list]")
	{
		SkipList<unsigned, unsigned> sl;
		std::vector<unsigned> order;
		for(unsigned i=0; i < 200000; i++)
		{
			sl.insert(i,i);		
			order.push_back(i);
		} 
		REQUIRE(order == sl.allKeysInOrder());
	} */

	TEST_CASE("SimpleInteger", "[skip-list]")
	{
		SkipList<unsigned, unsigned> sl;
		for (unsigned i = 0; i < 18; i++)
		{
			sl.insert(i, i);	
			
		} 
		
	}



}