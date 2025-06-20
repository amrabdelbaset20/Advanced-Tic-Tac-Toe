#include "Player.h"
Player::Player(char symbol) : symbol_(symbol) {}
char Player::getSymbol() const {
  return symbol_;
}