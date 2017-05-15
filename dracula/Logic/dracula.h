#ifndef DRACULA_H
#define DRACULA_H

#include "player.h"
#include "track.h"

class Dracula : public Player
{
public:
    enum MovementModifier{
        NONE = 0,
        DOUBLE_BACK = 1,
        WOLF_FORM = 2,
        BAT = 3
    };

    Dracula();
    virtual ~Dracula();
    int getEncounterMaxNumber() const;
    void setEncounterMaxNumber(int value);

    int getEventMaxNumber() const;
    void setEventMaxNumber(int value);

    virtual void setLocationNum(int locationNum);
    virtual void calcPossibleMovements(const QSet<int> forbittenPlaces = QSet<int>(), int prevLoc = -1);

    Track getTrack() const;
    Track& getTrackRef();
    virtual void copy(Player * player);

    MovementModifier getMovementModifier() const;
    void setMovementModifier(const MovementModifier &value);

    void changeHealth(int delta);

private:
    Track track;
    int encounterMaxNumber;  //maximum possible dracula encounters. Possible numbers: 5(initial), 7(if ally dracula's bride)
    int eventMaxNumber;      //depends on dracula ally
    MovementModifier movementModifier;

};

#endif // DRACULA_H
