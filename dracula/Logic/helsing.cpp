#include "helsing.h"
#include "QsLog.h"
#include "constants.h"

Helsing::Helsing()
{
    QLOG_DEBUG() << "Helsing constructor";
    name = HELSING_NAME;
    maxHealth = HELSING_MAX_HEALTH;
    health = maxHealth;
}

Helsing::~Helsing()
{

}

