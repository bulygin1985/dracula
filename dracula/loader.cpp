#include <assert.h>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include <QStringList>
#include <iostream>

#include "loader.h"
#include "QsLog.h"
#include "constants.h"

Loader::Loader()
{
    QLOG_DEBUG() << " Loader constructor";
    loadLocations();
    loadLocationNames(locationNamesRus, "../info/location_names_rus.txt");
    loadLocationNames(locationNamesEng, "../info/location_names_eng.txt");
    loadGraph("../info/roads_seas.txt", roadSeasGraph);
    loadGraph("../info/railway.txt", railWayGraph);
    loadGraph("../info/land_param.txt", landParam);

}

Loader& Loader::get()
{
    static Loader loader;
    return loader;
}

QPointF Loader::getLocationPoint(int i)
{
    assert(i < locationPoints.length());
    return locationPoints[i];
}

QVector<int> Loader::getNeighbours(int locationNumber)
{
    assert(locationNumber >= 0 && locationNumber <= LOCATION_NUMBER);
    return roadSeasGraph[locationNumber];
}

QString Loader::getLocationName(int i, QString language)
{
    QLOG_DEBUG() << " Loader::getLocationName(" << i << ")," << language <<")";

    if ("eng" == language)
    {
        assert(i >= 0 && i < locationNamesEng.length());
        return locationNamesEng[i];
    }
    assert(i >= 0 && i < locationNamesRus.length());
    return locationNamesRus[i];
}


void Loader::loadLocations()
{
    QLOG_DEBUG() << "Loader::loadLocations()";
    QFile locationPointFile("../info/location_points.txt");
    if (!locationPointFile.open(QIODevice::ReadOnly))
    {
        assert("cannot open cities_coor.txt");
    }
    QTextStream locationPointStream(&locationPointFile);
    QPointF point;
    int counter = 0;
    double number;
    while (!locationPointStream.atEnd())
    {
        locationPointStream >> number;
        if (counter % 3 == 0)  // we skip each third number
        {
            point.setX(number);
        }
        else if (counter % 3 == 1)
        {
            point.setY(number);
        }
        else if (counter % 3 == 2)
        {
            locationPoints.push_back(point);
        }
        counter++;
    }
}

void Loader::loadGraph(QString path, QVector<QVector<int> > &graph)
{
    QLOG_ERROR() << "Loader::loadGraph(" << path << ")";
    QFile graphFile(path);
    assert(graphFile.open(QFile::ReadOnly));
    QTextStream graphFileStream(&graphFile);
    while (!graphFileStream.atEnd())
    {
        QStringList list = graphFileStream.readLine().split(" ");
        list.pop_front(); // first number is equal to vector index
        QVector<int> neighbours;
        for (QString num: list) neighbours.push_back(num.toInt());
        graph.push_back(neighbours);
    }
}

void Loader::loadLocationNames(QVector<QString> &locationNames, QString path)
{
    QLOG_DEBUG() << "Loader::loadLocationNames(" << path << ")";
    QFile locatioNameFile(path);
    assert(locatioNameFile.open(QFile::ReadOnly));
    QTextCodec *codec = QTextCodec::codecForName("windows-1251");
    QTextStream locatioNameStream(&locatioNameFile);
    locatioNameStream.setCodec(codec);
    QString locationName = "";
    int num = 0;
    while (!locatioNameStream.atEnd())
    {
        locatioNameStream >> num;
        locationName = locatioNameStream.readLine().remove('\t');
        locationNames.push_back(locationName);
    }
}


