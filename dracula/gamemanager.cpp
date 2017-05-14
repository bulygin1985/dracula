#include "gamemanager.h"
#include "gamestate.h"
#include "QsLog.h"
#include "constants.h"
#include "loader.h"
#include "QsLog.h"
#include "parameters.h"

#include <assert.h>

GameManager::GameManager()
{
    QLOG_DEBUG() << "GameManager constructor";
    prevGameState = new GameState();
    gameState = new GameState();
    guimanager = new Guimanager(gameState, prevGameState);
    gameController = new GameController(gameState, prevGameState);
    possibleActionCalculator = new PossibleActionCalculator(gameState, prevGameState);
    possibleActionCalculator->calc();
    connect(guimanager, SIGNAL(action(Action)), this, SLOT(processAction(Action)));
}

Guimanager *GameManager::getGuimanager() const
{
    QLOG_DEBUG() << "GameManager::getGuimanager";
    return guimanager;
}

bool GameManager::processAction(const Action& action)
{
    QLOG_DEBUG() << "GameManager::processAction()";
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

    if (Parameters::MULTI_PLAYER == Parameters::get().mode)
    {
        emit sendAction(action);
    }
    //TODO - AI if single player
    return true;
}

void GameManager::receiveAction(const Action &action)
{
    QLOG_INFO() << "GameManager::receiveAction(" << action.toQString() << ")";
    //only correct action could be received from server
    prevGameState->copy(gameState);
    gameController->process(action);
    possibleActionCalculator->calc();
    guimanager->paint();
}

GameController *GameManager::getGameController() const
{
    QLOG_DEBUG() << "GameManager::getGameController";
    return gameController;
}

void GameManager::reset()
{
    QLOG_DEBUG() << "GameManager::reset()";
    delete prevGameState;
    delete gameState;
    prevGameState = new GameState();
    gameState = new GameState();
    guimanager->setGameStates(gameState, prevGameState);
    gameController->setGameStates(gameState, prevGameState);
    possibleActionCalculator->setGameStates(gameState, prevGameState);
    possibleActionCalculator->calc();
}

GameState *GameManager::getPrevGameState() const
{
    QLOG_DEBUG() << "GameManager::getPrevGameState()";
    return prevGameState;
}

GameState* GameManager::getGameState()
{
    QLOG_DEBUG() << "GameManager::getGameState()";
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

