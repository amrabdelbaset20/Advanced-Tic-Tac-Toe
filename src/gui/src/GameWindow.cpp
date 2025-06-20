#include "GameWindow.h"
#include "ui_gamewindow.h"
#include "DatabaseManager.h"
#include <QSignalMapper>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>

GameWindow::GameWindow(const User& user, QWidget* parent)
    : QWidget(parent), 
      ui(new Ui::GameWindow), 
      currentUser_(user), 
      gameMode_(GameMode::None), 
      isGameOver_(true) 
{
    ui->setupUi(this);
    setupBoard();
    setupControls();
}

GameWindow::~GameWindow() {
    delete ui;
}

void GameWindow::setupControls() {
    delete ui->pvpButton;
    delete ui->pveButton;

    QGroupBox* pvpGroup = new QGroupBox("Two Player", this);
    QHBoxLayout* pvpLayout = new QHBoxLayout();
    QPushButton* pvpButton = new QPushButton("New Game", this);
    connect(pvpButton, &QPushButton::clicked, this, &GameWindow::startPvpGame);
    pvpLayout->addWidget(pvpButton);
    pvpGroup->setLayout(pvpLayout);

    QGroupBox* pveGroup = new QGroupBox("Player vs. AI", this);
    QHBoxLayout* pveLayout = new QHBoxLayout();
    QPushButton* easyButton = new QPushButton("Easy", this);
    QPushButton* mediumButton = new QPushButton("Medium", this);
    QPushButton* hardButton = new QPushButton("Hard", this);
    connect(easyButton, &QPushButton::clicked, this, &GameWindow::startPveGameEasy);
    connect(mediumButton, &QPushButton::clicked, this, &GameWindow::startPveGameMedium);
    connect(hardButton, &QPushButton::clicked, this, &GameWindow::startPveGameHard);
    pveLayout->addWidget(easyButton);
    pveLayout->addWidget(mediumButton);
    pveLayout->addWidget(hardButton);
    pveGroup->setLayout(pveLayout);

    ui->verticalLayout->addWidget(pvpGroup);
    ui->verticalLayout->addWidget(pveGroup);
}

void GameWindow::startPvpGame() {
    startNewGame(GameMode::PvP);
}

void GameWindow::startPveGameEasy() {
    currentDifficulty_ = AIDifficulty::Easy;
    startNewGame(GameMode::PvE);
}

void GameWindow::startPveGameMedium() {
    currentDifficulty_ = AIDifficulty::Medium;
    startNewGame(GameMode::PvE);
}

void GameWindow::startPveGameHard() {
    currentDifficulty_ = AIDifficulty::Hard;
    startNewGame(GameMode::PvE);
}

void GameWindow::processAiMove() {
    if (isGameOver_) return;
    Move aiMove = ai_.findBestMove(game_.getBoard(), currentDifficulty_);
    if (aiMove.row != -1 && game_.makeMove(aiMove.row, aiMove.col)) {
        updateBoard();
        GameState state = game_.checkGameState();
        if (state == GameState::Won) {
            endGame(QString("Player %1 (AI) Wins!").arg(game_.getCurrentPlayerSymbol()));
        } else if (state == GameState::Draw) {
            endGame("It's a Draw!");
        }
    }
}

void GameWindow::endGame(const QString& message) {
  isGameOver_ = true;
  ui->statusLabel->setText(message);
  if (!currentUser_.isValid()) return;
  
  QString opponentType = "Human";
  if (gameMode_ == GameMode::PvE) {
      switch (currentDifficulty_) {
          case AIDifficulty::Easy: opponentType = "AI (Easy)"; break;
          case AIDifficulty::Medium: opponentType = "AI (Medium)"; break;
          case AIDifficulty::Hard: opponentType = "AI (Hard)"; break;
      }
  }

  QString winner;
  GameState state = game_.checkGameState();
  if (state == GameState::Draw) {
      winner = "Draw";
  } else if (state == GameState::Won) {
      if (game_.getCurrentPlayerSymbol() == 'X') {
          winner = "You";
      } else {
          winner = "Opponent";
      }
  }
  if (!winner.isEmpty()) {
      DatabaseManager::getInstance().saveGame(currentUser_.getId(), opponentType, winner, game_.getMoves());
  }
}

void GameWindow::setupBoard() {
    QSignalMapper* signalMapper = new QSignalMapper(this);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton* button = new QPushButton(this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setProperty("isGameBoard", true);
            ui->gridLayout->addWidget(button, i, j);
            boardButtons_.push_back(button);
            connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(button, boardButtons_.size() - 1);
        }
    }
    connect(signalMapper, SIGNAL(mappedInt(int)), this, SLOT(handleCellClick(int)));
}

void GameWindow::startNewGame(GameMode mode) {
    game_.resetGame();
    gameMode_ = mode;
    isGameOver_ = false;
    updateBoard();
}

void GameWindow::handleCellClick(int index) {
    if (isGameOver_ || gameMode_ == GameMode::None) return;
    int row = index / 3;
    int col = index % 3;
    processPlayerMove(row, col);
}

void GameWindow::processPlayerMove(int row, int col) {
    if (isGameOver_ || !game_.getBoard().isCellEmpty(row, col)) return;
    if (game_.makeMove(row, col)) {
        updateBoard();
        GameState state = game_.checkGameState();
        if (state == GameState::Won) {
            endGame(QString("Player %1 Wins!").arg(game_.getCurrentPlayerSymbol()));
        } else if (state == GameState::Draw) {
            endGame("It's a Draw!");
        } else {
            if (gameMode_ == GameMode::PvE) {
                processAiMove();
            }
        }
    }
}

void GameWindow::updateBoard() {
  const Board& board = game_.getBoard();
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      boardButtons_[i * 3 + j]->setText(QChar(board.getCell(i, j)));
    }
  }
  if (!isGameOver_) {
    ui->statusLabel->setText(QString("Player %1's Turn").arg(game_.getCurrentPlayerSymbol()));
  }
}