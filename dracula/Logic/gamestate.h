#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "dracula.h"
#include "lord.h"
#include "doctor.h"
#include "helsing.h"
#include "mina.h"

class GameState
{
public:
    GameState();
    Dracula* getDracula() const;
    Hunter* getHunter(int num) const;
    Player * getPlayer(int num) const;
    Player* getWhoMoves();
    void startNextTurn();
    int getWhoMovesNum() const;

private:
    std::vector<Player*> players;
    int whoMoves;                     // 0 - dracula, 1 - lord, 2 - doctor, 3- helsing, 4 - mina
    uint dayNightPosition;           //from 0 to 5
    uint hunterScore;
    uint draculaScore;
};

#endif // GAMESTATE_H
