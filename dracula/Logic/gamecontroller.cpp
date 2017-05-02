#include <assert.h>

#include "gamecontroller.h"
#include "QsLog.h"
#include "constants.h"

GameController::GameController(GameState *gameState) : gameState(gameState)
{

}

void GameController::process(const Action &action)
{
    QLOG_DEBUG() << "GameController::process";
    assert(action.number >= 0 && action.number <= 70);
    gameState->getWhoMoves()->setLocationNum(action.number);
    startNextTurn();
}

void GameController::startNextTurn()
{
    QLOG_DEBUG() << "GameController::startNextTurn()";
    gameState->setWhoMoves((gameState->getWhoMovesNum() + 1) % PLAYER_AMOUNT);
    int num =  gameState->getDracula()->getLocationNum();
    if ((DRACULA_NUM == gameState->getWhoMovesNum()) &&
            (num <= 60)     //time stops on sea
            && (num != -1)) //it is notfirst round
    {
        gameState->incrementDayNightPosition();
    }
}

