#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include "Game.h"
#include "AI.h"
#include "User.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget {
  Q_OBJECT

 public:
  explicit GameWindow(const User& user, QWidget* parent = nullptr); 
  ~GameWindow();

 private slots:
  void handleCellClick(int index);
  void startPvpGame();
  void startPveGameEasy();
  void startPveGameMedium();
  void startPveGameHard();

 private:
  enum class GameMode { None, PvP, PvE };
  
  void setupBoard();
  void setupControls(); // New function to create game mode buttons
  void updateBoard();
  void processPlayerMove(int row, int col);
  void processAiMove();
  void endGame(const QString& message);
  void startNewGame(GameMode mode);

  Ui::GameWindow* ui;
  Game game_;
  AI ai_;
  AIDifficulty currentDifficulty_; // Store current AI difficulty
  User currentUser_;
  GameMode gameMode_;
  std::vector<QPushButton*> boardButtons_;
  bool isGameOver_;
};

#endif  // GAMEWINDOW_H