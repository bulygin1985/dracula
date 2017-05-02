#ifndef HUNTER_H
#define HUNTER_H

#include "player.h"

class Hunter : public Player
{
public:

    enum MovementModifier{
        NONE = -1,
        TRAIN_X = 0,
        TRAIN_1 = 1,
        TRAIN_2 = 2,
        TRAIN_3 = 3,
        HORCE = 4,
        EXCELLENT_WEATHER = 5,
        CONTROL_STORM = 6,
        BATS = 7,   //encounter bats - use only roads, no sea, no railway
        ANY_LOCATION = 8
    };

    Hunter();
    virtual ~Hunter();

    int getBiteNum() const;
    void setBiteNum(int value);

    virtual void copy(Player * player);
    virtual void calcPossibleMovements(const QSet<int> forbittenPlaces = QSet<int>(), int prevLoc = -1);
    MovementModifier getMovementModifier() const;
    void setMovementModifier(const MovementModifier &value);



protected:
    MovementModifier movementModifier;
    int biteNum;
};

#endif // HUNTER_H
