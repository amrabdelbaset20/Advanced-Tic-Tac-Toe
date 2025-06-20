#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QDialog>
#include "DatabaseManager.h"
#include "User.h"
namespace Ui {
class LoginDialog;
}
class LoginDialog : public QDialog {
  Q_OBJECT
 public:
  explicit LoginDialog(QWidget* parent = nullptr);
  ~LoginDialog();
  User getCurrentUser() const;
 private slots:
  void on_loginButton_clicked();
  void on_registerButton_clicked();
 private:
  Ui::LoginDialog* ui;
  DatabaseManager& dbManager_;
  std::optional<User> currentUser_;
};
#endif  // LOGINDIALOG_H