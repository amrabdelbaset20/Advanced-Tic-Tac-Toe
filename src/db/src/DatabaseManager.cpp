/*
================================================================================
 FILE: src/db/src/DatabaseManager.cpp (Corrected Version)
================================================================================
*/
#include "DatabaseManager.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>

DatabaseManager& DatabaseManager::getInstance() {
  static DatabaseManager instance;
  return instance;
}

DatabaseManager::DatabaseManager() {
    db_ = QSqlDatabase::addDatabase("QSQLITE");
}

DatabaseManager::~DatabaseManager() {
    if (db_.isOpen()) {
        db_.close();
    }
}

bool DatabaseManager::openDatabase(const QString& path) {
    db_.setDatabaseName(path);
    if (!db_.open()) {
        qDebug() << "Error: connection with database failed:" << db_.lastError();
        return false;
    }
    qDebug() << "Database: connection ok";
    return initDb();
}

bool DatabaseManager::initDb() {
    QSqlQuery query;
    bool success = query.exec("CREATE TABLE IF NOT EXISTS users ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "username TEXT UNIQUE NOT NULL, "
                            "password_hash TEXT NOT NULL);");
    if (!success) {
        qDebug() << "Failed to create users table:" << query.lastError();
        return false;
    }
    
    success = query.exec("CREATE TABLE IF NOT EXISTS games ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "user_id INTEGER NOT NULL, "
                         "opponent_type TEXT NOT NULL, "
                         "winner TEXT NOT NULL, "
                         "moves TEXT NOT NULL, "
                         "game_date DATETIME NOT NULL, "
                         "FOREIGN KEY(user_id) REFERENCES users(id));");

    if (!success) {
        qDebug() << "Failed to create games table:" << query.lastError();
    }
    return success;
}

QString DatabaseManager::hashPassword(const QString& password) {
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

std::optional<User> DatabaseManager::validateUser(const QString& username, const QString& password) {
    QSqlQuery query;
    // Using positional placeholders (?) for robustness
    query.prepare("SELECT id, username FROM users WHERE username = ? AND password_hash = ?");
    query.addBindValue(username);
    query.addBindValue(hashPassword(password));

    if (query.exec() && query.next()) {
        return User(query.value(0).toInt(), query.value(1).toString());
    }
    return std::nullopt;
}

bool DatabaseManager::addUser(const QString& username, const QString& password) {
    if (username.isEmpty() || password.isEmpty()) return false;

    QSqlQuery query;
    // Using positional placeholders (?) for robustness
    query.prepare("INSERT INTO users (username, password_hash) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(hashPassword(password));

    if (!query.exec()) {
        qDebug() << "Failed to add user:" << query.lastError();
        return false;
    }
    return true;
}

bool DatabaseManager::saveGame(int userId, const QString& opponentType, const QString& winner, const std::vector<int>& moves) {
    QString movesString;
    for (size_t i = 0; i < moves.size(); ++i) {
        movesString += QString::number(moves[i]);
        if (i < moves.size() - 1) {
            movesString += ",";
        }
    }

    QSqlQuery query;
    // THIS IS THE MAIN FIX: Using positional placeholders (?) instead of named placeholders.
    // This resolves the mismatch error definitively.
    query.prepare("INSERT INTO games (user_id, opponent_type, winner, moves, game_date) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(userId);
    query.addBindValue(opponentType);
    query.addBindValue(winner);
    query.addBindValue(movesString);
    query.addBindValue(QDateTime::currentDateTime());

    if (!query.exec()) {
        qDebug() << "Failed to save game:" << query.lastError();
        return false;
    }
    return true;
}

std::vector<GameRecord> DatabaseManager::getGameHistory(int userId) {
    std::vector<GameRecord> history;
    QSqlQuery query;
    // Using positional placeholders (?) for robustness
    query.prepare("SELECT id, opponent_type, winner, moves, game_date FROM games "
                  "WHERE user_id = ? ORDER BY game_date DESC");
    query.addBindValue(userId);

    if (query.exec()) {
        while (query.next()) {
            GameRecord record;
            record.gameId = query.value(0).toInt();
            record.opponent = query.value(1).toString();
            record.winner = query.value(2).toString();
            record.moves = query.value(3).toString();
            record.date = query.value(4).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            history.push_back(record);
        }
    } else {
        qDebug() << "Failed to retrieve game history:" << query.lastError();
    }
    return history;
}