#ifndef LOADER_H
#define LOADER_H

#include <QVector>
#include <QObject>
#include <QPointF>


class Loader : public QObject
{
    Q_OBJECT
private:
    QVector<QPointF> locationPoints;

private:
    void loadLocations();
    Loader();

public:
    static Loader& get();
    Q_INVOKABLE QPointF getLocationPoint(int i);
};

#endif // LOADER_H
