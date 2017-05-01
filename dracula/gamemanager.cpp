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
    {
        assert(action.number >= 0 && action.number <= 70);
        gameState->getWhoMoves()->setLocationNum(action.number);
        gameState->startNextTurn();
    }
    for (int i = DRACULA_NUM ; i <= MINA_NUM; i++ )
    {
        gameState->getPlayer(i)->resetPossibleAction();
    }
    int locNum = gameState->getWhoMoves()->getLocationNum();
    if (locNum != -1)
    {
        QVector<int> possibleLocationsVector = Loader::get().roadSeasGraph[locNum];
        gameState->getWhoMoves()->setPossibleLocations(possibleLocationsVector.toList());
    }

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

