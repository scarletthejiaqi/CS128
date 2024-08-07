// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
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
#include <iostream>
#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Drop", "[Drop]") {
  Board test;
  InitBoard(test);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  SECTION("drop disk") {
    REQUIRE(test.board[0][0] == DiskType::kPlayer1);
    REQUIRE(test.board[1][0] == DiskType::kPlayer1);
  }
}
TEST_CASE("Location", "[location]") {
  REQUIRE_FALSE(BoardLocationInBounds(-1, 0));
  REQUIRE_FALSE(BoardLocationInBounds(1, 10));
  REQUIRE_FALSE(BoardLocationInBounds(1, -1));
  REQUIRE_FALSE(BoardLocationInBounds(10, 0));
  REQUIRE(BoardLocationInBounds(0, 0));
  REQUIRE(BoardLocationInBounds(5, 6));
}
TEST_CASE("Horizontal", "[horizontal_win]") {
  // SECTION("Can use sections") {}
  // clang-format off
  Board test;
  InitBoard(test);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer1,1);
  DropDiskToBoard(test,DiskType::kPlayer1,2);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  REQUIRE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kHorizontal));

}
TEST_CASE("Vertical", "[vertical_win]") {
  // SECTION("Can use sections") {}
  // clang-format off
  Board test;
  InitBoard(test);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  REQUIRE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kVertical));

}
TEST_CASE("Leftdiag", "[Left_down]") {
  // SECTION("Can use sections") {}
  // clang-format off
  Board test;
  InitBoard(test);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer2,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer2,1);
  DropDiskToBoard(test,DiskType::kPlayer1,1);
  DropDiskToBoard(test,DiskType::kPlayer1,1);
  DropDiskToBoard(test,DiskType::kPlayer1,2);
  DropDiskToBoard(test,DiskType::kPlayer1,2);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  REQUIRE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kLeftDiag));

}
TEST_CASE("Rightdiag1", "[Right_up]") {
  // SECTION("Can use sections") {}
  // clang-format off
  Board test;
  InitBoard(test);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer2,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer2,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer1,5);
  DropDiskToBoard(test,DiskType::kPlayer2,5);
  DropDiskToBoard(test,DiskType::kPlayer1,5);
  DropDiskToBoard(test,DiskType::kPlayer2,5);
  DropDiskToBoard(test,DiskType::kPlayer1,5);
  DropDiskToBoard(test,DiskType::kPlayer1,4);
  DropDiskToBoard(test,DiskType::kPlayer1,4);
  DropDiskToBoard(test,DiskType::kPlayer2,4);
  DropDiskToBoard(test,DiskType::kPlayer1,4);
  DropDiskToBoard(test,DiskType::kPlayer2,3);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  REQUIRE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kRightDiag));
}
TEST_CASE("Rightdiag2", "[left_down]") {
  // SECTION("Can use sections") {}
  // clang-format off
  Board test;
  InitBoard(test);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer2,1);
  DropDiskToBoard(test,DiskType::kPlayer1,1);
  DropDiskToBoard(test,DiskType::kPlayer2,2);
  DropDiskToBoard(test,DiskType::kPlayer2,2);
  DropDiskToBoard(test,DiskType::kPlayer1,2);
  DropDiskToBoard(test,DiskType::kPlayer2,3);
  DropDiskToBoard(test,DiskType::kPlayer2,3);
  DropDiskToBoard(test,DiskType::kPlayer2,3);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  REQUIRE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kRightDiag));
}
TEST_CASE("Rightdiag3", "[Right_down]") {
  // SECTION("Can use sections") {}
  // clang-format off
  Board test;
  InitBoard(test);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  DropDiskToBoard(test,DiskType::kPlayer2,4);
  DropDiskToBoard(test,DiskType::kPlayer1,4);
  DropDiskToBoard(test,DiskType::kPlayer2,5);
  DropDiskToBoard(test,DiskType::kPlayer2,5);
  DropDiskToBoard(test,DiskType::kPlayer1,5);
  DropDiskToBoard(test,DiskType::kPlayer2,6);
  DropDiskToBoard(test,DiskType::kPlayer2,6);
  DropDiskToBoard(test,DiskType::kPlayer2,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  REQUIRE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kRightDiag));
}
TEST_CASE("Rightdiag4", "[Left_up]") {
  // SECTION("Can use sections") {}
  // clang-format off
  Board test;
  InitBoard(test);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  DropDiskToBoard(test,DiskType::kPlayer2,3);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  DropDiskToBoard(test,DiskType::kPlayer2,3);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  DropDiskToBoard(test,DiskType::kPlayer1,2);
  DropDiskToBoard(test,DiskType::kPlayer2,2);
  DropDiskToBoard(test,DiskType::kPlayer1,2);
  DropDiskToBoard(test,DiskType::kPlayer2,2);
  DropDiskToBoard(test,DiskType::kPlayer1,2);
  DropDiskToBoard(test,DiskType::kPlayer1,1);
  DropDiskToBoard(test,DiskType::kPlayer1,1);
  DropDiskToBoard(test,DiskType::kPlayer2,1);
  DropDiskToBoard(test,DiskType::kPlayer1,1);
  DropDiskToBoard(test,DiskType::kPlayer2,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  REQUIRE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kRightDiag));
}
TEST_CASE("full", "[full]") {
  // SECTION("Can use sections") {}
  // clang-format off
  Board test;
  InitBoard(test);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  REQUIRE_THROWS_AS(DropDiskToBoard(test,DiskType::kPlayer1,6),std::runtime_error);
}
TEST_CASE("outoflowerbound","[bound]") {
  Board test;
  InitBoard(test);
  REQUIRE_THROWS_AS(DropDiskToBoard(test,DiskType::kPlayer1,-1),std::runtime_error);
}
TEST_CASE("outofupperbound","[bound]") {
  Board test;
  InitBoard(test);
  REQUIRE_THROWS_AS(DropDiskToBoard(test,DiskType::kPlayer1,8),std::runtime_error);
}
TEST_CASE("equal", "[equal]") {
  // SECTION("Can use sections") {}
  // clang-format off
  Board test;
  InitBoard(test);
  DropDiskToBoard(test,DiskType::kPlayer2,6);
  DropDiskToBoard(test,DiskType::kPlayer2,6);
  DropDiskToBoard(test,DiskType::kPlayer2,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer1,6);
  DropDiskToBoard(test,DiskType::kPlayer2,4);
  DropDiskToBoard(test,DiskType::kPlayer2,4);
  DropDiskToBoard(test,DiskType::kPlayer2,4);
  DropDiskToBoard(test,DiskType::kPlayer1,4);
  DropDiskToBoard(test,DiskType::kPlayer1,4);
  DropDiskToBoard(test,DiskType::kPlayer1,4);
  DropDiskToBoard(test,DiskType::kPlayer2,2);
  DropDiskToBoard(test,DiskType::kPlayer2,2);
  DropDiskToBoard(test,DiskType::kPlayer2,2);
  DropDiskToBoard(test,DiskType::kPlayer1,2);
  DropDiskToBoard(test,DiskType::kPlayer1,2);
  DropDiskToBoard(test,DiskType::kPlayer1,2);
  DropDiskToBoard(test,DiskType::kPlayer2,0);
  DropDiskToBoard(test,DiskType::kPlayer2,0);
  DropDiskToBoard(test,DiskType::kPlayer2,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer1,0);
  DropDiskToBoard(test,DiskType::kPlayer1,1);
  DropDiskToBoard(test,DiskType::kPlayer1,1);
  DropDiskToBoard(test,DiskType::kPlayer1,1);
  DropDiskToBoard(test,DiskType::kPlayer2,1);
  DropDiskToBoard(test,DiskType::kPlayer2,1);
  DropDiskToBoard(test,DiskType::kPlayer2,1);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  DropDiskToBoard(test,DiskType::kPlayer1,3);
  DropDiskToBoard(test,DiskType::kPlayer2,3);
  DropDiskToBoard(test,DiskType::kPlayer2,3);
  DropDiskToBoard(test,DiskType::kPlayer2,3);
  DropDiskToBoard(test,DiskType::kPlayer1,5);
  DropDiskToBoard(test,DiskType::kPlayer1,5);
  DropDiskToBoard(test,DiskType::kPlayer1,5);
  DropDiskToBoard(test,DiskType::kPlayer2,5);
  DropDiskToBoard(test,DiskType::kPlayer2,5);
  DropDiskToBoard(test,DiskType::kPlayer2,5);
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kRightDiag));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kLeftDiag));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kHorizontal));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer2,WinningDirection::kVertical));
  REQUIRE_FALSE(SearchForWinner(test,DiskType::kPlayer1,WinningDirection::kVertical));
  
}

/////////////////////////////////////////////////////////////////////////////////////////////