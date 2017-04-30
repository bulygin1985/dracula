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
    QLOG_ERROR() << "elements == l.elements : " << (elements == l.elements);
    QLOG_ERROR() << "left size:" << elements.size();
    QLOG_ERROR() << "right size:" << l.elements.size();

//    for (int i = 0; i < elements.size(); i++)
//    {
//         QLOG_ERROR() << "right:" << elements.at(i).location.number;
//         QLOG_ERROR() << "left:" << l.elements.at(i).location.number;
//    }
    return (elements == l.elements);
}



