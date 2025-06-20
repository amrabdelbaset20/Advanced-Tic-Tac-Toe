// FILE: tests/ai/test_ai_logic.cpp (Corrected)

#include "gtest/gtest.h"
#include "AI.h"
#include "Board.h"

TEST(AITest, BlocksWinningMove) {
  Board b;
  AI ai;
  // Setup board where player 'X' is about to win
  b.placeMark(0, 0, 'X');
  b.placeMark(0, 1, 'X');
  b.placeMark(1, 0, 'O');

  // AI ('O') should block at (0, 2) when playing on Hard
  // CORRECTED: Pass the difficulty level to the function
  Move bestMove = ai.findBestMove(b, AIDifficulty::Hard);
  EXPECT_EQ(bestMove.row, 0);
  EXPECT_EQ(bestMove.col, 2);
}

TEST(AITest, MakesWinningMove) {
  Board b;
  AI ai;
  // Setup board where AI 'O' can win
  b.placeMark(0, 0, 'O');
  b.placeMark(0, 1, 'O');
  b.placeMark(1, 0, 'X');
  b.placeMark(2, 0, 'X');

  // AI ('O') should win at (0, 2) when playing on Hard
  // CORRECTED: Pass the difficulty level to the function
  Move bestMove = ai.findBestMove(b, AIDifficulty::Hard);
  EXPECT_EQ(bestMove.row, 0);
  EXPECT_EQ(bestMove.col, 2);
}