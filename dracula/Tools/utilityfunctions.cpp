#include "utilityfunctions.h"
#include "assert.h"
#include "constants.h"
#include "parameters.h"
#include "loader.h"

bool isHunter(int playerNum)
{
    return (playerNum >= LORD_NUM && playerNum <= MINA_NUM);
}

bool areYouHunter()
{
   const QSet<int> &whoAreYou = Parameters::get().whoAreYou;
   return ( whoAreYou.contains(LORD_NUM) || whoAreYou.contains(DOCTOR_NUM) || whoAreYou.contains(HELSING_NUM) ||  whoAreYou.contains(MINA_NUM) );
}

bool areYouDracula()
{
    const QSet<int> &whoAreYou = Parameters::get().whoAreYou;
    return whoAreYou.contains(DRACULA_NUM);
}

bool isWest(int num)
{
    if (isSea(num)) return false;  //incorrect value
    return (Loader::get().landParam[num][0] == 1) ? true: false;
}

bool isCity(int num)
{
    if (isSea(num)) return false;  //incorrect value
    return (Loader::get().landParam[num][1] == 1) ? true: false;
}

bool isPort(int num)
{
    if (isSea(num)) return false;  //incorrect value
    return (Loader::get().landParam[num][2] == 1) ? true: false;
}

bool isSea(int num)
{
    return (num >= Loader::get().railWayGraph.size()) ? true : false;
}

int getLocationAmount()
{
    return Loader::get().roadSeasGraph.size();
}

bool isLand(int num)
{
    return !isSea(num);
}

bool isDay(int time)
{
    return ((time <= 2) && (time >= 0));
}

bool isNight(int time)
{
    return ((time <= 5) && (time >= 3));
}
