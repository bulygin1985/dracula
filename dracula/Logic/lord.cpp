#include "lord.h"
#include "QsLog.h"
#include "constants.h"

Lord::Lord()
{
    QLOG_DEBUG() << "Lord constructor";
    name = LORD_NAME;
    maxHealth = LORD_MAX_HEALTH;
    health = maxHealth;
}

Lord::~Lord()
{

}

