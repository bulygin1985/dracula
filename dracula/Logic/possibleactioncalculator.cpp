#include <QsLog.h>
#include "possibleactioncalculator.h"
#include "movementcalculator.h"
#include "gamestate.h"
#include "constants.h"

PossibleActionCalculator::PossibleActionCalculator(GameState * gameState, GameState * prevGameState):
    gameState(gameState), prevGameState(prevGameState)
{
    QLOG_DEBUG() << "PossibleActionCalculator constructor";
}

void PossibleActionCalculator::calcPossibleMovements()
{
    QLOG_DEBUG() << "PossibleActionCalculator::calcPossibleMovements()";
    for (int i = DRACULA_NUM ; i <= MINA_NUM; i++ )
    {
        gameState->getPlayer(i)->resetPossibleAction();
    }
    Player * player = gameState->getWhoMoves();
    int whoMoves = gameState->getWhoMovesNum();
    int locNum = player->getLocationNum();
    if (-1 == locNum) //first turn
    {
        if (DRACULA_NUM == gameState->getWhoMovesNum())
        {
            QSet<uint> hunterLocations;
            for (int i = LORD_NUM; i <= MINA_NUM; i++)
               hunterLocations << gameState->getPlayer(i)->getLocationNum();
            for (int i = 0; i < HOSPITAL_NUM; i++)
                if ( (i != DRACULA_CASTLE_NUM) && (!hunterLocations.contains(i)) ) player->addPossibleLocation(i);
        }
        else
        {
            for (int i = 0; i < HOSPITAL_NUM; i++)
                if (i != DRACULA_CASTLE_NUM) player->addPossibleLocation(i);
        }
    }
    else
    {
        QSet<int> forbittenPlaces = (whoMoves == DRACULA_NUM) ?
                    gameState->getSaintPlaces() : gameState->getHunterBlockedLocation(whoMoves);
        int prevLoc = prevGameState->getPlayer(whoMoves)->getLocationNum();
        player->calcPossibleMovements(forbittenPlaces, prevLoc);
//        QLOG_ERROR() << "possibleLocationsVector = " << possibleLocationsVector;
    }
}

void PossibleActionCalculator::calc()
{
    QLOG_DEBUG() << "PossibleActionCalculator::calc()";
    calcPossibleMovements();
}

bool PossibleActionCalculator::isActionPossible(const Action &action, QString &message)
{
    QLOG_DEBUG() << "PossibleActionCalculator::isActionPossible()";
    const QList<int> & possibleLocations = gameState->getWhoMoves()->getPossibleLocations();
    bool isLocationPossible = possibleLocations.contains(action.number);
    if (!isLocationPossible)
    {
        message = "Wrong Location";
    }
    return isLocationPossible;
}

