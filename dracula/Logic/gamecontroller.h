#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "gamestate.h"

class GameController
{
public:
    GameController(GameState *gameState);
    void process(const Action &action);
private:
    void startNextTurn();
    GameState *gameState;
};

#endif // GAMECONTROLLER_H
