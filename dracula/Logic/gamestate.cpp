#include <assert.h>

#include "gamestate.h"
#include "constants.h"
#include "QsLog.h"


GameState::GameState()
{
    QLOG_DEBUG() << "GameState constructor";
    players.resize(PLAYER_AMOUNT);
    players[DRACULA_NUM] = new Dracula;
    players[LORD_NUM] = new Lord;
    players[DOCTOR_NUM] = new Doctor;
    players[HELSING_NUM] = new Helsing;
    players[MINA_NUM] = new Mina;

    whoMoves = 1;
    dayNightPosition = 0;
    hunterScore = 0;
    draculaScore = 0;
}

Player *GameState::getWhoMoves()
{
    return players[whoMoves];
}

Dracula *GameState::getDracula() const
{
    QLOG_DEBUG() << "GameState::getDracula";
    return dynamic_cast<Dracula*>(players[DRACULA_NUM]);
}

Player *GameState::getPlayer(int num) const
{
    assert(num >= DRACULA_NUM && num <= MINA_NUM);
    return players[num];
}


Hunter *GameState::getHunter(int num) const
{
    QLOG_DEBUG() << "GameState::getHunter";
    assert(num >= LORD_NUM && num <= MINA_NUM);
    return dynamic_cast<Hunter*>(players[num]);
}

