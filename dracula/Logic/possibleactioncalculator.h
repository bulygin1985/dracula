#ifndef POSSIBLEACTIONCALCULATOR_H
#define POSSIBLEACTIONCALCULATOR_H

#include "gamestate.h"
#include "movementcalculator.h"
#include "logicobjects.h"

class PossibleActionCalculator
{
public:
    PossibleActionCalculator(GameState * gameState, GameState * prevGameState);
    void calcPossibleMovements();
    void calc();
    bool isActionPossible(const Action &action, QString& message);
    void setGameStates(GameState * gameState, GameState * prevGameState);
    void resetPossibleActions();


private:
    GameState * gameState;
    GameState * prevGameState;
};

#endif // POSSIBLEACTIONCALCULATOR_H
