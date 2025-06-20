#ifndef PLAYER_H
#define PLAYER_H
class Player {
 public:
  explicit Player(char symbol);
  char getSymbol() const;
 private:
  char symbol_;
};
#endif  // PLAYER_H