#include "convert.hpp"
#include "MyPriorityQueue.hpp"
#include "catch_amalgamated.hpp"
#include "ver.hpp"
#include <fstream>

namespace {
    TEST_CASE("MyPriorityQueue class test", "[MyPriorityQueue]") {
        MyPriorityQueue<int> pq;
        SECTION("test size()") {
            pq.insert(1);
            pq.insert(2);
            pq.insert(3);
            pq.insert(4);
            pq.insert(5);
            REQUIRE(pq.size() == 5);
        }
        SECTION("test empty()") {
            REQUIRE(pq.isEmpty() == true);
            pq.insert(1);
            REQUIRE(pq.isEmpty() == false);
        }
        SECTION("test min()") {
            pq.insert(1);
            pq.insert(2);
            pq.insert(3);
            pq.insert(4);
            pq.insert(5);
            REQUIRE(pq.min() == 1);
        }
        SECTION("insert with min extractions") {
            pq.insert(1);
            pq.insert(2);
            pq.insert(3);
            pq.insert(4);
            pq.insert(5);
            REQUIRE(pq.min() == 1);
            pq.extractMin();
            REQUIRE(pq.min() == 2);
            pq.extractMin();
            REQUIRE(pq.min() == 3);
            pq.extractMin();
            REQUIRE(pq.min() == 4);
            pq.extractMin();
            REQUIRE(pq.min() == 5);
        }
    }

    TEST_CASE("Empty to One Insertion", "[pq-custom]")
    {
        MyPriorityQueue<int> q;
        REQUIRE(q.isEmpty() == true);
        REQUIRE_THROWS_AS(q.min(), PriorityQueueEmptyException);
        REQUIRE_THROWS_AS(q.extractMin(), PriorityQueueEmptyException);
        q.insert(1);
        REQUIRE(q.min() == 1);
        REQUIRE(q.size() == 1);
    }

    TEST_CASE("Reversed 3 Insertion1", "[pq-custom]")
    {
        MyPriorityQueue<int> q;
        q.insert(3);
        q.insert(2);
        q.insert(1);
        REQUIRE(q.min() == 1);
        REQUIRE(q.size() == 3);
        q.extractMin();
        REQUIRE(q.min() == 2);
        REQUIRE(q.size() == 2);
        q.extractMin();
        REQUIRE(q.min() == 3);
        REQUIRE(q.size() == 1);
        q.extractMin();
        REQUIRE(q.size() == 0);
    }

    TEST_CASE("Reversed 15 Insertion", "[pq-custom]")
    {
        MyPriorityQueue<int> q;
        for(int i = 15; i >= 1; i--)
        {
            q.insert(i);
        }
        REQUIRE(q.min() == 1);
        REQUIRE(q.size() == 15);
        q.extractMin();
        REQUIRE(q.min() == 2);
        REQUIRE(q.size() == 14);
        q.extractMin();
        REQUIRE(q.min() == 3);
        REQUIRE(q.size() == 13);
        q.extractMin();
        REQUIRE(q.min() == 4);
        REQUIRE(q.size() == 12);
        q.extractMin();
        REQUIRE(q.min() == 5);
        REQUIRE(q.size() == 11);
        q.extractMin();
        REQUIRE(q.min() == 6);
        REQUIRE(q.size() == 10);
        q.extractMin();
        REQUIRE(q.min() == 7);
        REQUIRE(q.size() == 9);
        q.extractMin();
        REQUIRE(q.min() == 8);
        REQUIRE(q.size() == 8);
    }

    TEST_CASE("Huge Left", "[pq-custom]")
    {
        MyPriorityQueue<int> q;
        q.insert(1);
        q.insert(100);
        q.insert(5);
        q.insert(200);
        q.insert(300);
        q.insert(6);
        q.insert(7);
        q.insert(400);
        q.insert(500);
        REQUIRE(q.min() == 1);
        REQUIRE(q.size() == 9);
        q.extractMin();
        REQUIRE(q.min() == 5);
        REQUIRE(q.size() == 8);
        q.extractMin();
        REQUIRE(q.min() == 6);
        REQUIRE(q.size() == 7);
        q.extractMin();
        REQUIRE(q.min() == 7);
        REQUIRE(q.size() == 6);
        q.extractMin();
        REQUIRE(q.min() == 100);
        REQUIRE(q.size() == 5);
        q.extractMin();
        REQUIRE(q.min() == 200);
        REQUIRE(q.size() == 4);
        q.extractMin();
        REQUIRE(q.min() == 300);
        REQUIRE(q.size() == 3);
        q.extractMin();
        REQUIRE(q.min() == 400);
        REQUIRE(q.size() == 2);
        q.extractMin();
        REQUIRE(q.min() == 500);
        REQUIRE(q.size() == 1);
    }

    TEST_CASE("Huge Right", "[pq-custom]")
    {
        MyPriorityQueue<int> q;
        q.insert(1);
        q.insert(5);
        q.insert(100);
        q.insert(6);
        q.insert(7);
        q.insert(200);
        q.insert(300);
        q.insert(8);
        q.insert(9);
        REQUIRE(q.min() == 1);
        REQUIRE(q.size() == 9);
        q.extractMin();
        REQUIRE(q.min() == 5);
        REQUIRE(q.size() == 8);
        q.extractMin();
        REQUIRE(q.min() == 6);
        REQUIRE(q.size() == 7);
        q.extractMin();
        REQUIRE(q.min() == 7);
        REQUIRE(q.size() == 6);
        q.extractMin();
        REQUIRE(q.min() == 8);
        REQUIRE(q.size() == 5);
        q.extractMin();
        REQUIRE(q.min() == 9);
        REQUIRE(q.size() == 4);
        q.extractMin();
        REQUIRE(q.min() == 100);
        REQUIRE(q.size() == 3);
        q.extractMin();
        REQUIRE(q.min() == 200);
        REQUIRE(q.size() == 2);
        q.extractMin();
        REQUIRE(q.min() == 300);
        REQUIRE(q.size() == 1);
        q.extractMin();
    }

