#include "ai.h"
#include "parameters.h"
#include "QsLog.h"
#include "constants.h"

AI::AI(GameState *gameState, GameState *prevGameState) :
    gameState(gameState),
    prevGameState(prevGameState)
{
    QLOG_DEBUG() << " AI constructor";

}

void AI::setGameStates(GameState *gameState, GameState *prevGameState)
{
    this->gameState = gameState;
    this->prevGameState = prevGameState;
}

Action AI::getAction(int who)
{
    QLOG_DEBUG() << "AI::getAction()";
    QList<int> movements = gameState->getPlayer(who)->getPossibleLocations();
    int rand = qrand() % (movements.size());
    QLOG_INFO() << "rand  = " << rand;
    return Action((int)ActionType::LOCATION, movements[rand], who);
    //return Action((int)ActionType::DO_NOTHING, 0, who);
}
