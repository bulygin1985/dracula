#include "track.h"
#include "QsLog.h"
#include "constants.h"
#include "QsLog.h"

Track::Track()
{
    QLOG_DEBUG() << "Track constructor";
}

void Track::addTrackElement(const TrackElement& element)
{
    QLOG_DEBUG() << "Track::addTrackElement(" << element.location.number << ","
                 << element.encounter.name << "," <<element.draculaPower.name << ")";


    elements.push_front(element);
    if (DRACULA_CASTLE_NUM == element.location.number) elements.front().location.isOpened = true;

    if (elements.size() == TRACK_SIZE + 1)
    {
        elements.pop_back();
    }
}

QList<TrackElement> Track::getElements() const
{
    return elements;
}

bool Track::operator==(const Track &l) const
{
    return (elements == l.elements);
}
bool Track::operator!=(const Track&l) const
{
    return (!(*this == l));
}

bool Track::isOnTrack(int locationNum) const
{
    QLOG_INFO() << "Track::isOnTrack( " << locationNum << " )";
    for (const TrackElement &element : elements)
    {
        if (locationNum == element.location.number)
        {
            return true;
        }
    }
    return false;
}

bool Track::openTrack(int locationNum)  //if HIDE - open it too
{
    QLOG_INFO() << "Track::openTrack( " << locationNum << " )";
    for (TrackElement &element : elements)
    {
        if (locationNum == element.location.number)
        {
            element.open();
            return true;
        }
    }
    return false;
}

int Track::getTrackIndex(int locationNum)
{
    for (int i = 0; i < elements.size(); i++)
    {
        TrackElement &element = elements[i];
        if (locationNum == element.location.number)
        {
            QLOG_INFO() << "we get it!";
            return i;
        }
    }
    return -1;
}

QString Track::toQString()
{
    QLOG_DEBUG() << "Track::toQString";
    QString trackString;
    for (TrackElement & element : elements)
    {
        trackString += (element.toQString()) + " ";
    }
    return trackString;
}



