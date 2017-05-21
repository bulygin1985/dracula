#ifndef AI_H
#define AI_H

#include "logicobjects.h"
#include "gamestate.h"


class AI
{
public:
    AI(GameState *gameState, GameState *prevGameState);
    Action getAction(int who);

    void setGameStates(GameState *gameState, GameState *prevGameState);

private:
    GameState *gameState;
    GameState * prevGameState;
};

#endif // AI_H
