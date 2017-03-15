#include "dracula.h"
#include "QsLog.h"
#include "constants.h"

Dracula::Dracula()
{
    name = DRACULA_NAME;
    maxHealth = DRACULA_MAX_HEALTH;
    health = maxHealth;
    encounterMaxNumber = 5;
    eventMaxNumber = 4;
}
int Dracula::getEncounterMaxNumber() const
{
    return encounterMaxNumber;
}

void Dracula::setEncounterMaxNumber(int value)
{
    encounterMaxNumber = value;
}
int Dracula::getEventMaxNumber() const
{
    return eventMaxNumber;
}

void Dracula::setEventMaxNumber(int value)
{
    eventMaxNumber = value;
}



