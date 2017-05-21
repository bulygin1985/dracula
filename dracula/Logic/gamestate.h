#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QVector>

#include "dracula.h"
#include "lord.h"
#include "doctor.h"
#include "helsing.h"
#include "mina.h"

enum class WhoWin
{
    NONE = 0,
    HUNTER = 1,
    DRACULA = 2
};

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

    int getDraculaScore() const;

    int getHunterScore() const;
    bool isAIturn();

    void changeHunterScore(int delta);
    void changeDraculaScore(int delta);


    WhoWin whoWin;
private:
    int dayNightPosition;            //from 0 to 5
    QVector<Player*> players;
    int whoMoves;                     // 0 - dracula, 1 - lord, 2 - doctor, 3- helsing, 4 - mina
    int hunterScore;
    int draculaScore;
};

#endif // GAMESTATE_H
