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

void GameState::startNextTurn()
{
    QLOG_DEBUG() << "GameState::startNextTurn()";
    whoMoves = (whoMoves + 1) % PLAYER_AMOUNT;
    int num =  players[DRACULA_NUM]->getLocationNum();
    QLOG_ERROR() << "num = " << num;
    if ((DRACULA_NUM == whoMoves) &&
            (num <= 60)     //time stops on sea
            && (num != -1)) //it is notfirst round
    {
        QLOG_ERROR() << "dayNightPosition = " << dayNightPosition;
        dayNightPosition++;
        dayNightPosition %= DAY_LENTH;
    }
}

int GameState::getWhoMovesNum() const
{
    return whoMoves;
}
int GameState::getDayNightPosition() const
{
    return dayNightPosition;
}
void GameState::setDayNightPosition(int value)
{
    dayNightPosition = value;
}

Track GameState::getTrack() const
{
    return getDracula()->getTrack();
}

void GameState::copy(GameState *state) //TODO clone players
{
    QLOG_DEBUG() << "GameState::copy()";
    dayNightPosition = state->dayNightPosition;
    whoMoves = state->whoMoves;
    hunterScore = state->hunterScore;
    draculaScore = state->draculaScore;
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->copy(state->players[i]);
    }
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

