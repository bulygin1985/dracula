#include "guimanager.h"
#include "QsLog.h"

Guimanager::Guimanager()
{

}

void Guimanager::processAction(int num)
{
    emit action(Action(num));
}
void Guimanager::paint(GameState *gameState)
{
    this->gameState = gameState;
    emit requestPaint();
}

int Guimanager::getPlayerLocation(int playerNum)
{
    return gameState->getPlayer(playerNum)->getLocationNum();
}

