#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>

#include "logicobjects.h"
#include "gamestate.h"

class Guimanager : public QObject
{
    Q_OBJECT
public:
    Guimanager();

    void paint(GameState * gameState);
    Q_INVOKABLE int getPlayerLocation(int playerNum);

signals:
    void requestPaint();
    void action(const Action& action);

public slots:
    void processAction(int num);
private:
    GameState * gameState;
};

#endif // GUIMANAGER_H
