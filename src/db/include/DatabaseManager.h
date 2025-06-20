#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>
#include <QString>
#include <optional>
#include <vector>
#include "User.h"
#include "GameRecord.h"

class DatabaseManager {
 public:
  static DatabaseManager& getInstance();
  bool openDatabase(const QString& path);
  std::optional<User> validateUser(const QString& username, const QString& password);
  bool addUser(const QString& username, const QString& password);
  bool saveGame(int userId, const QString& opponentType, const QString& winner, const std::vector<int>& moves);
  std::vector<GameRecord> getGameHistory(int userId);

 private:
  DatabaseManager();
  ~DatabaseManager();
  DatabaseManager(const DatabaseManager&) = delete;
  DatabaseManager& operator=(const DatabaseManager&) = delete;
  bool initDb();
  QString hashPassword(const QString& password);
  QSqlDatabase db_;
};

#endif 