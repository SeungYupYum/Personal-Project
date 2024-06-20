#include "catch_amalgamated.hpp"
#include "MyAVLTree.hpp"
#include <string>
#include <sstream>
#include <vector>

namespace 
{
    TEST_CASE("WORST INSERTION", "[avl-custom]")
    {
        MyAVLTree<int, std::string> tree;
        REQUIRE( tree.isEmpty() == true );

        tree.insert(1, "A");
        tree.insert(2, "B");
        tree.insert(3, "C");
        tree.insert(4, "D");
        tree.insert(5, "E");
        tree.insert(6, "F");
        tree.insert(7, "G");
        tree.insert(8, "H");
        tree.insert(9, "I");
        tree.insert(10, "J");

        REQUIRE(tree.contains(1) == true);
        REQUIRE(tree.contains(2) == true);
        REQUIRE(tree.contains(3) == true);
        REQUIRE(tree.contains(4) == true);
        REQUIRE(tree.contains(5) == true);
        REQUIRE(tree.contains(6) == true);
        REQUIRE(tree.contains(7) == true);
        REQUIRE(tree.contains(8) == true);
        REQUIRE(tree.contains(9) == true);
        REQUIRE(tree.contains(10) == true);

        REQUIRE(tree.size() == 10);

        std::vector<int> In_order_trav = tree.inOrder();
	    std::vector<int> In_order_expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	    REQUIRE( In_order_trav == In_order_expected );

        std::vector<int> Pre_order_trav = tree.preOrder();
	    std::vector<int> Pre_order_expected = {4, 2, 1, 3, 8, 6, 5, 7, 9, 10};
	    REQUIRE( Pre_order_trav == Pre_order_expected );        

        std::vector<int> Post_order_trav = tree.postOrder();
	    std::vector<int> Post_order_expected = {1, 3, 2, 5, 7, 6, 10, 9, 8, 4};
	    REQUIRE( Post_order_trav == Post_order_expected );

        REQUIRE( tree.height(1) == 0 );
        REQUIRE( tree.height(2) == 1 );
        REQUIRE( tree.height(3) == 0 );
        REQUIRE( tree.height(4) == 3 );
        REQUIRE( tree.height(5) == 0 );
        REQUIRE( tree.height(6) == 1 );
        REQUIRE( tree.height(7) == 0 );
        REQUIRE( tree.height(8) == 2 );
        REQUIRE( tree.height(9) == 1 );
        REQUIRE( tree.height(10) == 0 );

        REQUIRE( tree.find(1) == "A" );
        REQUIRE( tree.find(2) == "B" );
        REQUIRE( tree.find(3) == "C" );
        REQUIRE( tree.find(4) == "D" );
        REQUIRE( tree.find(5) == "E" );
        REQUIRE( tree.find(6) == "F" );
        REQUIRE( tree.find(7) == "G" );
        REQUIRE( tree.find(8) == "H" );
        REQUIRE( tree.find(9) == "I" );
        REQUIRE( tree.find(10) == "J" );

        REQUIRE( tree.isEmpty() == false );
    }

    TEST_CASE("WORST INSERTION 2", "[avl-custom]")
    {
        MyAVLTree<int, std::string> tree;
        REQUIRE( tree.isEmpty() == true );

        tree.insert(10, "A");
        tree.insert(9, "B");
        tree.insert(8, "C");
        tree.insert(7, "D");
        tree.insert(6, "E");
        tree.insert(5, "F");
        tree.insert(4, "G");
        tree.insert(3, "H");
        tree.insert(2, "I");
        tree.insert(1, "J");

        REQUIRE(tree.contains(1) == true);
        REQUIRE(tree.contains(2) == true);
        REQUIRE(tree.contains(3) == true);
        REQUIRE(tree.contains(4) == true);
        REQUIRE(tree.contains(5) == true);
        REQUIRE(tree.contains(6) == true);
        REQUIRE(tree.contains(7) == true);
        REQUIRE(tree.contains(8) == true);
        REQUIRE(tree.contains(9) == true);
        REQUIRE(tree.contains(10) == true);

        REQUIRE(tree.size() == 10);

        std::vector<int> In_order_trav = tree.inOrder();
	    std::vector<int> In_order_expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	    REQUIRE( In_order_trav == In_order_expected );

        std::vector<int> Pre_order_trav = tree.preOrder();
	    std::vector<int> Pre_order_expected = {7, 3, 2, 1, 5, 4, 6, 9, 8, 10};
	    REQUIRE( Pre_order_trav == Pre_order_expected );        

        std::vector<int> Post_order_trav = tree.postOrder();
	    std::vector<int> Post_order_expected = {1, 2, 4, 6, 5, 3, 8, 10, 9, 7};
	    REQUIRE( Post_order_trav == Post_order_expected );

        REQUIRE( tree.height(1) == 0 );
        REQUIRE( tree.height(2) == 1 );
        REQUIRE( tree.height(3) == 2 );
        REQUIRE( tree.height(4) == 0 );
        REQUIRE( tree.height(5) == 1 );
        REQUIRE( tree.height(6) == 0 );
        REQUIRE( tree.height(7) == 3 );
        REQUIRE( tree.height(8) == 0 );
        REQUIRE( tree.height(9) == 1 );
        REQUIRE( tree.height(10) == 0 );

        REQUIRE( tree.find(10) == "A" );
        REQUIRE( tree.find(9) == "B" );
        REQUIRE( tree.find(8) == "C" );
        REQUIRE( tree.find(7) == "D" );
        REQUIRE( tree.find(6) == "E" );
        REQUIRE( tree.find(5) == "F" );
        REQUIRE( tree.find(4) == "G" );
        REQUIRE( tree.find(3) == "H" );
        REQUIRE( tree.find(2) == "I" );
        REQUIRE( tree.find(1) == "J" );

        REQUIRE( tree.isEmpty() == false );
    }

