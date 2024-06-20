#include "LLStack.hpp"
#include "catch.hpp"
#include "postfixCalc.hpp"

namespace
{

TEST_CASE("Empty stack", "[llstack]") {
        LLStack<int> a;
        REQUIRE(a.isEmpty());
        REQUIRE(a.size() == 0);
        REQUIRE_THROWS_AS(a.top(), StackEmptyException);
        REQUIRE_THROWS_AS(a.pop(), StackEmptyException);

        const LLStack<int> b{a};
        REQUIRE_THROWS_AS(b.top(), StackEmptyException);

        LLStack<int> c;
        c = a;
        REQUIRE(c.isEmpty());
        REQUIRE(c.size() == 0);
        REQUIRE_THROWS_AS(c.top(), StackEmptyException);
        REQUIRE_THROWS_AS(c.pop(), StackEmptyException);
    }

    TEST_CASE("One element stack", "[llstack]") {
        LLStack<int> a;
        a.push(10);
        const LLStack<int> b{a};
        LLStack<int> c{b};
        c = a;
        LLStack<int> d;
        d = c;
        LLStack<int> e{d};
        e.push(20);
        REQUIRE(e.size() == 2);
        e = d;

        REQUIRE_FALSE(e.isEmpty());
        REQUIRE(e.size() == 1);
        REQUIRE(e.top() == 10);
        REQUIRE_NOTHROW(e.pop());

        REQUIRE(e.isEmpty());
        REQUIRE(e.size() == 0);
        REQUIRE_THROWS_AS(e.top(), StackEmptyException);
        REQUIRE_THROWS_AS(e.pop(), StackEmptyException);

        REQUIRE_FALSE(c.isEmpty());
        REQUIRE(c.size() == 1);
        REQUIRE(c.top() == 10);
        REQUIRE_NOTHROW(c.pop());

        REQUIRE(c.isEmpty());
        REQUIRE(c.size() == 0);
        REQUIRE_THROWS_AS(c.top(), StackEmptyException);
        REQUIRE_THROWS_AS(c.pop(), StackEmptyException);

        REQUIRE_FALSE(d.isEmpty());
        REQUIRE(d.size() == 1);
        REQUIRE(d.top() == 10);
        REQUIRE_NOTHROW(d.pop());

        REQUIRE(d.isEmpty());
        REQUIRE(d.size() == 0);
        REQUIRE_THROWS_AS(d.top(), StackEmptyException);
        REQUIRE_THROWS_AS(d.pop(), StackEmptyException);

        REQUIRE_FALSE(a.isEmpty());
        REQUIRE(a.size() == 1);
        REQUIRE(a.top() == 10);
        REQUIRE_NOTHROW(a.pop());

        REQUIRE(a.isEmpty());
        REQUIRE(a.size() == 0);
        REQUIRE_THROWS_AS(a.top(), StackEmptyException);
        REQUIRE_THROWS_AS(a.pop(), StackEmptyException);

        REQUIRE_FALSE(b.isEmpty());
        REQUIRE(b.size() == 1);
        REQUIRE(b.top() == 10);
    }

