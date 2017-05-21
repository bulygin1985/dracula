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
    ai = new AI(gameState, prevGameState);
    possibleActionCalculator = new PossibleActionCalculator(gameState, prevGameState);
    possibleActionCalculator->calc();
    connect(guimanager, SIGNAL(action(Action)), this, SLOT(processAction(Action)));
    if (Parameters::SINGLE_PLAYER == Parameters::get().mode)
    {
        requestAIaction();
    }
}

Guimanager *GameManager::getGuimanager() const
{
    QLOG_DEBUG() << "GameManager::getGuimanager";
    return guimanager;
}

bool GameManager::processAction(const Action& action)
{
    QLOG_INFO() << "GameManager::processAction(" << action.toQString() << ")";
    QString message;
    if (!possibleActionCalculator->isActionPossible(action, message))
    {
        QLOG_INFO() << "wrong action";
        guimanager->setWrongMessage(message);
        return false;
    }
    prevGameState->copy(gameState);
    gameController->process(action);
    if (!gameController->isGameFinished())
    {
        possibleActionCalculator->calc();
    }
    else
    {
        possibleActionCalculator->resetPossibleActions();
    }

    guimanager->paint(action);

    if (Parameters::MULTI_PLAYER == Parameters::get().mode)
    {
        emit sendAction(action);
    }
    if (Parameters::SINGLE_PLAYER == Parameters::get().mode)
    {
        requestAIaction();
    }
    //TODO - AI if single player
    return true;
}

void GameManager::receiveAction(const Action &action)
{
    QLOG_INFO() << "GameManager::receiveAction(" << action.toQString() << ")";
    processAction(action);
}

void GameManager::requestAIaction()
{
    QLOG_DEBUG() << "GameManager::requestAIaction";
    QLOG_INFO() << "SINGLE_PLAYER mode";
    if (gameState->isAIturn()) //your turn, then AI turn
    {
        QLOG_INFO() << "gameState->isAIturn()";

        Action action = ai->getAction(gameState->getWhoMovesNum());
        QLOG_INFO() << "action:" << action.toQString();
        if (action.type != (int)ActionType::DO_NOTHING)
        {
            processAction(action);
        }
    }
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
    ai->setGameStates(gameState, prevGameState);
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
    delete ai;
}

