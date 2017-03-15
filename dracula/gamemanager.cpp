#include "gamemanager.h"
#include "gamestate.h"
#include "QsLog.h"

#include <assert.h>

GameManager::GameManager()
{

}

bool GameManager::processAction(Action action)
{
    if ("location" == action.kind)
    {
        assert(action.number >= 0 && action.number <= 70);
        gameState.getWhoMoves()->setLocationNum(action.number);
    }
}
