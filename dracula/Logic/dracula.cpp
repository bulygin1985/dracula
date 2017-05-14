#include "dracula.h"
#include "QsLog.h"
#include "constants.h"
#include "logicobjects.h"
#include "movementcalculator.h"

Dracula::Dracula() : movementModifier(NONE)
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

void Dracula::calcPossibleMovements(const QSet<int> forbittenPlaces, int prevLoc)
{
    QLOG_DEBUG() << "Dracula::calcPossibleMovements()";
    MovementCalculator* mc = MovementCalculator::get();
    QVector<int> near = mc->getMovement(locationNum, prevLoc, forbittenPlaces);
    switch(movementModifier)
    {
        case NONE:
            for (int i : near) { if (!track.isOnTrack(i) )
                    possibleLocations.push_back(i);}

    }
}

Track Dracula::getTrack() const
{
    QLOG_DEBUG() << "Dracula::getTrack()";
    QLOG_DEBUG() << "track.getElements().size() = "<< track.getElements().size();
    return track;
}

void Dracula::copy(Player *player)
{
    QLOG_DEBUG() << "Dracula::copy()";
    *this = *dynamic_cast<Dracula*>(player);
}

Dracula::MovementModifier Dracula::getMovementModifier() const
{
    return movementModifier;
}

void Dracula::setMovementModifier(const MovementModifier &value)
{
    movementModifier = value;
}


Dracula::~Dracula()
{

}





