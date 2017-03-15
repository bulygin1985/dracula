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