    TEST_CASE("200,000 KEY INSERTION", "[avl-custom]")
    {
        MyAVLTree<int, int> tree;
        for(int i=0; i < 200000; i++)
		{
			tree.insert(i,i);
        }
        REQUIRE( tree.size() == 200000);
    }

    TEST_CASE("Exception test", "[avl-custom]")
    {
        MyAVLTree<int, std::string> tree;
        REQUIRE_THROWS_AS(tree.find(5), ElementNotFoundException);
        REQUIRE_THROWS_AS(tree.height(5), ElementNotFoundException);

        std::vector<int> In_order_expected = {};
        std::vector<int> Pre_order_expected = {};
        std::vector<int> Post_order_expected = {};
        std::vector<int> In_order_trav = tree.inOrder();
        std::vector<int> Pre_order_trav = tree.preOrder();
        std::vector<int> Post_order_trav = tree.postOrder(); 
        REQUIRE( In_order_trav == In_order_expected );        
	    REQUIRE( Pre_order_trav == Pre_order_expected );        
	    REQUIRE( Post_order_trav == Post_order_expected );        

        tree.insert(1, "A");
        REQUIRE_THROWS_AS(tree.find(5), ElementNotFoundException);
        REQUIRE_THROWS_AS(tree.height(5), ElementNotFoundException);
    }

    TEST_CASE("empty", "[avl-custom]")
	{
		MyAVLTree<int, std::string> tree;

		REQUIRE(tree.isEmpty());
		REQUIRE(tree.size() == 0);
		REQUIRE_FALSE(tree.contains(5));
		REQUIRE_THROWS_AS(tree.find(5), ElementNotFoundException);
		REQUIRE_THROWS_AS(tree.height(5), ElementNotFoundException);
	}

	TEST_CASE("find returns reference", "[avl-custom]")
	{
		MyAVLTree<int, std::string> tree;
		tree.insert(5, "pikachu");

		REQUIRE(tree.find(5) == "pikachu");

		tree.find(5) = "charmander";

		REQUIRE(tree.find(5) == "charmander");

		const MyAVLTree<int, std::string>& treeRef = tree;

		REQUIRE(treeRef.find(5) == "charmander");
	}

	TEST_CASE("two nodes", "[avl-custom]")
	{
		MyAVLTree<int, std::string> tree;
		tree.insert(5, "pikachu");
		tree.insert(10, "charmander");

		REQUIRE_FALSE(tree.isEmpty());
		REQUIRE(tree.size() == 2);
		REQUIRE(tree.contains(5));
		REQUIRE(tree.contains(10));
		REQUIRE(tree.find(5) == "pikachu");
		REQUIRE(tree.find(10) == "charmander");
		REQUIRE(tree.height(5) == 1);
		REQUIRE(tree.height(10) == 0);
	}

	TEST_CASE("no rotation", "[avl-custom]")
	{
		MyAVLTree<int, std::string> tree;
		tree.insert(5, "foo");
		tree.insert(3, "sna");
		tree.insert(10, "bar");
		tree.insert(12, "twelve");

		REQUIRE_FALSE(tree.isEmpty());
		REQUIRE(tree.size() == 4);
		REQUIRE(tree.contains(5));
		REQUIRE(tree.contains(3));
		REQUIRE(tree.contains(5));
		REQUIRE(tree.contains(12));
		REQUIRE(tree.find(5) == "foo");
		REQUIRE(tree.find(3) == "sna");
		REQUIRE(tree.find(10) == "bar");
		REQUIRE(tree.find(12) == "twelve");
		REQUIRE(tree.height(5) == 2);
		REQUIRE(tree.height(3) == 0);
		REQUIRE(tree.height(10) == 1);
		REQUIRE(tree.height(12) == 0);
	}

