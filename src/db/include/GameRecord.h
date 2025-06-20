#ifndef GAMERECORD_H
#define GAMERECORD_H

#include <QString>

struct GameRecord {
    int gameId;
    QString opponent;
    QString winner;
    QString date;
    QString moves;
};

#endif // GAMERECORD_H