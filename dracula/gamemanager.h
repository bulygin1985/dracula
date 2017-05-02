#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>

#include "gamestate.h"
#include "logicobjects.h"
#include "guimanager.h"
#include "gamecontroller.h"
#include "possibleactioncalculator.h"

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager();
    ~GameManager();

    Guimanager *getGuimanager() const;

    GameState* getGameState();
    GameState *getPrevGameState() const;

    GameController *getGameController() const;

public slots:
    bool processAction(const Action &action); //return false if Action is  incorrect

private:
    GameState* gameState; //TODO - remove to gameController.
    GameState* prevGameState;
    GameController * gameController;
    Guimanager *guimanager;
    PossibleActionCalculator * possibleActionCalculator;
};

#endif // GAMEMANAGER_H