    TEST_CASE("Multi element stack", "[llstack]") {
        LLStack<int> a;
        a.push(1);
        a.push(2);
        a.push(3);
        const LLStack<int> b{a};
        LLStack<int> c{a};
        LLStack<int> d{b};
        d = a;
        LLStack<int> e;
        e = d;
        LLStack<int> f{d};
        f.push(4);
        f.push(5);
        f = e;
        LLStack<int> g;
        g.push(1);
        REQUIRE(g.size() == 1);
        g = a;

        REQUIRE_FALSE(g.isEmpty());
        REQUIRE(g.size() == 3);
        REQUIRE(g.top() == 3);
        REQUIRE_NOTHROW(g.pop());

        REQUIRE_FALSE(g.isEmpty());
        REQUIRE(g.size() == 2);
        REQUIRE(g.top() == 2);
        REQUIRE_NOTHROW(g.pop());

        REQUIRE_FALSE(g.isEmpty());
        REQUIRE(g.size() == 1);
        REQUIRE(g.top() == 1);
        REQUIRE_NOTHROW(g.pop());

        REQUIRE(g.isEmpty());
        REQUIRE(g.size() == 0);
        REQUIRE_THROWS_AS(g.top(), StackEmptyException);
        REQUIRE_THROWS_AS(g.pop(), StackEmptyException);

        REQUIRE_FALSE(f.isEmpty());
        REQUIRE(f.size() == 3);
        REQUIRE(f.top() == 3);
        REQUIRE_NOTHROW(f.pop());

        REQUIRE_FALSE(f.isEmpty());
        REQUIRE(f.size() == 2);
        REQUIRE(f.top() == 2);
        REQUIRE_NOTHROW(f.pop());

        REQUIRE_FALSE(f.isEmpty());
        REQUIRE(f.size() == 1);
        REQUIRE(f.top() == 1);
        REQUIRE_NOTHROW(f.pop());

        REQUIRE(f.isEmpty());
        REQUIRE(f.size() == 0);
        REQUIRE_THROWS_AS(f.top(), StackEmptyException);
        REQUIRE_THROWS_AS(f.pop(), StackEmptyException);

        REQUIRE_FALSE(e.isEmpty());
        REQUIRE(e.size() == 3);
        REQUIRE(e.top() == 3);
        REQUIRE_NOTHROW(e.pop());

        REQUIRE_FALSE(e.isEmpty());
        REQUIRE(e.size() == 2);
        REQUIRE(e.top() == 2);
        REQUIRE_NOTHROW(e.pop());

        REQUIRE_FALSE(e.isEmpty());
        REQUIRE(e.size() == 1);
        REQUIRE(e.top() == 1);
        REQUIRE_NOTHROW(e.pop());

        REQUIRE(e.isEmpty());
        REQUIRE(e.size() == 0);
        REQUIRE_THROWS_AS(e.top(), StackEmptyException);
        REQUIRE_THROWS_AS(e.pop(), StackEmptyException);

        REQUIRE_FALSE(d.isEmpty());
        REQUIRE(d.size() == 3);
        REQUIRE(d.top() == 3);
        REQUIRE_NOTHROW(d.pop());

        REQUIRE_FALSE(d.isEmpty());
        REQUIRE(d.size() == 2);
        REQUIRE(d.top() == 2);
        REQUIRE_NOTHROW(d.pop());

        REQUIRE_FALSE(d.isEmpty());
        REQUIRE(d.size() == 1);
        REQUIRE(d.top() == 1);
        REQUIRE_NOTHROW(d.pop());

        REQUIRE(d.isEmpty());
        REQUIRE(d.size() == 0);
        REQUIRE_THROWS_AS(d.top(), StackEmptyException);
        REQUIRE_THROWS_AS(d.pop(), StackEmptyException);

        REQUIRE_FALSE(c.isEmpty());
        REQUIRE(c.size() == 3);
        REQUIRE(c.top() == 3);
        REQUIRE_NOTHROW(c.pop());

        REQUIRE_FALSE(c.isEmpty());
        REQUIRE(c.size() == 2);
        REQUIRE(c.top() == 2);
        REQUIRE_NOTHROW(c.pop());

        REQUIRE_FALSE(c.isEmpty());
        REQUIRE(c.size() == 1);
        REQUIRE(c.top() == 1);
        REQUIRE_NOTHROW(c.pop());

        REQUIRE(c.isEmpty());
        REQUIRE(c.size() == 0);
        REQUIRE_THROWS_AS(c.top(), StackEmptyException);
        REQUIRE_THROWS_AS(c.pop(), StackEmptyException);

        REQUIRE_FALSE(b.isEmpty());
        REQUIRE(b.size() == 3);
        REQUIRE(b.top() == 3);

        REQUIRE_FALSE(a.isEmpty());
        REQUIRE(a.size() == 3);
        REQUIRE(a.top() == 3);
        REQUIRE_NOTHROW(a.pop());

        REQUIRE_FALSE(a.isEmpty());
        REQUIRE(a.size() == 2);
        REQUIRE(a.top() == 2);
        REQUIRE_NOTHROW(a.pop());

        REQUIRE_FALSE(a.isEmpty());
        REQUIRE(a.size() == 1);
        REQUIRE(a.top() == 1);
        REQUIRE_NOTHROW(a.pop());

        REQUIRE(a.isEmpty());
        REQUIRE(a.size() == 0);
        REQUIRE_THROWS_AS(a.top(), StackEmptyException);
        REQUIRE_THROWS_AS(a.pop(), StackEmptyException);
    }

    TEST_CASE("Non-int stacks", "[llstack]") {
        LLStack<std::string> a;
        REQUIRE(a.size() == 0);
        REQUIRE_THROWS_AS(a.top(), StackEmptyException);
        REQUIRE_THROWS_AS(a.pop(), StackEmptyException);
        a.push("foo");
        REQUIRE(a.size() == 1);
        REQUIRE(a.top() == "foo");
        a.push("bar");
        REQUIRE(a.size() == 2);
        REQUIRE(a.top() == "bar");

        LLStack<std::string> b;
        b.push("foobar");
        a = b;
        b.pop();
        REQUIRE(b.size() == 0);
        REQUIRE(a.size() == 1);
        REQUIRE(a.top() == "foobar");
        a.push("thing");
        REQUIRE(a.size() == 2);
        REQUIRE(a.top() == "thing");
        LLStack<std::string> c{a};
        LLStack<std::string> d;
        a = d;
        REQUIRE(a.size() == 0);
        REQUIRE(a.isEmpty());
        REQUIRE(c.size() == 2);
        REQUIRE_FALSE(c.isEmpty());
        c.top() = "nothing";
        REQUIRE(c.top() == "nothing");
    }

