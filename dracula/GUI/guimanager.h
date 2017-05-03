#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QStringList>

#include "logicobjects.h"
#include "gamestate.h"

class Guimanager : public QObject
{
    Q_OBJECT
public:
    Guimanager(GameState * gameState, GameState * prevGameState);
    void paint();
    void setWrongMessage(QString message);
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
    Q_INVOKABLE QPointF getLocationPoint(int i); //TODO -> to GuiManager
    Q_INVOKABLE QString getLocationName(int i, QString language = "rus");
    Q_INVOKABLE QStringList getEvents(int playerNum);


signals:
    void requestPaint();
    void wrongAction(QString message);
    void action(const Action& action);

public slots:
    void processAction(int type, int num, int who = 0);

private:
    // case if there are several player on the same location
    void calcPlayersPhi();
    GameState * gameState;
    GameState * prevGameState;

    QVector<double> phi;
    QStringList draculaItems;
    QVector<QStringList> hunterItemsVector;
};

#endif // GUIMANAGER_H
