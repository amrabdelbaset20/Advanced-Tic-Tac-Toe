#include "User.h"
User::User() : id_(-1) {}
User::User(int id, const QString& username) : id_(id), username_(username) {}
int User::getId() const { return id_; }
const QString& User::getUsername() const { return username_; }
bool User::isValid() const { return id_ != -1; }