// FILE: src/ai/include/AI.h (Corrected)

#ifndef AI_H
#define AI_H

#include "Board.h"
#include <vector>

struct Move {
    int row = -1;
    int col = -1;
};

// CORRECTED: Added a space between "class" and "AIDifficulty"
enum class AIDifficulty { Easy, Medium, Hard };

class AI {
 public:
  Move findBestMove(Board board, AIDifficulty difficulty);

 private:
  int minimax(Board& board, int depth, bool isMaximizing, int alpha, int beta, int maxDepth);
  int evaluate(const Board& board);
  Move findRandomMove(const Board& board);
};

#endif  // AI_H