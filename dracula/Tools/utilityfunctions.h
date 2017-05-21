#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <QVector>


bool isHunter(int playerNum);
bool areYouHunter();
bool areYouDracula();

bool isWest(int num);
bool isCity(int num);
bool isPort(int num);
bool isSea(int num);
bool isLand(int num);
bool isDay(int time);
bool isNight(int time);

int getLocationAmount();

QVector<int> getRandom(int smallest, int largest, int size);



#endif // UTILITYFUNCTIONS_H
