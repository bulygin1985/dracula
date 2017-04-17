#ifndef TRACK_H
#define TRACK_H

#include <QList>

class Track
{
public:
    Track();
    void addLocation(int number);

    QList<int> getLocations() const;

private:
    QList<int> locations;
};

#endif // TRACK_H
