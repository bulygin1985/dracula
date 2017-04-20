#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>
#include <QVector>

#include "logicobjects.h"
#include "gamestate.h"

class Guimanager : public QObject
{
    Q_OBJECT
public:
    Guimanager(GameState * gameState);
    void paint(GameState * gameState);
    Q_INVOKABLE int getPlayerLocation(int playerNum) const;
    Q_INVOKABLE int getWhoMoves() const;
    Q_INVOKABLE double getPlayerPhi(int playerNum); //case if ther are several players on the same location
    Q_INVOKABLE QList<int> getTrack();
    Q_INVOKABLE int getPlayerHealth(int playerNum) const;
    Q_INVOKABLE int getPlayerMaxHealth(int playerNum) const;
    Q_INVOKABLE int getDayNightPosition() const;
signals:
    void requestPaint();
    void action(const Action& action);

public slots:
    void processAction(int num);

private:
    void calcPlayersPhi();
    GameState * gameState;
    QVector<double> phi;
};

#endif // GUIMANAGER_H
