#include "hunter.h"
#include "QsLog.h"

Hunter::Hunter()
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


