#ifndef USER_H
#define USER_H
#include <QString>
class User {
 public:
  User();
  User(int id, const QString& username);
  int getId() const;
  const QString& getUsername() const;
  bool isValid() const;
 private:
  int id_;
  QString username_;
};
#endif  // USER_H