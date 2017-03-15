#ifndef LOGICOBJECTS
#define LOGICOBJECTS

#include "QString"

struct Action
{
    Action(QString kind, int num)
    {
        this->kind = kind;
        this->number = num;
    }

    QString kind;
    int number;
};

#endif // LOGICOBJECTS

