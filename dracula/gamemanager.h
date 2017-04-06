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
    GameState gameState; //TODO - remove to gameController.
    Guimanager *guimanager;


    Guimanager *getGuimanager() const;

public slots:
    bool processAction(const Action &action); //return false if Action is  incorrect

};

#endif // GAMEMANAGER_H
