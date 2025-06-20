#ifndef BOARD_H
#define BOARD_H
#include <vector>
class Board {
 public:
  Board();
  bool isCellEmpty(int row, int col) const;
  void placeMark(int row, int col, char symbol);
  char getCell(int row, int col) const;
  bool isFull() const;
  void reset();
  std::vector<std::vector<char>> grid;
};
#endif  // BOARD_H