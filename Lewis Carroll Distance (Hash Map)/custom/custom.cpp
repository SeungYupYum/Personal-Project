#include "Wordset.hpp"
#include "convert.hpp"
#include <vector>
#include <string>
#include <fstream>
#include "ver.hpp"
#include "catch_amalgamated.hpp"
namespace 
{

    /* TEST_CASE("AntToAunt", "[convert-custom]") 
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("ant", "aunt", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 0);
    }

    TEST_CASE("AntToAnt", "[convert-custom]") 
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("ant", "ant", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 1);
        REQUIRE(r[0] == "ant");
        REQUIRE(validConversion(r, "ant", "ant", in2));
    } */

    /* TEST_CASE("nested resize", "[wordset-custom]") 
    {
        // std::cout << "starting nested test\n";
        WordSet ws(1, 0);
        // std::cout << "inserting a\n";
        ws.insert("a");
        // std::cout << "inserting c\n";
        ws.insert("c");
        REQUIRE(ws.contains("a"));
        REQUIRE(ws.contains("c"));
        REQUIRE(ws.getCapacity() == 5);
        REQUIRE(ws.getCount() == 2);
    } */

    /* TEST_CASE("test contains", "[convert-public]")
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        REQUIRE(words.getCount() == 38607);
    }

    TEST_CASE("AntToArt123", "[convert-public]")
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r  = convert("ant", "art", words);

        // this was a success if r was a valid conversion of length 2.
        std::ifstream in2("words.txt");
        REQUIRE(words.contains("ant"));
        REQUIRE(words.contains("art"));
        REQUIRE(r.size() == 2);
        REQUIRE(validConversion(r, "ant", "art", in2));
    }

    TEST_CASE("AntToAunt123", "[convert-custom]") 
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("ant", "aunt", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 0);
    }

    TEST_CASE("AntToAnt123", "[convert-custom]") 
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("ant", "ant", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 1);
        REQUIRE(r[0] == "ant");
        REQUIRE(validConversion(r, "ant", "ant", in2));
    }


    TEST_CASE("nested resize123", "[wordset-custom]") 
    {
        // std::cout << "starting nested test\n";
        WordSet ws(1, 0);
        // std::cout << "inserting a\n";
        ws.insert("a");
        // std::cout << "inserting c\n";
        ws.insert("c");
        REQUIRE(ws.contains("a"));
        REQUIRE(ws.contains("c"));
		REQUIRE(ws.getCount() == 2);
        REQUIRE(ws.getCapacity() == 5);
    }

	TEST_CASE("test cat to cat123", "[convert-public]")
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("cat", "cat", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 1);
        REQUIRE(validConversion(r, "cat", "cat", in2));
    }

    TEST_CASE("test costs to pence123", "[convert-public]")
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("costs", "pence", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 11);
        REQUIRE(validConversion(r, "costs", "pence", in2));
    }

    TEST_CASE("test rouge to cheek123", "[convert-public]")
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("rouge", "cheek", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 17);
        REQUIRE(validConversion(r, "rouge", "cheek", in2));
    }

    TEST_CASE("test cold to warm123", "[convert-public]")
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("cold", "warm", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 5);
        REQUIRE(validConversion(r, "cold", "warm", in2));
    }

	TEST_CASE("test contains123", "[convert-public]")
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);
        REQUIRE(words.getCount() == 38607);
    } 

    TEST_CASE("aback to sucks", "[convert-public]")
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);

        std::vector< std::string > r = convert("aback", "sucks", words);

        std::ifstream in2("words.txt");

        REQUIRE(r.size() == 0);
    }

    TEST_CASE("new test contains", "[convert-public]")
    {
        WordSet words(11);
        std::ifstream in("words.txt");
        loadWordsIntoTable(words, in);
        REQUIRE(words.getCapacity() == 205759);
        REQUIRE(words.getCount() == 38607);
    } */

    TEST_CASE("wordset insert conflict", "[wordset-public]")
    {
        WordSet ws(11);
        ws.insert("aez");
        ws.insert("bdy");
        ws.insert("ccx");
        REQUIRE(ws.contains("aez"));
        REQUIRE(ws.contains("bdy"));
        REQUIRE(ws.contains("ccx"));
        REQUIRE(ws.getCapacity() == 23);
    }
}