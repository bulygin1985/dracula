#include "Logic/mina.h"
#include "QsLog.h"
#include "constants.h"

Mina::Mina()
{
    QLOG_DEBUG() << "Mina constructor";
    name = MINA_NAME;
    maxHealth = MINA_MAX_HEALTH;
    health = maxHealth;
}

