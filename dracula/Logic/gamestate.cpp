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
    QLOG_DEBUG() << "GameState::getWhoMoves";
    return players[whoMoves];
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

void GameState::incrementDayNightPosition()
{
    dayNightPosition++;
    if (dayNightPosition > DAY_LENTH)
    {
        draculaScore++;
        hunterScore++;
    }
    dayNightPosition %= DAY_LENTH;
}

Track GameState::getTrack() const
{
    QLOG_DEBUG() << "GameState::getTrack()";
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
void GameState::setWhoMoves(int value)
{
    whoMoves = value;
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

QSet<int> GameState::getSaintPlaces() const
{
    QSet<int> saintPlaces;
    saintPlaces << 60;
    return saintPlaces;
}

QSet<int> GameState::getHunterBlockedLocation(uint playerNum) const
{
    assert(playerNum >= LORD_NUM && playerNum <= MINA_NUM);
    QSet<int> blocked;
    return blocked;
}

int GameState::getDraculaScore() const
{
    return draculaScore;
}

int GameState::getHunterScore() const
{
    return hunterScore;
}

GameState::~GameState()
{
    for (int i = 0; i < players.size(); i++)
    {
        delete players[i];
    }
}