	TEST_CASE("basic rotation", "[avl-custom]")
	{
		MyAVLTree<int, std::string> tree;
		tree.insert(5, "foo");
		tree.insert(3, "sna");
		tree.insert(10, "bar");
		tree.insert(12, "twelve");
		tree.insert(15, "fifteen");

		REQUIRE_FALSE(tree.isEmpty());
		REQUIRE(tree.size() == 5);
		REQUIRE(tree.contains(5));
		REQUIRE(tree.contains(3));
		REQUIRE(tree.contains(5));
		REQUIRE(tree.contains(12));
		REQUIRE(tree.contains(15));
		REQUIRE(tree.find(5) == "foo");
		REQUIRE(tree.find(3) == "sna");
		REQUIRE(tree.find(10) == "bar");
		REQUIRE(tree.find(12) == "twelve");
		REQUIRE(tree.find(15) == "fifteen");
		REQUIRE(tree.height(5) == 2);
		REQUIRE(tree.height(3) == 0);
		REQUIRE(tree.height(10) == 0);
		REQUIRE(tree.height(12) == 1);
		REQUIRE(tree.height(15) == 0);
	}

	TEST_CASE("double rotation/median", "[avl-custom]")
	{
		MyAVLTree<int, std::string> tree;
		tree.insert(5, "foo");
		tree.insert(3, "sna");
		tree.insert(10, "bar");
		tree.insert(12, "twelve");
		tree.insert(11, "eleven");

		REQUIRE_FALSE(tree.isEmpty());
		REQUIRE(tree.size() == 5);
		REQUIRE(tree.contains(5));
		REQUIRE(tree.contains(3));
		REQUIRE(tree.contains(5));
		REQUIRE(tree.contains(12));
		REQUIRE(tree.contains(11));
		REQUIRE(tree.find(5) == "foo");
		REQUIRE(tree.find(3) == "sna");
		REQUIRE(tree.find(10) == "bar");
		REQUIRE(tree.find(12) == "twelve");
		REQUIRE(tree.find(11) == "eleven");
		REQUIRE(tree.height(5) == 2);
		REQUIRE(tree.height(3) == 0);
		REQUIRE(tree.height(10) == 0);
		REQUIRE(tree.height(12) == 0);
		REQUIRE(tree.height(11) == 1);
	}

	TEST_CASE("rotate at root", "[avl-custom]")
	{
		MyAVLTree<int, std::string> tree;
		tree.insert(5, "foo");
		tree.insert(3, "sna");
		tree.insert(7, "bar");
		tree.insert(1, "one");
		tree.insert(4, "four");
		tree.insert(2, "two");

		REQUIRE_FALSE(tree.isEmpty());
		REQUIRE(tree.size() == 6);
		REQUIRE(tree.contains(5));
		REQUIRE(tree.contains(3));
		REQUIRE(tree.contains(7));
		REQUIRE(tree.contains(1));
		REQUIRE(tree.contains(4));
		REQUIRE(tree.contains(2));
		REQUIRE(tree.find(5) == "foo");
		REQUIRE(tree.find(3) == "sna");
		REQUIRE(tree.find(7) == "bar");
		REQUIRE(tree.find(1) == "one");
		REQUIRE(tree.find(4) == "four");
		REQUIRE(tree.find(2) == "two");
		REQUIRE(tree.height(5) == 1);
		REQUIRE(tree.height(3) == 2);
		REQUIRE(tree.height(7) == 0);
		REQUIRE(tree.height(1) == 1);
		REQUIRE(tree.height(4) == 0);
		REQUIRE(tree.height(2) == 0);
	}

	TEST_CASE("traversals", "[avl-custom]")
	{
		MyAVLTree<int, std::string> tree;
		tree.insert(4, "");
		tree.insert(2, "");
		tree.insert(6, "");
		tree.insert(1, "");
		tree.insert(3, "");
		tree.insert(5, "");
		tree.insert(7, "");

		std::vector<int> trav = tree.inOrder();
		std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7};
		REQUIRE(trav == expected);

		trav = tree.preOrder();
		expected = {4, 2, 1, 3, 6, 5, 7};
		REQUIRE(trav == expected);

		trav = tree.postOrder();
		expected = {1, 3, 2, 5, 7, 6, 4};
		REQUIRE(trav == expected);
	}
}