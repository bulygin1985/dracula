#ifndef TRACK_H
#define TRACK_H

#include <QList>
#include <logicobjects.h>
#include <QString>

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
    bool isOnTrack(int locationNum) const;
    bool openTrack(int locationNum);
    int getTrackIndex(int locationNum);
    QString toQString();

private:
    QList<int> locations;
};

#endif // TRACK_H
