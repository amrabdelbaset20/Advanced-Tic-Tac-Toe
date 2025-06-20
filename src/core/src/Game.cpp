#include "Game.h"

Game::Game() : playerX_('X'), playerO_('O') {
  resetGame();
}

void Game::resetGame() {
    board_.reset();
    moves_.clear();
    currentPlayer_ = &playerX_;
    gameState_ = GameState::InProgress;
}

bool Game::makeMove(int row, int col) {
  if (gameState_ != GameState::InProgress || !board_.isCellEmpty(row, col)) {
    return false;
  }
  
  moves_.push_back(row * 3 + col);
  
  board_.placeMark(row, col, currentPlayer_->getSymbol());
  gameState_ = checkGameState();
  if (gameState_ == GameState::InProgress) {
    switchPlayer();
  }
  return true;
}

const std::vector<int>& Game::getMoves() const {
    return moves_;
}

GameState Game::checkGameState() {
  char winnerSymbol = ' ';
  for (int i = 0; i < 3; ++i) {
    if (board_.getCell(i, 0) != ' ' && board_.getCell(i, 0) == board_.getCell(i, 1) && board_.getCell(i, 1) == board_.getCell(i, 2)) {
      winnerSymbol = board_.getCell(i, 0);
    }
    if (board_.getCell(0, i) != ' ' && board_.getCell(0, i) == board_.getCell(1, i) && board_.getCell(1, i) == board_.getCell(2, i)) {
      winnerSymbol = board_.getCell(0, i);
    }
  }
  if (board_.getCell(0, 0) != ' ' && board_.getCell(0, 0) == board_.getCell(1, 1) && board_.getCell(1, 1) == board_.getCell(2, 2)) {
    winnerSymbol = board_.getCell(0, 0);
  }
  if (board_.getCell(0, 2) != ' ' && board_.getCell(0, 2) == board_.getCell(1, 1) && board_.getCell(1, 1) == board_.getCell(2, 0)) {
    winnerSymbol = board_.getCell(0, 2);
  }
  if (winnerSymbol != ' ') {
    return GameState::Won;
  }
  if (board_.isFull()) {
    return GameState::Draw;
  }
  return GameState::InProgress;
}

void Game::switchPlayer() {
  currentPlayer_ = (currentPlayer_ == &playerX_) ? &playerO_ : &playerX_;
}

char Game::getCurrentPlayerSymbol() const {
  return currentPlayer_->getSymbol();
}

const Board& Game::getBoard() const {
    return board_;
}