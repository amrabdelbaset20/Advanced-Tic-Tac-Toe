#include "gtest/gtest.h"
#include "Game.h"
#include "Board.h"

TEST(BoardTest, Initialization) {
  Board b;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(b.getCell(i, j), ' ');
      EXPECT_TRUE(b.isCellEmpty(i, j));
    }
  }
}

TEST(BoardTest, PlaceMark) {
  Board b;
  b.placeMark(1, 1, 'X');
  EXPECT_EQ(b.getCell(1, 1), 'X');
  EXPECT_FALSE(b.isCellEmpty(1, 1));
}

TEST(GameTest, WinConditionRow) {
  Game g;
  g.makeMove(0, 0); // X
  g.makeMove(1, 0); // O
  g.makeMove(0, 1); // X
  g.makeMove(1, 1); // O
  g.makeMove(0, 2); // X wins
  EXPECT_EQ(g.checkGameState(), GameState::Won);
  EXPECT_EQ(g.getCurrentPlayerSymbol(), 'X');
}

TEST(GameTest, DrawCondition) {
  Game g;
  g.makeMove(0, 0); // X
  g.makeMove(0, 1); // O
  g.makeMove(0, 2); // X
  g.makeMove(1, 1); // O
  g.makeMove(1, 0); // X
  g.makeMove(1, 2); // O
  g.makeMove(2, 1); // X
  g.makeMove(2, 0); // O
  g.makeMove(2, 2); // X - Draw
  EXPECT_EQ(g.checkGameState(), GameState::Draw);
}