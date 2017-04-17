#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>

#include "gamestate.h"
#include "logicobjects.h"
#include "guimanager.h"

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager();
    Guimanager *guimanager;


    Guimanager *getGuimanager() const;

    GameState* getGameState();

public slots:
    bool processAction(const Action &action); //return false if Action is  incorrect

private:
    GameState* gameState; //TODO - remove to gameController.
};

#endif // GAMEMANAGER_H
