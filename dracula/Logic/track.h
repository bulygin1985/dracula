#ifndef TRACK_H
#define TRACK_H

#include <QList>
#include <logicobjects.h>

class Track
{
public:
    Track();
    //track elelement is added only to begin of track
    void addTrackElement(const TrackElement& element);
    QList<TrackElement> elements;

    QList<TrackElement> getElements() const;
    bool operator==(const Track &l) const;
    bool operator!=(const Track &l) const;
    bool isOnTrack(int i);

private:
    QList<int> locations;
};

#endif // TRACK_H
