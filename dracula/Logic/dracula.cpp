#include "dracula.h"
#include "QsLog.h"
#include "constants.h"
#include "logicobjects.h"

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

void Dracula::setLocationNum(int value)
{
    QLOG_DEBUG() << "void Dracula::setLocationNum(" <<  value << ")";
    Player::setLocationNum(value);
    track.addTrackElement(TrackElement(value));
}

Track Dracula::getTrack() const
{
    return track;
}

void Dracula::copy(Player *player)
{
    QLOG_DEBUG() << "Dracula::copy()";
    *this = *dynamic_cast<Dracula*>(player);
}






