#ifndef LOGICOBJECTS
#define LOGICOBJECTS

#include <QString>
#include <assert.h>

struct Action
{
    Action(int type, int num, int who = 0)
    {
        this->type = type;
        this->number = num;
        this->who = who;
    }
    int type;
    int number;
    int who; // - for events, items which are played by hunters, dracula
    QString toQString() const{
        return ( "(" + QString::number(type) + ", " + QString::number(number) +
                 ", " + QString::number(who) + ")" );
    }
};

struct LocationCard
{
    int number;    //number of land Location : 0..60, sea location : 61..70
    bool isOpened;
    LocationCard(int number = -1, bool isOpened = false)
    {
        this->number = number;
        this->isOpened = isOpened;
    }
    bool operator==(const LocationCard &l) const
    {
        return ((number == l.number) && (isOpened == l.isOpened));
    }
    bool operator!=(const LocationCard &l) const
    {
        return (!(*this == l));
    }
};

struct Card
{
    QString name;
    bool isOpened;
    Card(QString name = "", bool isOpened = false)
    {
        this->name = name;
        this->isOpened = isOpened;
    }
    virtual bool operator==(const Card &l) const
    {
        return ((name == l.name) && (isOpened == l.isOpened));
    }
    virtual bool operator!=(const Card &l) const
    {
        return (!(*this == l));
    }
};

struct EncounterCard : public Card {};

struct DraculaPowerCard : public Card {};

struct TrackElement
{
    LocationCard location;
    EncounterCard encounter;
    DraculaPowerCard draculaPower;
    TrackElement(LocationCard location = LocationCard(), EncounterCard encounterCard = EncounterCard(), DraculaPowerCard draculaPower = DraculaPowerCard())
    {
        this->location = location;
        this->encounter = encounterCard;
        this->draculaPower = draculaPower;
    }
    void open()
    {
        location.isOpened = true;
        encounter.isOpened = true;
        draculaPower.isOpened = true;
    }

    bool operator==(const TrackElement &l) const
    {
        return ( (encounter == l.encounter) && (location == l.location) && (draculaPower == l.draculaPower) );
    }
    bool operator!=(const TrackElement &l) const
    {
        return (!(*this == l));
    }
    QString toQString() const{
        return ( "| (" + QString::number(location.number) + ", " + QString::number(location.isOpened) +"), (" +
                 encounter.name + ", " + QString::number(encounter.isOpened) + "), (" +
                 draculaPower.name + ", " + QString::number(draculaPower.isOpened) + ") |" );
    }
};



#endif // LOGICOBJECTS

