#ifndef DRACULA_H
#define DRACULA_H

#include "player.h"
#include "track.h"

class Dracula : public Player
{
public:
    Dracula();

    int getEncounterMaxNumber() const;
    void setEncounterMaxNumber(int value);

    int getEventMaxNumber() const;
    void setEventMaxNumber(int value);

    virtual void setLocationNum(int value);



    Track getTrack() const;
    virtual void copy(Player * player);

private:
    int encounterMaxNumber;  //maximum possible dracula encounters. Possible numbers: 5(initial), 7(if ally dracula's bride)
    int eventMaxNumber;      //depends on dracula ally
    Track track;

};

#endif // DRACULA_H
