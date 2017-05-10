#include "gamemanager.h"
#include "gamestate.h"
#include "QsLog.h"
#include "constants.h"
#include "loader.h"
#include "QsLog.h"

#include <assert.h>

GameManager::GameManager()
{
    prevGameState = new GameState();
    gameState = new GameState();
    guimanager = new Guimanager(gameState, prevGameState);
    gameController = new GameController(gameState);
    possibleActionCalculator = new PossibleActionCalculator(gameState, prevGameState);
    possibleActionCalculator->calc();
    connect(guimanager, SIGNAL(action(Action)), this, SLOT(processAction(Action)));
}

Guimanager *GameManager::getGuimanager() const
{
    return guimanager;
}

bool GameManager::processAction(const Action& action)
{
    QString message;
    if (!possibleActionCalculator->isActionPossible(action, message))
    {
        guimanager->setWrongMessage(message);
        return false;
    }
    prevGameState->copy(gameState);
    gameController->process(action);

    possibleActionCalculator->calc();

    guimanager->paint();

    //TODO - send if network
    //TODO - AI if single player
    return true;
}
GameController *GameManager::getGameController() const
{
    return gameController;
}

GameState *GameManager::getPrevGameState() const
{
    return prevGameState;
}

GameState* GameManager::getGameState()
{
    return gameState;
}

GameManager::~GameManager()
{
    QLOG_DEBUG() << "GameManager destructor";
    delete gameState;
    delete prevGameState;
    delete gameController;
    delete guimanager;
}

