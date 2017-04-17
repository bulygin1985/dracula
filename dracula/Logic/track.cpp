#include "track.h"
#include "QsLog.h"
#include "constants.h"

Track::Track()
{
    QLOG_DEBUG() << "Track constructor";
}

void Track::addLocation(int number)
{
    QLOG_DEBUG() << "Track::addLocation(" << number << ")";
    locations.push_front(number);
    if (locations.size() == TRACK_SIZE + 1)
    {
        locations.pop_back();
    }
}
QList<int> Track::getLocations() const
{
    return locations;
}


