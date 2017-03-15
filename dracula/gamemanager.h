#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>

#include "gamestate.h"
#include "logicobjects.h"

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager();
    GameState gameState; //TODO - remove to gameController.

public slots:
    bool processAction(Action action); //return false if Action is  incorrect

};

#endif // GAMEMANAGER_H