    TEST_CASE("Miscellanous", "[llstack]") {
        LLStack<int> a;
        a.push(5);
        a.push(10);
        REQUIRE(a.top() == 10);
        a = a;
        REQUIRE(a.top() == 10);
        a.pop();
        REQUIRE(a.top() == 5);
        a.pop();
        REQUIRE_THROWS_AS(a.top(), StackEmptyException);
        REQUIRE_THROWS_AS(a.pop(), StackEmptyException);

        for (int i = 0; i < 10000; ++i) {
            a.push(i);
            REQUIRE(a.top() == i);
            REQUIRE((int) a.size() == i + 1);
        }
        a = a;
        LLStack<int> b{a};
        for (int i = 9999; i >= 0; --i) {
            REQUIRE(a.top() == i);
            a.pop();
            REQUIRE(b.top() == i);
            b.pop();
        }
        REQUIRE(a.size() == 0);
        REQUIRE(b.size() == 0);
    }

    TEST_CASE("Simple", "[postfix-calc]") {
        const std::vector<std::string> EXPRESSION = {"5", "3", "*"};
        REQUIRE(postfixCalculator(EXPRESSION) == 15);
    }

    TEST_CASE("Two operators", "[postfix-calc]") {
        const std::vector<std::string> EXPRESSION = {"5", "3", "2", "-", "*"};
        REQUIRE(postfixCalculator(EXPRESSION) == 5);
    }

    TEST_CASE("Remaining operands", "[postfix-calc]") {
        const std::vector<std::string> EXPRESSION = {"5", "3", "2", "1", "-", "*"};
        REQUIRE_THROWS_AS(postfixCalculator(EXPRESSION), CannotEvaluateException);
    }

    TEST_CASE("Empty", "[postfix-calc]") {
        const std::vector<std::string> EXPRESSION;
        REQUIRE_THROWS_AS(postfixCalculator(EXPRESSION), CannotEvaluateException);
    }

    TEST_CASE("One thing", "[postfix-calc]") {
        const std::vector<std::string> EXPRESSION = {"1"};
        REQUIRE(postfixCalculator(EXPRESSION) == 1);
    }

    TEST_CASE("Too many operations", "[postfix-calc]") {
        const std::vector<std::string> EXPRESSION = {"*"};
        REQUIRE_THROWS_AS(postfixCalculator(EXPRESSION), CannotEvaluateException);

        const std::vector<std::string> EXPRESSION2 = {"5", "3", "2", "1", "-", "*", "+", "+"};
        REQUIRE_THROWS_AS(postfixCalculator(EXPRESSION2), CannotEvaluateException);
    }

    TEST_CASE("Big", "[postfix-calc]") {
        const std::vector<std::string> EXPRESSION = {"4", "10", "3", "*" , "27", "-", "*", "6", "/", "9", "9", "/", "3", "*", "*"};
        REQUIRE(postfixCalculator(EXPRESSION) == 6);
    }

    TEST_CASE("Misc", "[postfix-calc]") {
        const std::vector<std::string> EXPRESSION = {"0", "0", "+", "0" , "0", "*", "+"};
        REQUIRE(postfixCalculator(EXPRESSION) == 0);

        const std::vector<std::string> EXPRESSION2 = {"4", "10", "3", "*" , "27", "-", "*", "6", "/", "9", "9", "/", "3", "*", "*", "0", "*"};
        REQUIRE(postfixCalculator(EXPRESSION2) == 0);

        const std::vector<std::string> EXPRESSION3 = {"4", "+"};
        REQUIRE_THROWS_AS(postfixCalculator(EXPRESSION3), CannotEvaluateException);

        const std::vector<std::string> EXPRESSION4 = {"4", "5", "-"};
        REQUIRE(postfixCalculator(EXPRESSION4) == 4294967295);

        const std::vector<std::string> EXPRESSION5 = {"2147483647", "1", "+"};
        REQUIRE(postfixCalculator(EXPRESSION5) == 2147483648);
    }
    // INSERT CUSTOM TESTS HERE!
}