#ifndef HUNTER_H
#define HUNTER_H

#include "player.h"

class Hunter : public Player
{
public:
    Hunter();

    int getBiteNum() const;
    void setBiteNum(int value);

    virtual void copy(Player * player);

protected:
    int biteNum;
};

#endif // HUNTER_H
