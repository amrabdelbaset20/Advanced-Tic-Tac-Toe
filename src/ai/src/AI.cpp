#include "AI.h"
#include <limits>
#include <algorithm>
#include <vector>
#include <random> // For random moves on Easy

Move AI::findBestMove(Board board, AIDifficulty difficulty) {
    switch (difficulty) {
        case AIDifficulty::Easy:
            return findRandomMove(board);

        case AIDifficulty::Medium:
        case AIDifficulty::Hard: {
            int bestVal = std::numeric_limits<int>::min();
            Move bestMove;
            bestMove.row = -1;
            bestMove.col = -1;
            
            // For Medium difficulty, we limit the search depth.
            // For Hard, we don't (-1 means infinite depth).
            int maxDepth = (difficulty == AIDifficulty::Medium) ? 3 : -1;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board.isCellEmpty(i, j)) {
                        board.placeMark(i, j, 'O');
                        int moveVal = minimax(board, 0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), maxDepth);
                        board.grid[i][j] = ' '; // Undo move

                        if (moveVal > bestVal) {
                            bestMove.row = i;
                            bestMove.col = j;
                            bestVal = moveVal;
                        }
                    }
                }
            }
            return bestMove;
        }
    }
    return {}; // Should not happen
}

// New function for Easy difficulty
Move AI::findRandomMove(const Board& board) {
    std::vector<Move> possibleMoves;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.isCellEmpty(i, j)) {
                possibleMoves.push_back({i, j});
            }
        }
    }

    if (!possibleMoves.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, possibleMoves.size() - 1);
        return possibleMoves[distrib(gen)];
    }
    return {-1, -1}; // No possible moves
}


// Update minimax to respect the maximum depth
int AI::minimax(Board& board, int depth, bool isMaximizing, int alpha, int beta, int maxDepth) {
  int score = evaluate(board);

  if (score == 10) return score - depth;
  if (score == -10) return score + depth;
  if (board.isFull()) return 0;
  
  // New condition: stop searching if we reach the depth limit for Medium
  if (maxDepth != -1 && depth >= maxDepth) return 0;

  if (isMaximizing) {
    int best = std::numeric_limits<int>::min();
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board.isCellEmpty(i, j)) {
          board.placeMark(i, j, 'O');
          best = std::max(best, minimax(board, depth + 1, !isMaximizing, alpha, beta, maxDepth));
          board.grid[i][j] = ' ';
          alpha = std::max(alpha, best);
          if (beta <= alpha) break;
        }
      }
      if (beta <= alpha) break; // Pruning across columns
    }
    return best;
  } else {
    int best = std::numeric_limits<int>::max();
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board.isCellEmpty(i, j)) {
          board.placeMark(i, j, 'X');
          best = std::min(best, minimax(board, depth + 1, !isMaximizing, alpha, beta, maxDepth));
          board.grid[i][j] = ' ';
          beta = std::min(beta, best);
          if (beta <= alpha) break;
        }
      }
      if (beta <= alpha) break; // Pruning across columns
    }
    return best;
  }
}

int AI::evaluate(const Board& board) {
    for (int row = 0; row < 3; row++) {
        if (board.getCell(row, 0) != ' ' && board.getCell(row, 0) == board.getCell(row, 1) && board.getCell(row, 1) == board.getCell(row, 2)) {
            if (board.getCell(row, 0) == 'O') return 10;
            if (board.getCell(row, 0) == 'X') return -10;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board.getCell(0, col) != ' ' && board.getCell(0, col) == board.getCell(1, col) && board.getCell(1, col) == board.getCell(2, col)) {
            if (board.getCell(0, col) == 'O') return 10;
            if (board.getCell(0, col) == 'X') return -10;
        }
    }
    if (board.getCell(0, 0) != ' ' && board.getCell(0, 0) == board.getCell(1, 1) && board.getCell(1, 1) == board.getCell(2, 2)) {
        if (board.getCell(0, 0) == 'O') return 10;
        if (board.getCell(0, 0) == 'X') return -10;
    }
    if (board.getCell(0, 2) != ' ' && board.getCell(0, 2) == board.getCell(1, 1) && board.getCell(1, 1) == board.getCell(2, 0)) {
        if (board.getCell(0, 2) == 'O') return 10;
        if (board.getCell(0, 2) == 'X') return -10;
    }
    return 0;
}