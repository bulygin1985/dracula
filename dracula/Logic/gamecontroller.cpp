#include <assert.h>

#include "gamecontroller.h"
#include "QsLog.h"
#include "constants.h"
#include "utilityfunctions.h"
#include "loader.h"

GameController::GameController(GameState *gameState, GameState *prevGameState) :
    gameState(gameState),
    prevGameState(prevGameState)
{
}

void GameController::process(const Action &action)
{
    QLOG_DEBUG() << "GameController::process";
    if ((int)ActionType::LOCATION == action.type)
    {
        assert(action.number >= 0 && action.number <= getLocationAmount() - 1);
        int locationNum = action.number;
        gameState->getWhoMoves()->setLocationNum(locationNum);
        //check if we on dracula trail
        if (isLand(locationNum))  // only land location hunter could reveal using movement
        {
            if (isHunter(gameState->getWhoMovesNum()))
            {
                Track & track = gameState->getDracula()->getTrackRef();
                if (track.openTrack(locationNum))
                {
                    QLOG_INFO() << "track:" << track.toQString();
                    if (gameState->getDracula()->getLocationNum() == gameState->getWhoMoves()->getLocationNum())
                    {
                        reachDracula();
                    }
                }
            }
            else if (DRACULA_NUM == gameState->getWhoMovesNum())
            {
                draculaAttack();
            }
        }
        startNextTurn();
    }
}

bool GameController::draculaAttack()
{
    QLOG_DEBUG() << "GameController::draculaAttack()";
    Dracula * dracula = gameState->getDracula();
    std::vector<int> playerNum;
    for (int i = LORD_NUM; i <= MINA_NUM; i++)
    {
        if (dracula->getLocationNum() == gameState->getPlayer(i)->getLocationNum())
        {
            playerNum.push_back(i);
        }
    }
    if (playerNum.size() == 0) return false;
    if (playerNum.size() >= 1)
    {
        gameState->getDracula()->getTrackRef().openTrack(dracula->getLocationNum());
        reachDracula();
    }
    return true;
}

void GameController::reachDracula()
{
    QLOG_INFO() << "GameController::reachDracula()";

    if (isDay(gameState->getDayNightPosition()))
    {
        gameState->getDracula()->changeHealth(-4);
    }
    else if (isNight(gameState->getDayNightPosition()))
    {
        gameState->getDracula()->changeHealth(-2);
    }
}

bool GameController::isGameFinished()
{
    QLOG_DEBUG() << "GameController::isGameFinished()";

    bool draculaWin = (gameState->getDraculaScore() >= DRACULA_MAX_SCORE);
    bool hunterWin = (gameState->getDracula()->getHealth() <= 0);
    for (int i = DRACULA_NUM; i <= MINA_NUM; i++)
    {
        gameState->getPlayer(i)->resetPossibleAction();
    }
    if (draculaWin)
    {
        QLOG_INFO() << "Dracula wins!";
    }
    if (hunterWin)
    {
        QLOG_INFO() << "Hunter wins!";
    }
    if (draculaWin || hunterWin)
    {
        return true;
    }
    return false;
}

void GameController::setGameStates(GameState *gameState, GameState *prevGameState)
{
    this->gameState = gameState;
    this->prevGameState = prevGameState;
}

void GameController::startNextTurn()
{
    QLOG_DEBUG() << "GameController::startNextTurn()";
    gameState->setWhoMoves((gameState->getWhoMovesNum() + 1) % PLAYER_AMOUNT);
    int num =  gameState->getDracula()->getLocationNum();
    if ((DRACULA_NUM == gameState->getWhoMovesNum()) &&
            (!isSea(num))     //time stops on sea
            && (num != -1))   //it is not first round
    {
        gameState->incrementDayNightPosition();
    }
}

