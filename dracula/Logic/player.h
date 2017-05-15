#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QList>
#include <QSet>

class Player
{
public:
    Player();
    virtual ~Player();
    enum class Phase {WAIT = 0, MOVEMENT = 1, ACTION = 2, END_TURN = 3};

    virtual int getLocationNum() const;
    virtual void setLocationNum(int value);

    virtual QString getName() const;
    virtual void setName(const QString &value);

    virtual uint getMaxHealth() const;
    virtual void setMaxHealth(const uint &value);

    virtual Phase getPhase() const;
    virtual void setPhase(const Phase &value);

    virtual int getHealth() const;
    virtual void setHealth(int value);
    virtual void copy(Player * player) = 0;
    QList<int> getPossibleLocations() const;
    void setPossibleLocations(const QList<int> &value);
    void resetPossibleAction();  //set possible action containers as empty
    void addPossibleLocation(int i);
    virtual void calcPossibleMovements(const QSet<int> forbittenPlaces = QSet<int>(), int prevLoc = -1) = 0;


protected:
    int locationNum;   // land 1-60 - locations(cities), sea 61-70 - sea location
    QString name;
    int maxHealth;
    Phase phase;
    int health;
    QList<int> possibleLocations;
};

#endif // PLAYER_H
