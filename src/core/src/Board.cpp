#include "Board.h"
#include <vector>
Board::Board() {
  reset();
}
void Board::reset() {
  grid.assign(3, std::vector<char>(3, ' '));
}
bool Board::isCellEmpty(int row, int col) const {
  return grid[row][col] == ' ';
}
void Board::placeMark(int row, int col, char symbol) {
  if (row >= 0 && row < 3 && col >= 0 && col < 3 && isCellEmpty(row, col)) {
    grid[row][col] = symbol;
  }
}
char Board::getCell(int row, int col) const {
  return grid[row][col];
}
bool Board::isFull() const {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (grid[i][j] == ' ') {
        return false;
      }
    }
  }
  return true;
}