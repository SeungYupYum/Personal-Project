#include "InterferenceGraph.hpp"
#include "CSVReader.hpp"
#include "IGWriter.hpp"
#include "register_allocation.hpp"
#include "catch_amalgamated.hpp"
#include "verifier.hpp"


namespace {
    TEST_CASE("RuntimeTest", "[ig-complete_1001]") 
    {
        const auto &GRAPH = "tests/graphs/syyum.csv";
        InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);
        REQUIRE(ig.numVertices() == 1001);
    }

    TEST_CASE("RuntimeTest", "[ig-complete_1000]") 
    {
        const auto &GRAPH = "tests/graphs/jake.csv";
        InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);

        for(unsigned i = 0; i < ig.numVertices() - 1; i++)
        {
            const std::string s = "Node_" + std::to_string(i); 
            REQUIRE(ig.neighbors(s).size() == 999);
        }

        REQUIRE(ig.numVertices() == 1000);
        REQUIRE(ig.numEdges() == 499500);

        ig.removeVertex("Node_1");
        REQUIRE(ig.numVertices() == 999);
        REQUIRE(ig.numEdges() == 498501);

        ig.removeEdge("Node_2", "Node_420");
        REQUIRE(ig.numEdges() == 498500);

        REQUIRE(ig.vertices().size() == 999);
        REQUIRE(ig.degree("Node_5") == 998);
        REQUIRE(ig.neighbors("Node_666").size() == 998);

        REQUIRE(ig.interferes("Node_5", "Node_10") == true);
    }

    TEST_CASE("SUMMIT_1 Success", "[ra-custom]") 
    {
        const auto &GRAPH = "tests/graphs/SUMMIT_1.csv";
        const auto NUM_REGS = 5;

        const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
        REQUIRE((verifyAllocation(GRAPH, NUM_REGS, allocation)));
    }

    TEST_CASE("SUMMIT_1 Fail", "[ra-custom]") 
    {
        const auto &GRAPH = "tests/graphs/SUMMIT_1.csv";
        const auto NUM_REGS = 4;

        const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
        REQUIRE((allocation.empty()));
    }

    TEST_CASE("SUMMIT_2 Success", "[ra-custom]") 
    {
        const auto &GRAPH = "tests/graphs/SUMMIT_2.csv";
        const auto NUM_REGS = 1;

        const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
        REQUIRE((verifyAllocation(GRAPH, NUM_REGS, allocation)));
    }

    TEST_CASE("SUMMIT_2 Fail", "[ra-custom]") 
    {
        const auto &GRAPH = "tests/graphs/SUMMIT_2.csv";
        const auto NUM_REGS = 0;

        const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
        REQUIRE((allocation.empty()));
    }

    TEST_CASE("SUMMIT_3 Success", "[ra-custom]") 
    {
        const auto &GRAPH = "tests/graphs/SUMMIT_3.csv";
        const auto NUM_REGS = 1;

        const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
        REQUIRE((verifyAllocation(GRAPH, NUM_REGS, allocation)));
    }

    TEST_CASE("P2 Runtime Test", "[ig-complete-250]")
    {
    // Load the graph pointed to by graph_stress_test.csv
    const auto &GRAPH = "tests/graphs/graph_stress_test.csv";
    const auto NUM_REGS = 500;
    const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
    IGWriter::write(CSVReader::load(GRAPH), "tests/graphs/stress_success.dot",allocation);

    REQUIRE((verifyAllocation(GRAPH, NUM_REGS, allocation)));
    }

    TEST_CASE("SUMMIT_4 Success", "[ra-custom]") 
    {
        const auto &GRAPH = "tests/graphs/SUMMIT_4.csv";
        const auto NUM_REGS = 10;

        const auto &allocation = assignRegisters(GRAPH, NUM_REGS);
        REQUIRE((verifyAllocation(GRAPH, NUM_REGS, allocation)));
    }

    TEST_CASE("SUMMIT_4 Basic-Test", "[ig-custom]") 
    {
        const auto &GRAPH = "tests/graphs/SUMMIT_4.csv";

        const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);
        const std::unordered_set<Variable> &a_expected_neighbors = {"b", "c"};
        const std::unordered_set<Variable> &b_expected_neighbors = {"a", "c", "d"};
        const std::unordered_set<Variable> &c_expected_neighbors = {"a", "b", "d", "e"};
        const std::unordered_set<Variable> &d_expected_neighbors = {"b", "c"};
        const std::unordered_set<Variable> &e_expected_neighbors = {"c", "f"};
        const std::unordered_set<Variable> &f_expected_neighbors = {"e", "g"};
        const std::unordered_set<Variable> &g_expected_neighbors = {"f"};
        const std::unordered_set<Variable> &expected_verticies = {"a", "b", "c", "d", "e", "f", "g"};

        REQUIRE(ig.neighbors("a") == a_expected_neighbors);
        REQUIRE(ig.neighbors("b") == b_expected_neighbors);
        REQUIRE(ig.neighbors("c") == c_expected_neighbors);
        REQUIRE(ig.neighbors("d") == d_expected_neighbors);
        REQUIRE(ig.neighbors("e") == e_expected_neighbors);
        REQUIRE(ig.neighbors("f") == f_expected_neighbors);
        REQUIRE(ig.neighbors("g") == g_expected_neighbors);
        REQUIRE(ig.vertices() == expected_verticies);
        REQUIRE(ig.numVertices() == 7);
        REQUIRE(ig.numEdges() == 8);
        // REQUIRE_THROWS_AS(ig.removeEdge("a", "g"), UnknownEdgeException);
        // REQUIRE_THROWS_AS(ig.removeEdge("z", "g"), UnknownVertexException);
        // REQUIRE_THROWS_AS(ig.removeVertex("z"), UnknownVertexException);
        REQUIRE_THROWS_AS(ig.interferes("z", "b"), UnknownVertexException);
        REQUIRE_THROWS_AS(ig.degree("z"), UnknownVertexException);
    }

    TEST_CASE("Complete6-BasicTests", "[ig-hydrohn]") 
    {
    const auto &GRAPH = "tests/graphs/complete_6.csv";
    const InterferenceGraph<Variable> &ig = CSVReader::load(GRAPH);
    const std::unordered_set<Variable> &expected_vertices = {"1", "2", "3", "4", "5", "6"};

    SECTION("CompleteVertexTest")
    {
        REQUIRE(ig.numVertices() == 6);
        REQUIRE(ig.vertices() == expected_vertices);
    }

    SECTION("EdgeCapacityTest")
    {
        REQUIRE(ig.numEdges() == 15);
    }
    
    SECTION("InterferesTestI")
    {
        REQUIRE(ig.interferes("1","2"));
        REQUIRE(ig.interferes("1","3"));
        REQUIRE(ig.interferes("1","4"));
        REQUIRE(ig.interferes("1","5"));
        REQUIRE(ig.interferes("1","6"));
        REQUIRE(ig.interferes("2","3"));
        REQUIRE(ig.interferes("2","4"));
        REQUIRE(ig.interferes("2","5"));
        REQUIRE(ig.interferes("2","6"));
        REQUIRE(ig.interferes("3","4"));
        REQUIRE(ig.interferes("3","5"));
        REQUIRE(ig.interferes("3","6"));
        REQUIRE(ig.interferes("4","5"));
        REQUIRE(ig.interferes("4","6"));
        REQUIRE(ig.interferes("5","6"));
    }

    SECTION("InterferesTestII")
    {
        REQUIRE(ig.interferes("2","1"));
        REQUIRE(ig.interferes("3","1"));
        REQUIRE(ig.interferes("4","1"));
        REQUIRE(ig.interferes("5","1"));
        REQUIRE(ig.interferes("6","1"));
        REQUIRE(ig.interferes("3","2"));
        REQUIRE(ig.interferes("4","2"));
        REQUIRE(ig.interferes("5","2"));
        REQUIRE(ig.interferes("6","2"));
        REQUIRE(ig.interferes("4","3"));
        REQUIRE(ig.interferes("5","3"));
        REQUIRE(ig.interferes("6","3"));
        REQUIRE(ig.interferes("5","4"));
        REQUIRE(ig.interferes("6","4"));
        REQUIRE(ig.interferes("6","5"));
    }

    const std::unordered_set<Variable> &expected_neighbors_1 = {"2", "3", "4", "5", "6"};
    const std::unordered_set<Variable> &expected_neighbors_2 = {"1", "3", "4", "5", "6"};
    const std::unordered_set<Variable> &expected_neighbors_3 = {"1", "2", "4", "5", "6"};
    const std::unordered_set<Variable> &expected_neighbors_4 = {"1", "2", "3", "5", "6"};
    const std::unordered_set<Variable> &expected_neighbors_5 = {"1", "2", "3", "4", "6"};
    const std::unordered_set<Variable> &expected_neighbors_6 = {"1", "2", "3", "4", "5"};


    SECTION("NeighborsTest")
    {
        REQUIRE(ig.neighbors("1") == expected_neighbors_1);
        REQUIRE(ig.neighbors("2") == expected_neighbors_2);
        REQUIRE(ig.neighbors("3") == expected_neighbors_3);
        REQUIRE(ig.neighbors("4") == expected_neighbors_4);
        REQUIRE(ig.neighbors("5") == expected_neighbors_5);
        REQUIRE(ig.neighbors("6") == expected_neighbors_6);
    }

    SECTION("CompleteGraphDegreeTest")
    {
        REQUIRE(ig.degree("1") == 5);
        REQUIRE(ig.degree("2") == 5);
        REQUIRE(ig.degree("2") == 5);
        REQUIRE(ig.degree("3") == 5);
        REQUIRE(ig.degree("4") == 5);
        REQUIRE(ig.degree("5") == 5);
        REQUIRE(ig.degree("6") == 5);
        REQUIRE(ig.numVertices() - 1 == 5);
    }

    }

    TEST_CASE("SimpleRemoveVertex", "[ig-hydrohn]") 
    {
    const auto &GRAPH = "tests/graphs/simple.csv";

    InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);
    ig.removeVertex("x");

    REQUIRE(ig.numEdges() == 1);
    REQUIRE(ig.numVertices() == 2);
    }

    TEST_CASE("OneNeighbor", "[ig-hydrohn]") {
    const auto &GRAPH = "tests/graphs/simple.csv";

    InterferenceGraph<Variable> ig = CSVReader::load(GRAPH);
    ig.removeVertex("x");

    const std::unordered_set<Variable> &expected_neighbors = {"z"};
    REQUIRE(ig.neighbors("y") == expected_neighbors);
    }
}