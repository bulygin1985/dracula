#include <assert.h>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>

#include "loader.h"
#include "QsLog.h"

Loader::Loader()
{
    QLOG_DEBUG() << " Loader constructor";
    loadLocations();
    loadLocationNames(locationNamesRus, "../info/location_names_rus.txt");
    loadLocationNames(locationNamesEng, "../info/location_names_eng.txt");
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

void Loader::loadLocationNames(QVector<QString> &locationNames, QString path)
{
    QLOG_DEBUG() << "Loader::loadLocationNames(" << path << ")";
    QFile locatioNameFile(path);
    if (!locatioNameFile.open(QFile::ReadOnly))
    {
        assert("cannot open location_names_rus.txt");
    }
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


