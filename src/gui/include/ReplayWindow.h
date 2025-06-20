#ifndef REPLAYWINDOW_H
#define REPLAYWINDOW_H

#include <QDialog>
#include <vector>
#include "Board.h"

class QPushButton;
class QTimer;

namespace Ui {
class ReplayWindow;
}

class ReplayWindow : public QDialog {
    Q_OBJECT

public:
    explicit ReplayWindow(const QString& movesString, QWidget *parent = nullptr);
    ~ReplayWindow();

private slots:
    void nextMove();
    void prevMove();
    void toggleAutoReplay();

private:
    void setupBoard();
    void updateBoardDisplay();
    void updateStatus();
    void parseMoves(const QString& movesString);

    Ui::ReplayWindow *ui;
    Board board_;
    std::vector<QPushButton*> boardButtons_;
    std::vector<int> parsedMoves_;
    int currentMoveIndex_;
    QTimer* autoReplayTimer_;
};

#endif