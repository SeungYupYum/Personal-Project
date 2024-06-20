#include "catch.hpp"
#include "gradeYesAnswer.hpp"
#include "puzzleSolver.hpp"

namespace {

    TEST_CASE("SOLVE(ABC + D = HHHHHEHG) LEADING ZERO TRUE", "[solver]") 
    {
        std::unordered_map<char, unsigned> mapping;
        std::string s1 = "ABC";
        std::string s2 = "D";
        std::string s3 = "HHHHHEHG";

        bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
        REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("SOLVE(WALK + LONG = TRAIL)", "[solver]")
    {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "WALK";
    std::string s2 = "LONG";
    std::string s3 = "TRAIL";


    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test SHHA + DSFQ = ODTCC", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "SHHA";
     std::string s2 = "DSFQ";
    std::string s3 = "ODTCC";
  
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test CSNJU + MMW = RBHN", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "CSNJU";
    std::string s2 = "MMW";
    std::string s3 = "RBHN";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test FBG + MKP = LVDU", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "FBG";
    std::string s2 = "MKP";
    std::string s3 = "LVDU";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test AHE + TCZS = JDZN", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "AHE";
    std::string s2 = "TCZS";
    std::string s3 = "JDZN";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test NKXNN + DNGGWK = BJSNGJI", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "NKXNN";
    std::string s2 = "DNGGWK";
    std::string s3 = "BJSNGJI";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test OIRZD + ZLVN = HIGHG", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "OIRZD";
    std::string s2 = "ZLVN";
    std::string s3 = "HIGHG";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test GXWXF + FXH = SZRKD", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "GXWXF";
    std::string s2 = "FXH";
    std::string s3 = "SZRKD";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test YYZF + ZLE = UNQQ", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "YYZF";
    std::string s2 = "ZLE";
    std::string s3 = "UNQQ";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test IQI + QZT = DTH", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "IQI";
    std::string s2 = "QZT";
    std::string s3 = "DTH";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test ABB + VLJZ = QEQ", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "ABB";
    std::string s2 = "VLJZ";
    std::string s3 = "QEQ";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test MPP + WFSMM = JHQS", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "MPP";
    std::string s2 = "WFSMM";
    std::string s3 = "JHQS";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test CZQ + IFS = ALBA", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "CZQ";
    std::string s2 = "IFS";
    std::string s3 = "ALBA";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test GXOV + FLF = KUP", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "GXOV";
    std::string s2 = "FLF";
    std::string s3 = "KUP";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test MWWA + KLU = HHHY", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "MWWA";
    std::string s2 = "KLU";
    std::string s3 = "HHHY";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test DMQ + HHAS = WBHCH", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "DMQ";
    std::string s2 = "HHAS";
    std::string s3 = "WBHCH";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test QAIPT + IMM = YZJC", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "QAIPT";
    std::string s2 = "IMM";
    std::string s3 = "YZJC";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test NIVB + ZNGFI = GFHMX", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "NIVB";
    std::string s2 = "ZNGFI";
    std::string s3 = "GFHMX";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test FFU + GRPR = WZATQ", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "FFU";
    std::string s2 = "GRPR";
    std::string s3 = "WZATQ";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test HPY + ZXMZK = VVMN", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "HPY";
    std::string s2 = "ZXMZK";
    std::string s3 = "VVMN";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test GDEPK + WPJS = RSYD", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "GDEPK";
    std::string s2 = "WPJS";
    std::string s3 = "RSYD";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test MJF + WHJW = CFPG", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "MJF";
    std::string s2 = "WHJW";
    std::string s3 = "CFPG";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test OTCC + LQA = YIOU", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "OTCC";
    std::string s2 = "LQA";
    std::string s3 = "YIOU";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test QSIOY + RPTK = JQTR", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "QSIOY";
    std::string s2 = "RPTK";
    std::string s3 = "JQTR";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test WUX + TFUL = XILGO", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "WUX";
    std::string s2 = "TFUL";
    std::string s3 = "XILGO";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test MKN + LTC = SSD", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "MKN";
    std::string s2 = "LTC";
    std::string s3 = "SSD";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test MMU + EDUZ = WKSCR", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "MMU";
    std::string s2 = "EDUZ";
    std::string s3 = "WKSCR";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test JHCY + MXSG = MDHH", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "JHCY";
    std::string s2 = "MXSG";
    std::string s3 = "MDHH";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test ZWTT + YNHDGT = MWLYZ", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "ZWTT";
    std::string s2 = "YNHDGT";
    std::string s3 = "MWLYZ";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test KPMXH + APOUL = OUZMX", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "KPMXH";
    std::string s2 = "APOUL";
    std::string s3 = "OUZMX";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test VVRS + CTP = ZFY", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "VVRS";
    std::string s2 = "CTP";
    std::string s3 = "ZFY";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test KHN + OUWS = WLIO", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "KHN";
    std::string s2 = "OUWS";
    std::string s3 = "WLIO";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test JYK + BCK = JTMH", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "JYK";
    std::string s2 = "BCK";
    std::string s3 = "JTMH";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test XZWS + SOWS = WULRW", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "XZWS";
    std::string s2 = "SOWS";
    std::string s3 = "WULRW";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test PWK + MSK = HIPLR", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "PWK";
    std::string s2 = "MSK";
    std::string s3 = "HIPLR";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test HWK + GGQT = EPCKJ", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "HWK";
    std::string s2 = "GGQT";
    std::string s3 = "EPCKJ";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test BIUN + LPQ = BPRRC", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "BIUN";
    std::string s2 = "LPQ";
    std::string s3 = "BPRRC";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("Test UQMVL + XOV = WKPX", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "UQMVL";
    std::string s2 = "XOV";
    std::string s3 = "WKPX";
    
    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("SOLVE(SEND + MORE = MONEY) TRUE", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "SEND";
    std::string s2 = "MORE";
    std::string s3 = "MONEY";

    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("SOLVE(EAT + THAT = APPLE) TRUE", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "EAT";
    std::string s2 = "THAT";
    std::string s3 = "APPLE";

    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

    TEST_CASE("SOLVE(CATCH + BATCH = BATCH) FALSE", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "CATCH";
    std::string s2 = "BATCH";
    std::string s3 = "BATCH";

    REQUIRE_FALSE(puzzleSolver(s1, s2, s3, mapping));
    }

    TEST_CASE("SOLVE(ABCDEFGHIJ + FIJHDEBACG = IJHGFABCDE) MAX BOUND TOO BIG",
            "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "ABCDEFGHIJ";
    std::string s2 = "FIJHDEBACG";
    std::string s3 = "IJHGFABCDE";

    REQUIRE_FALSE(puzzleSolver(s1, s2, s3, mapping));
    }

    TEST_CASE(
        "SOLVE(ABDDEFGHIJIJABDDEFGHIJ + JBADEFGHIJABDDEFGHIJ = "
        "ABCDEFGHIJABDDEFGHIJ) TOO LARGE LETTERS",
        "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "ABDDEFGHIJIJABDDEFGHIJ";
    std::string s2 = "JBADEFGHIJABDDEFGHIJ";
    std::string s3 = "ABCDEFGHIJABDDEFGHIJ";
    
     REQUIRE_FALSE(puzzleSolver(s1, s2, s3, mapping));
    }

    TEST_CASE("SOLVE(AAAAAAAABCDEF + ABCDEF = GHIJKL) LEADING ZERO FALSE",
            "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "AAAAAAAABCDEF";
    std::string s2 = "ABCDEF";
    std::string s3 = "GHIJKL";

    REQUIRE_FALSE(puzzleSolver(s1, s2, s3, mapping));
    }

    TEST_CASE("SOLVE(AAAAAAAAAABC + DEF = HIJ) LEADING ZERO TRUE", "[solver]") {
    std::unordered_map<char, unsigned> mapping;
    std::string s1 = "AAAAAAAAAABC";
    std::string s2 = "DEF";
    std::string s3 = "HIJ";

    bool const has_answer = puzzleSolver(s1, s2, s3, mapping);
    REQUIRE((has_answer && gradeYesAnswer(s1, s2, s3, mapping)));
    }

}
