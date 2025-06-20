#include "ReplayWindow.h"
#include "ui_replaywindow.h"
#include <QPushButton>
#include <QTimer>

ReplayWindow::ReplayWindow(const QString& movesString, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReplayWindow),
    currentMoveIndex_(-1)
{
    ui->setupUi(this);
    setupBoard();
    parseMoves(movesString);
    
    autoReplayTimer_ = new QTimer(this);
    autoReplayTimer_->setInterval(800);

    connect(ui->nextButton, &QPushButton::clicked, this, &ReplayWindow::nextMove);
    connect(ui->prevButton, &QPushButton::clicked, this, &ReplayWindow::prevMove);
    connect(ui->autoButton, &QPushButton::clicked, this, &ReplayWindow::toggleAutoReplay);
    connect(autoReplayTimer_, &QTimer::timeout, this, &ReplayWindow::nextMove);

    updateBoardDisplay();
    updateStatus();
}

ReplayWindow::~ReplayWindow()
{
    delete ui;
}

void ReplayWindow::parseMoves(const QString& movesString) {
    if (movesString.isEmpty()) return;
    QStringList moveList = movesString.split(',');
    for (const QString& move : moveList) {
        if (!move.isEmpty()) {
            parsedMoves_.push_back(move.toInt());
        }
    }
}

void ReplayWindow::setupBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton* button = new QPushButton(this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setProperty("isGameBoard", true);
            button->setEnabled(false);
            ui->gridLayout->addWidget(button, i, j);
            boardButtons_.push_back(button);
        }
    }
}

void ReplayWindow::nextMove() {
    if (currentMoveIndex_ < (int)parsedMoves_.size() - 1) {
        currentMoveIndex_++;
        updateBoardDisplay();
    } else {
        if (autoReplayTimer_->isActive()) {
            toggleAutoReplay();
        }
    }
}

void ReplayWindow::prevMove() {
    if (autoReplayTimer_->isActive()) {
        toggleAutoReplay();
    }
    if (currentMoveIndex_ >= 0) {
        currentMoveIndex_--;
        updateBoardDisplay();
    }
}

void ReplayWindow::toggleAutoReplay() {
    if (autoReplayTimer_->isActive()) {
        autoReplayTimer_->stop();
        ui->autoButton->setText("Auto Replay");
    } else {
        if (currentMoveIndex_ >= (int)parsedMoves_.size() - 1) {
            currentMoveIndex_ = -1;
            updateBoardDisplay();
        }
        autoReplayTimer_->start();
        ui->autoButton->setText("Pause");
    }
}

void ReplayWindow::updateBoardDisplay() {
    board_.reset();
    for (int i = 0; i <= currentMoveIndex_; ++i) {
        int moveIndex = parsedMoves_[i];
        int row = moveIndex / 3;
        int col = moveIndex % 3;
        char symbol = (i % 2 == 0) ? 'X' : 'O';
        board_.placeMark(row, col, symbol);
    }

    for (int i = 0; i < 9; ++i) {
        int row = i / 3;
        int col = i % 3;
        boardButtons_[i]->setText(QChar(board_.getCell(row, col)));
    }
    updateStatus();
}

void ReplayWindow::updateStatus() {
    ui->statusLabel->setText(QString("Replay: Move %1 / %2")
                                .arg(currentMoveIndex_ + 1)
                                .arg(parsedMoves_.size()));
    ui->prevButton->setEnabled(currentMoveIndex_ >= 0);
    ui->nextButton->setEnabled(currentMoveIndex_ < (int)parsedMoves_.size() - 1);
}