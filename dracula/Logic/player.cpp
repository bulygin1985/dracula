#include "player.h"
#include "QsLog.h"

Player::Player() : locationNum(-1)
{
    QLOG_DEBUG() << "Player constructor";
}
int Player::getLocationNum() const
{
    return locationNum;
}

void Player::setLocationNum(int value)
{
    locationNum = value;
}
QString Player::getName() const
{
    return name;
}

void Player::setName(const QString &value)
{
    name = value;
}
uint Player::getMaxHealth() const
{
    return maxHealth;
}

void Player::setMaxHealth(const uint &value)
{
    maxHealth = value;
}
Player::Phase Player::getPhase() const
{
    return phase;
}

void Player::setPhase(const Phase &value)
{
    phase = value;
}
int Player::getHealth() const
{
    return health;
}

void Player::setHealth(int value)
{
    health = value;
}
QList<int> Player::getPossibleLocations() const
{
    return possibleLocations;
}
void Player::setPossibleLocations(const QList<int> &value)
{
    possibleLocations = value;
}



//void Player::copy(Player *player)
//{
//    QLOG_DEBUG() << "Player::copy";
//    *this = *player;
//}






