#include "dracula.h"
#include "QsLog.h"
#include "constants.h"
#include "logicobjects.h"
#include "movementcalculator.h"
#include "utilityfunctions.h"

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

void Dracula::setLocationNum(int locationNum)
{
    QLOG_DEBUG() << "Dracula::setLocationNum(" <<  locationNum << ")";
    Player::setLocationNum(locationNum);
    track.addTrackElement(TrackElement(locationNum));
    if (isSea(track.getElements().front().location.number))
    {
        int numOfSeas = 0;
        for (TrackElement& element : track.getElements())
        {
            if (isSea(element.location.number)) numOfSeas++;
            else break;
        }
        if (numOfSeas % 2 == 1) health--;  //if it is odd sea
    }
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

Track &Dracula::getTrackRef()
{
    QLOG_DEBUG() << "Dracula::getTrackRef()";
    return track;
}

void Dracula::copy(Player *player)
{
    QLOG_DEBUG() << "Dracula::copy()";
    *this = *dynamic_cast<Dracula*>(player);
}

Dracula::MovementModifier Dracula::getMovementModifier() const
{
    QLOG_DEBUG() << "Dracula::getMovementModifier()";
    return movementModifier;
}

void Dracula::setMovementModifier(const MovementModifier &value)
{
    QLOG_DEBUG() << "Dracula::setMovementModifier()";
    movementModifier = value;
}

void Dracula::changeHealth(int delta)
{
    QLOG_DEBUG() << "Dracula::changeHealth()";

    health += delta;
    if (health > maxHealth) health = maxHealth;
    else if (health < 0) health = 0;
}


Dracula::~Dracula()
{
    QLOG_DEBUG() << "Dracula destructor";

}





