#ifndef MOVEMENTCALCULATOR
#define MOVEMENTCALCULATOR

#include <queue>
#include <QSet>
#include <QVector>

class MovementCalculator
{
public:
    static void create(QVector<QVector<int> > &roadSeaGraph, QVector<QVector<int> > &railwayGraph, QVector<QVector<int> > &landParam);
    static MovementCalculator *get();
    QVector<int> getTrainMovement(unsigned int begin, unsigned int length, const QSet<int> blocked = QSet<int>() ) const; //only for travelling by train
    QVector<int> getMovement(unsigned int begin, int prevLoc = -1, const QSet<int> forbitten = QSet<int>()) const; //usual movement when player cannot visit lat sea
    QVector<int> getBatMovement(unsigned int begin, QSet<int> saintPlaces = QSet<int>()) const;
    QVector<int> getWolfMovement(unsigned int begin, QSet<int> saintPlaces = QSet<int>()) const;
    QVector<int> getHorceMovement(unsigned int begin) const;
    QVector<int> getExcellentWeatherMovements(unsigned int begin) const;
    QVector<int> getControlStormMovements(unsigned int begin) const;
    QVector<int> getNeighbours(unsigned int begin) const;
    QVector<int> getLandNeighbours(unsigned int begin) const;
    bool isWest(int num) const;
    bool isCity(int num) const;
    bool isPort(int num) const;
    bool isSea(int num) const;


private:
    //MovementCalculator();
    static MovementCalculator *movementCalculator;
    MovementCalculator(QVector<QVector<int> >& roadSeaGraph, QVector<QVector<int> >& railwayGraph, QVector<QVector<int> >& landParam);
    QVector<QVector<int> > roadSeaGraph;
    QVector<QVector<int> > railwayGraph;
    QVector<QVector<int> > landParam;
//    std::queue<int> q;
//    QVector<int> dists;
};

#endif // MOVEMENTCALCULATOR

