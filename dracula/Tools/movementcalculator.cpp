#include "movementcalculator.h"

MovementCalculator* MovementCalculator::movementCalculator = nullptr;

#include <QDebug>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <QVector>

MovementCalculator::MovementCalculator(QVector<QVector<int> >& roadSeaGraph, QVector<QVector<int> >& railwayGraph, QVector<QVector<int> > &landParam)
{
    this->roadSeaGraph = roadSeaGraph;
    this->railwayGraph = railwayGraph;
    this->landParam = landParam;
}

void MovementCalculator::create(QVector<QVector<int> > &roadSeaGraph, QVector<QVector<int> > &railwayGraph, QVector<QVector<int> > &landParam)
{

    if (movementCalculator == NULL)
    {
    //assert(!movementCalculator);
    movementCalculator = new MovementCalculator(roadSeaGraph, railwayGraph, landParam);
    }
}

MovementCalculator* MovementCalculator::get()
{
    assert(movementCalculator);
    return movementCalculator;
}

QVector<int> MovementCalculator::getTrainMovement(unsigned int begin, unsigned int length, const QSet<int> blocked) const
{
    QVector<int> locations;
    if (length > 3 || begin >= railwayGraph.size() || length == 0) return locations;
    QSet<int> eastTrain; //only for length = 3
    std::queue<int> q;
    QVector<int> dists(railwayGraph.size(), -1);
    dists[begin] = 0;
    q.push(begin);
    if (!isWest(begin)) eastTrain.insert(begin);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        if (dists[u] < length - (eastTrain.contains(u) && length == 3))
        {
            for (int v : railwayGraph[u])
            {
                if (dists[v] == -1 && !blocked.contains(v))
                {
                    q.push(v);
                    dists[v] = dists[u] + 1;
                    if (eastTrain.contains(u) || !isWest(v)) eastTrain.insert(v);
                    if (dists[v] < 3 || (!eastTrain.contains(v))) locations.push_back(v);
                }
            }
        }
    }
    return locations;
}

QVector<int> MovementCalculator::getMovement(unsigned int begin, int prevLoc, const QSet<int> forbitten) const
{
    //qDebug() << "MovementCalculator::getMovement(begin =" << begin  << "prevSea =" << prevSea << ")";
    if (begin >= roadSeaGraph.size()) return QVector<int>();
    QVector<int> near = roadSeaGraph[begin];
    QVector<int> locations;
    for (int i : near) if ( !forbitten.contains(i) ) locations.push_back(i);
    if (!isSea(begin)) locations.push_back(begin);  //we could not stay on sea
    bool noBackWay = isSea(begin) && (isSea(prevLoc) || isPort(prevLoc));
    if (noBackWay)
        locations.erase( std::remove( locations.begin(), locations.end(), prevLoc ), locations.end() );
    return locations;
}

QVector<int> MovementCalculator::getBatMovement(unsigned int begin, QSet<int> saintPlaces) const
{
    QVector<int> locations;
    if (begin >= railwayGraph.size()) return locations;
    std::queue<int> q;
    QVector<int> dists(railwayGraph.size(), -1);
    dists[begin] = 0;
    q.push(begin);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        if (dists[u] < 2)
        {
            for (int v : roadSeaGraph[u])
            {
                if (dists[v] == -1 && v <= 60 && !saintPlaces.contains(v))
                {
                    q.push(v);
                    dists[v] = dists[u] + 1;
                    locations.push_back(v);
                }
            }
        }
    }
    return locations;
}

QVector<int> MovementCalculator::getWolfMovement(unsigned int begin, QSet<int> saintPlaces) const
{
    QVector<int> locations = getBatMovement(begin, saintPlaces);
    if (begin < railwayGraph.size()) locations.push_back(begin);
    return locations;

}

QVector<int> MovementCalculator::getHorceMovement(unsigned int begin) const
{
    return getWolfMovement(begin);
}

QVector<int> MovementCalculator::getExcellentWeatherMovements(unsigned int begin) const
{
    QVector<int> locations;
    if (!isPort(begin)) return locations;
    std::queue<int> q;
    QVector<int> dists(roadSeaGraph.size(), -1);
    dists[begin] = 0;
    q.push(begin);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        if (dists[u] < 4 )
        {
            if (!isPort(u) || dists[u] == 0) // port city in end point except begin port
            {
                for (int v : roadSeaGraph[u])
                {
                    if (dists[v] == -1 && (isPort(v) || isSea(v)))
                    {
                        q.push(v);
                        dists[v] = dists[u] + 1;
                        locations.push_back(v);
                    }
                }
            }
        }
    }
    return locations;
}

QVector<int> MovementCalculator::getControlStormMovements(unsigned int begin) const
{
    QVector<int> locations;
    if (!isSea(begin)) return locations;
    std::queue<int> q;
    QVector<int> dists(roadSeaGraph.size(), -1);
    dists.clear();
    dists = QVector<int>(roadSeaGraph.size(), -1);
    dists[begin] = 0;
    q.push(begin);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
        if (dists[u] < 4 )
        {
            for (int v : roadSeaGraph[u])
            {
                if (dists[v] == -1 && (isPort(v) || isSea(v)))
                {
                    q.push(v);
                    dists[v] = dists[u] + 1;
                    if (isPort(v)) locations.push_back(v);
                }
            }
        }
    }
    return locations;
}

QVector<int> MovementCalculator::getNeighbours(unsigned int begin) const
{
    return roadSeaGraph[begin];
}

QVector<int> MovementCalculator::getLandNeighbours(unsigned int begin) const
{
    QVector<int> neighbours = roadSeaGraph[begin];
    QVector<int> landNeighbours;
    for (int i : neighbours) if (!isSea(i)) landNeighbours.push_back(i);
    return landNeighbours;
}


bool MovementCalculator::isWest(int num) const
{
    if (isSea(num)) return false;  //incorrect value
    return (landParam[num][0] == 1) ? true: false;
}

bool MovementCalculator::isCity(int num) const
{
    if (isSea(num)) return false;  //incorrect value
    return (landParam[num][1] == 1) ? true: false;
}

bool MovementCalculator::isPort(int num) const
{
    if (isSea(num)) return false;  //incorrect value
    return (landParam[num][2] == 1) ? true: false;
}

bool MovementCalculator::isSea(int num) const
{
    return (num >= railwayGraph.size()) ? true : false;
}

