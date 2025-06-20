#include "LoginDialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::LoginDialog), dbManager_(DatabaseManager::getInstance()) {
  ui->setupUi(this);
}
LoginDialog::~LoginDialog() {
  delete ui;
}
User LoginDialog::getCurrentUser() const {
    return currentUser_.value_or(User());
}
void LoginDialog::on_loginButton_clicked() {
  const QString username = ui->usernameLineEdit->text();
  const QString password = ui->passwordLineEdit->text();
  currentUser_ = dbManager_.validateUser(username, password);
  if (currentUser_ && currentUser_->isValid()) {
    accept();
  } else {
    ui->statusLabel->setText("Invalid username or password.");
    QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
  }
}
void LoginDialog::on_registerButton_clicked() {
  const QString username = ui->usernameLineEdit->text();
  const QString password = ui->passwordLineEdit->text();
  if (username.isEmpty() || password.length() < 4) {
      QMessageBox::warning(this, "Registration Failed", "Username cannot be empty and password must be at least 4 characters.");
      return;
  }
  if (dbManager_.addUser(username, password)) {
    QMessageBox::information(this, "Success", "Registration successful! You can now log in.");
    ui->statusLabel->setText("Registration successful! Please log in.");
  } else {
    QMessageBox::warning(this, "Registration Failed", "Username may already be taken.");
    ui->statusLabel->setText("Registration failed. Username may exist.");
  }
}