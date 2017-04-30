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
    Guimanager(GameState * gameState, GameState * prevGameState);
    void paint(GameState * gameState, GameState * prevGameState);
    Q_INVOKABLE int getPlayerLocation(int playerNum) const; //TODO : return playreLoc + Phi
    Q_INVOKABLE int getWhoMoves() const;
    Q_INVOKABLE double getPlayerPhi(int playerNum); //case if ther are several players on the same location
    Q_INVOKABLE QList<int> getLocations(QString type);
    Q_INVOKABLE QList<bool> getOpenState(QString name);
    Q_INVOKABLE int getPlayerHealth(int playerNum) const;
    Q_INVOKABLE int getPlayerMaxHealth(int playerNum) const;
    Q_INVOKABLE int getDayNightPosition() const;
    Q_INVOKABLE bool isTrackerChanged() const;
    Q_INVOKABLE QList<int> getPossibleLocations();
signals:
    void requestPaint();
    void action(const Action& action);

public slots:
    void processAction(int num);

private:
    // case if there are several player on the same location
    void calcPlayersPhi();
    GameState * gameState;
    GameState * prevGameState;

    QVector<double> phi;
};

#endif // GUIMANAGER_H
