#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "User.h"
class GameWindow;
class QPushButton;
class QWidget;
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onViewHistoryClicked();
private:
    void showLoginDialog();
    void setupUI();
    User currentUser_;
    GameWindow* gameWindow_;
    QPushButton* historyButton_;
    QWidget* centralContainer_;
};
#endif // MAINWINDOW_H