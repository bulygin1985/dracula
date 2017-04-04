#include <assert.h>
#include <QTextStream>

#include "loader.h"
#include <QFile>

Loader::Loader()
{
    loadLocations();
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

void Loader::loadLocations()
{
    QFile locationPointFile("../info/location_points.txt");
    if (!locationPointFile.open(QIODevice::ReadWrite))
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
