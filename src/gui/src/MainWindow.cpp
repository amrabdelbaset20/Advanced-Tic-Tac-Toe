#include "MainWindow.h"
#include "LoginDialog.h"
#include "GameWindow.h"
#include "HistoryDialog.h"
#include <QApplication>
#include <QTimer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), gameWindow_(nullptr), historyButton_(nullptr), centralContainer_(nullptr) {
    QTimer::singleShot(0, this, &MainWindow::showLoginDialog);
}
MainWindow::~MainWindow() {}
void MainWindow::showLoginDialog() {
    LoginDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        currentUser_ = dialog.getCurrentUser();
        setupUI();
        this->show();
    } else {
        QApplication::quit();
    }
}
void MainWindow::setupUI() {
    setWindowTitle(QString("Advanced Tic Tac Toe - Welcome, %1!").arg(currentUser_.getUsername()));
    resize(450, 550);
    centralContainer_ = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralContainer_);
    gameWindow_ = new GameWindow(currentUser_, this);
    historyButton_ = new QPushButton("View Game History", this);
    layout->addWidget(gameWindow_);
    layout->addWidget(historyButton_);
    setCentralWidget(centralContainer_);
    connect(historyButton_, &QPushButton::clicked, this, &MainWindow::onViewHistoryClicked);
}
void MainWindow::onViewHistoryClicked() {
    HistoryDialog dialog(currentUser_, this);
    dialog.exec();
}