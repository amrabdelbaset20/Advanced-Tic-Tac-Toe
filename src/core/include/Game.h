#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <vector>

enum class GameState { InProgress, Won, Draw };

class Game {
 public:
  Game();
  
  bool makeMove(int row, int col);
  GameState checkGameState();
  char getCurrentPlayerSymbol() const;
  const Board& getBoard() const;
  void resetGame();

  const std::vector<int>& getMoves() const;

 private:
  void switchPlayer();

  Board board_;
  Player playerX_;
  Player playerO_;
  Player* currentPlayer_;
  GameState gameState_;
  
  std::vector<int> moves_; 
};

#endif 