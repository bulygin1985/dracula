#include "doctor.h"
#include "QsLog.h"
#include "constants.h"

Doctor::Doctor()
{
    QLOG_DEBUG() << "Doctor constructor";
    name = DOCTOR_NAME;
    maxHealth = DOCTOR_MAX_HEALTH;
    health = maxHealth;
}

