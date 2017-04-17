#include "gamemanager.h"
#include "gamestate.h"
#include "QsLog.h"

#include <assert.h>

GameManager::GameManager()
{
    gameState = new GameState();
    guimanager = new Guimanager(gameState);
    connect(guimanager, SIGNAL(action(Action)), this, SLOT(processAction(Action)));
}

Guimanager *GameManager::getGuimanager() const
{
    return guimanager;
}


bool GameManager::processAction(const Action& action)
{
    //if ("location" == action.kind)
    {
        assert(action.number >= 0 && action.number <= 70);
        gameState->getWhoMoves()->setLocationNum(action.number);
        gameState->startNextTurn();
    }
    guimanager->paint(gameState);
}
GameState* GameManager::getGameState()
{
    return gameState;
}

