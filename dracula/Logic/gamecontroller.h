#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "gamestate.h"

class GameController
{
public:
    GameController(GameState *gameState, GameState *prevGameState);
    void process(const Action &action);
    void setGameStates(GameState * gameState, GameState * prevGameState);
    void reachDracula();
    bool isGameFinished();


private:
    bool draculaAttack();
    void startNextTurn();
    GameState *gameState;
    GameState * prevGameState;

};

#endif // GAMECONTROLLER_H
