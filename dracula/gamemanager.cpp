#include "gamemanager.h"
#include "gamestate.h"
#include "QsLog.h"
#include "constants.h"
#include "loader.h"

#include <assert.h>

GameManager::GameManager()
{
    prevGameState = new GameState();
    gameState = new GameState();
    guimanager = new Guimanager(gameState, prevGameState);
    connect(guimanager, SIGNAL(action(Action)), this, SLOT(processAction(Action)));
}

Guimanager *GameManager::getGuimanager() const
{
    return guimanager;
}

bool GameManager::processAction(const Action& action)
{
    prevGameState->copy(gameState);
    //if ("location" == action.kind)
    {
        assert(action.number >= 0 && action.number <= 70);
        gameState->getWhoMoves()->setLocationNum(action.number);
        gameState->startNextTurn();
    }
    QLOG_ERROR() << "prevGameState track size  = " << prevGameState->getTrack().getElements().size();
    QLOG_ERROR() << "gameState track size  = " << gameState->getTrack().getElements().size();
    for (int i = DRACULA_NUM ; i <= MINA_NUM; i++ )
    {
        if (i != gameState->getWhoMovesNum()) gameState->getPlayer(i)->setPossibleLocations(QList<int>());
        else{
            int locNum = gameState->getPlayer(i)->getLocationNum();
            if (locNum != -1)
            {
            QLOG_ERROR() << "gameState->getWhoMovesNum() = " << gameState->getWhoMovesNum();
            QLOG_ERROR() << "gameState->getPlayer(i)->getLocationNum() = " << locNum;
            QVector<int> possibleLocationsVector = Loader::get().roadSeasGraph[locNum];
            QLOG_ERROR() << "possibleLocationsVector.length() = " << possibleLocationsVector.length();
            QLOG_ERROR() << "possibleLocationsVector = " << possibleLocationsVector;
            QLOG_ERROR() << "possibleLocationsList = " << possibleLocationsVector.toList();
            gameState->getPlayer(i)->setPossibleLocations(possibleLocationsVector.toList());
            }
        }
    }

//    int locNum = gameState->getWhoMoves()->getLocationNum();
//    if (locNum != -1)
//    {
//        QVector<int> possibleLocationsVector = Loader::get().roadSeasGraph[locNum];

//        gameState->getWhoMoves()->setPossibleLocations(possibleLocationsVector.toList());
//    }
//    QLOG_ERROR() << "GameManager getPossibleLocations = " <<  gameState->getWhoMoves()->getPossibleLocations();

    guimanager->paint(gameState, prevGameState);

}
GameState *GameManager::getPrevGameState() const
{
    return prevGameState;
}

GameState* GameManager::getGameState()
{
    return gameState;
}

