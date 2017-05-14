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

bool Track::isOnTrack(int i)
{
    QLOG_DEBUG() << "Track::isOnTrack";
    for (TrackElement  &element : elements)
    {
        if (i == element.location.number)
        {
            return true;
        }
    }
    return false;
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



