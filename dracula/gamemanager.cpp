#include "gamemanager.h"
#include "gamestate.h"
#include "QsLog.h"

#include <assert.h>

GameManager::GameManager()
{
    guimanager = new Guimanager;
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
        gameState.getWhoMoves()->setLocationNum(action.number);
    }
    emit guimanager->paint(&gameState);
}
