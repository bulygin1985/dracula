#ifndef DRACULA_H
#define DRACULA_H

#include "player.h"

class Dracula : public Player
{
public:
    Dracula();

    int getEncounterMaxNumber() const;
    void setEncounterMaxNumber(int value);

    int getEventMaxNumber() const;
    void setEventMaxNumber(int value);

private:
    int encounterMaxNumber;  //maximum possible dracula encounters. Possible numbers: 5(initial), 7(if ally dracula's bride)
    int eventMaxNumber;      //depends on dracula ally
};

#endif // DRACULA_H
