#include "hunter.h"
#include "QsLog.h"
#include "movementcalculator.h"

Hunter::Hunter() : movementModifier(NONE)
{
    QLOG_DEBUG() << "Hunter constructor";
}
int Hunter::getBiteNum() const
{
    return biteNum;
}

void Hunter::setBiteNum(int value)
{
    biteNum = value;
}

void Hunter::copy(Player *player)
{
    QLOG_DEBUG() << "Hunter::copy()";
    *this = *dynamic_cast<Hunter*>(player);
}

void Hunter::calcPossibleMovements(const QSet<int> forbittenPlaces, int prevLoc)
{
    QLOG_DEBUG() << "Hunter::calcPossibleMovements()";
    MovementCalculator* mc = MovementCalculator::get();
    switch(movementModifier)
    {
        case NONE : possibleLocations = mc->getMovement(locationNum, prevLoc, forbittenPlaces).toList();
                    break;
    }
}
Hunter::MovementModifier Hunter::getMovementModifier() const
{
    return movementModifier;
}

void Hunter::setMovementModifier(const MovementModifier &value)
{
    movementModifier = value;
}


Hunter::~Hunter()
{

}


