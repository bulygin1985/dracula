#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QVector>

#include "dracula.h"
#include "lord.h"
#include "doctor.h"
#include "helsing.h"
#include "mina.h"

class GameState
{
public:
    GameState();
    ~GameState();
    Dracula* getDracula() const;
    Hunter* getHunter(int num) const;
    Player * getPlayer(int num) const;
    Player* getWhoMoves();
    int getWhoMovesNum() const;

    int getDayNightPosition() const;

    void setDayNightPosition(int value);
    void incrementDayNightPosition();
    Track getTrack() const;
    void copy(GameState * state);

    void setWhoMoves(int value);
    QSet<int> getSaintPlaces() const;
    QSet<int> getHunterBlockedLocation(uint playerNum) const;


private:
    int dayNightPosition;            //from 0 to 5
    QVector<Player*> players;
    int whoMoves;                     // 0 - dracula, 1 - lord, 2 - doctor, 3- helsing, 4 - mina
    uint hunterScore;
    uint draculaScore;
};

#endif // GAMESTATE_H
