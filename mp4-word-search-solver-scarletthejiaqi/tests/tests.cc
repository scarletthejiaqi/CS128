// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Jiaqi He                   Environment : ubuntu:bionic               //
//  Date ......: 2022/03/01                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Simple with direction", "[with direction]") { 
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'l', 'l', 'o'},
                                        {'e', 'e', 'e', 'e', 'o'},
                                        {'l', 'a', 'k', 'o', 'm'},
                                        {'w', 'e', 't', 'o', 'u'},
                                        {'o', 'e', 't', 'o', 'u'}};

    WordSearchSolver wss(puzzle);
    SECTION("Horizontal","[hori]") {
        WordLocation result = wss.FindWord("hello", CheckDirection::kHorizontal);
        REQUIRE(result.word == "hello");
        std::vector<CharPositions> c = {{'h',0,0},
                                        {'e',0,1},
                                        {'l',0,2},
                                        {'l',0,3},
                                        {'o',0,4}};
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("Vertical","[vert]") {
        WordLocation result2 = wss.FindWord("helwo", CheckDirection::kVertical);
        REQUIRE(result2.word == "helwo");
        std::vector<CharPositions> c = {{'h',0,0},
                                        {'e',1,0},
                                        {'l',2,0},
                                        {'w',3,0},
                                        {'o',4,0}};
        for (unsigned int i = 0; i < result2.char_positions.size(); ++i) {
            REQUIRE(result2.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result2.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result2.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("LeftDiag","[left]") {
        WordLocation result = wss.FindWord("oekeo", CheckDirection::kLeftDiag);
        REQUIRE(result.word == "oekeo");
        std::vector<CharPositions> c = {{'o',0,4},
                                        {'e',1,3},
                                        {'k',2,2},
                                        {'e',3,1},
                                        {'o',4,0}};
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("RightDiag","[right]") {
        WordLocation result = wss.FindWord("hekou", CheckDirection::kRightDiag);
        REQUIRE(result.word == "hekou");
        std::vector<CharPositions> c = {{'h',0,0},
                                        {'e',1,1},
                                        {'k',2,2},
                                        {'o',3,3},
                                        {'u',4,4}};
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("No match","[nomatch]") {
        WordLocation result = wss.FindWord("abcd", CheckDirection::kHorizontal);
        REQUIRE(result.word.empty());
        result = wss.FindWord("abcd", CheckDirection::kVertical);
        REQUIRE(result.word.empty());
        result = wss.FindWord("abcd", CheckDirection::kLeftDiag);
        REQUIRE(result.word.empty());
        result = wss.FindWord("abcd", CheckDirection::kRightDiag);
        REQUIRE(result.word.empty());
        result = wss.FindWord("abcd");
        REQUIRE(result.word.empty());
    }
    
}

TEST_CASE("Simple without direction","[without direction]") {
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'l', 'l', 'o'},
                                        {'e', 'e', 'e', 'e', 'o'},
                                        {'l', 'a', 'k', 'o', 'm'},
                                        {'w', 'e', 't', 'o', 'u'},
                                        {'o', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    SECTION("Horizontal","[hori]") {
        WordLocation result = wss.FindWord("hello");
        REQUIRE(result.word == "hello");
        std::vector<CharPositions> c = {{'h',0,0},
                                        {'e',0,1},
                                        {'l',0,2},
                                        {'l',0,3},
                                        {'o',0,4}};
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("Vertical","[vert]") {
        WordLocation result2 = wss.FindWord("helwo");
        REQUIRE(result2.word == "helwo");
        std::vector<CharPositions> c = {{'h',0,0},
                                        {'e',1,0},
                                        {'l',2,0},
                                        {'w',3,0},
                                        {'o',4,0}};
        for (unsigned int i = 0; i < result2.char_positions.size(); ++i) {
            REQUIRE(result2.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result2.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result2.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("LeftDiag","[left]") {
        WordLocation result = wss.FindWord("oekeo");
        REQUIRE(result.word == "oekeo");
        std::vector<CharPositions> c = {{'o',0,4},
                                        {'e',1,3},
                                        {'k',2,2},
                                        {'e',3,1},
                                        {'o',4,0}};
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("RightDiag","[right]") {
        WordLocation result = wss.FindWord("hekou");
        REQUIRE(result.word == "hekou");
        std::vector<CharPositions> c = {{'h',0,0},
                                        {'e',1,1},
                                        {'k',2,2},
                                        {'o',3,3},
                                        {'u',4,4}};
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
    
}

TEST_CASE("Substring", "[substring with direction]") { 
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'l', 'l', 'o'},
                                        {'e', 'e', 'e', 'e', 'o'},
                                        {'l', 'a', 'k', 'o', 'm'},
                                        {'w', 'e', 't', 'o', 'u'},
                                        {'o', 'e', 't', 'o', 'u'}};

    WordSearchSolver wss(puzzle);
    SECTION("Horizontal","[hori]") {
        WordLocation result = wss.FindWord("ell", CheckDirection::kHorizontal);
        REQUIRE(result.word == "ell");
        std::vector<CharPositions> c = {
                                        {'e',0,1},
                                        {'l',0,2},
                                        {'l',0,3}
                                        };
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("Vertical","[vert]") {
        WordLocation result2 = wss.FindWord("elw", CheckDirection::kVertical);
        REQUIRE(result2.word == "elw");
        std::vector<CharPositions> c = {
                                        {'e',1,0},
                                        {'l',2,0},
                                        {'w',3,0}
                                        };
        for (unsigned int i = 0; i < result2.char_positions.size(); ++i) {
            REQUIRE(result2.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result2.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result2.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("LeftDiag","[left]") {
        WordLocation result = wss.FindWord("eke", CheckDirection::kLeftDiag);
        REQUIRE(result.word == "eke");
        std::vector<CharPositions> c = {
                                        {'e',1,3},
                                        {'k',2,2},
                                        {'e',3,1}
                                        };
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("RightDiag","[right]") {
        WordLocation result = wss.FindWord("eko", CheckDirection::kRightDiag);
        REQUIRE(result.word == "eko");
        std::vector<CharPositions> c = {
                                        {'e',1,1},
                                        {'k',2,2},
                                        {'o',3,3}
                                        };
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
}
    
TEST_CASE("Substring without direction", "[substring without direction]") { 
    std::vector<std::vector<char>> puzzle{{'h', 'e', 'l', 'l', 'o'},
                                        {'e', 'e', 'e', 'e', 'o'},
                                        {'l', 'a', 'k', 'o', 'm'},
                                        {'w', 'e', 't', 'o', 'u'},
                                        {'o', 'e', 't', 'o', 'u'}};

    WordSearchSolver wss(puzzle);
    SECTION("Horizontal","[hori]") {
        WordLocation result = wss.FindWord("ell");
        REQUIRE(result.word == "ell");
        std::vector<CharPositions> c = {
                                        {'e',0,1},
                                        {'l',0,2},
                                        {'l',0,3}
                                        };
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("Vertical","[vert]") {
        WordLocation result2 = wss.FindWord("elw");
        REQUIRE(result2.word == "elw");
        std::vector<CharPositions> c = {
                                        {'e',1,0},
                                        {'l',2,0},
                                        {'w',3,0}
                                        };
        for (unsigned int i = 0; i < result2.char_positions.size(); ++i) {
            REQUIRE(result2.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result2.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result2.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("LeftDiag","[left]") {
        WordLocation result = wss.FindWord("eke");
        REQUIRE(result.word == "eke");
        std::vector<CharPositions> c = {
                                        {'e',1,3},
                                        {'k',2,2},
                                        {'e',3,1}
                                        };
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
    SECTION("RightDiag","[right]") {
        WordLocation result = wss.FindWord("eko");
        REQUIRE(result.word == "eko");
        std::vector<CharPositions> c = {
                                        {'e',1,1},
                                        {'k',2,2},
                                        {'o',3,3}
                                        };
        for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
        } 
    }
}
TEST_CASE("one list","[one line]") {
    std::vector<std::vector<char>> puzzle{{'h'},
                                        {'e'},
                                        {'l'},
                                        {'w'},
                                        {'o'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("elw");
    REQUIRE(result.word == "elw");
        std::vector<CharPositions> c = {
                                        {'e',1,0},
                                        {'l',2,0},
                                        {'w',3,0}
                                        };
    for (unsigned int i = 0; i < result.char_positions.size(); ++i) {
            REQUIRE(result.char_positions.at(i).character == c.at(i).character);
            REQUIRE(result.char_positions.at(i).row == c.at(i).row);
            REQUIRE(result.char_positions.at(i).col == c.at(i).col);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////