    TEST_CASE("Weird Insertion", "[pq-custom]")
    {
        MyPriorityQueue<int> q;
        for(int i = 1; i < 11; i++)
        {
            q.insert(i);
            q.insert(21 - i);
        }
        REQUIRE(q.min() == 1);
        REQUIRE(q.size() == 20);
        q.extractMin();
        REQUIRE(q.min() == 2);
        REQUIRE(q.size() == 19);
        q.extractMin();
        REQUIRE(q.min() == 3);
        REQUIRE(q.size() == 18);
        q.extractMin();
        REQUIRE(q.min() == 4);
        REQUIRE(q.size() == 17);
        q.extractMin();
        REQUIRE(q.min() == 5);
        REQUIRE(q.size() == 16);
        q.extractMin();
        REQUIRE(q.min() == 6);
        REQUIRE(q.size() == 15);
        q.extractMin();
        REQUIRE(q.min() == 7);
        REQUIRE(q.size() == 14);
        q.extractMin();
        REQUIRE(q.min() == 8);
        REQUIRE(q.size() == 13);
        q.extractMin();
        REQUIRE(q.min() == 9);
        REQUIRE(q.size() == 12);
        q.extractMin();
        REQUIRE(q.min() == 10);
        REQUIRE(q.size() == 11);
        q.extractMin();
        REQUIRE(q.min() == 11);
        REQUIRE(q.size() == 10);
        q.extractMin();
        REQUIRE(q.min() == 12);
        REQUIRE(q.size() == 9);
        q.extractMin();
        REQUIRE(q.min() == 13);
        REQUIRE(q.size() == 8);
        q.extractMin();
        REQUIRE(q.min() == 14);
        REQUIRE(q.size() == 7);
        q.extractMin();
        REQUIRE(q.min() == 15);
        REQUIRE(q.size() == 6);
        q.extractMin();
        REQUIRE(q.min() == 16);
        REQUIRE(q.size() == 5);
        q.extractMin();
        REQUIRE(q.min() == 17);
        REQUIRE(q.size() == 4);
        q.extractMin();
        REQUIRE(q.min() == 18);
        REQUIRE(q.size() == 3);
        q.extractMin();
        REQUIRE(q.min() == 19);
        REQUIRE(q.size() == 2);
        q.extractMin();
        REQUIRE(q.min() == 20);
        REQUIRE(q.size() == 1);
        q.extractMin();
        REQUIRE(q.size() == 0);
    } 

    TEST_CASE("Weird Insertion123", "[pq-custom]")
    {
        MyPriorityQueue<int> q;
        q.insert(1);
        q.insert(1);
        q.insert(1);
        q.insert(1);
        q.insert(2);
        q.insert(2);
        q.insert(2);
        q.insert(2);
        REQUIRE(q.min() == 1);
        REQUIRE(q.size() == 8);
        q.extractMin();
        REQUIRE(q.min() == 1);
        REQUIRE(q.size() == 7);
        q.extractMin();
        REQUIRE(q.min() == 1);
        REQUIRE(q.size() == 6);
        q.extractMin();
        REQUIRE(q.min() == 1);
        REQUIRE(q.size() == 5);
        q.extractMin();
        REQUIRE(q.min() == 2);
        REQUIRE(q.size() == 4);
        q.extractMin();
        REQUIRE(q.min() == 2);
        REQUIRE(q.size() == 3);
        q.extractMin();
        REQUIRE(q.min() == 2);
        REQUIRE(q.size() == 2);
        q.extractMin();
        REQUIRE(q.min() == 2);
        REQUIRE(q.size() == 1);
        q.extractMin();
    }


    TEST_CASE("AntToAunt", "[convert-custom]") {
    std::unordered_set<std::string> words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    std::vector<std::string> r = convert("ant", "aunt", words);

    REQUIRE(r.size() == 0);  // Assuming that "aunt" is not in the words set or
                            // there is no path from "ant" to "aunt"
    }

    TEST_CASE("AntToAnt", "[convert-custom]") {
    std::unordered_set<std::string> words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    std::vector<std::string> r = convert("ant", "ant", words);

    REQUIRE(r.size() == 0);
    }


    TEST_CASE("aback to sucks", "[convert-public]") 
    {
    std::unordered_set<std::string> words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    std::vector<std::string> r = convert("aback", "sucks", words);

    REQUIRE(r.size() == 0);  // Assuming that "sucks" is not in the words set or
                            // there is no path from "aback" to "sucks"
    }

TEST_CASE("test costs to pence", "[convert-public]")
{
	std::unordered_set<std::string> words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    std::vector< std::string > r = convert("costs", "pence", words);

    std::ifstream in2("words.txt");

    REQUIRE(r.size() == 11);
    REQUIRE(validConversion(r, "costs", "pence", in2));
}

    TEST_CASE("Reversed 3 Insertion", "[pq-custom]")
    {
        MyPriorityQueue<int> q;
        for(int i = 1; i < 100001; i++)
        {
            q.insert(i);
        }
        for(int i = 1; i < 100001; i++)
        {
            q.extractMin();
        }
    }

    TEST_CASE("SmokerToSoaked", "custom") 
    {
        std::unordered_set<std::string> words;    
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r  = convert("smoker", "soaked", words);

        std::ifstream in2("words.txt");
        
        REQUIRE(r.size() == 8);
        REQUIRE(  validConversion(r, "smoker", "soaked", in2) );
    }


}