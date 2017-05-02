#ifndef LOADER_H
#define LOADER_H

#include <QVector>
#include <QObject>
#include <QPointF>


class Loader : public QObject
{
    Q_OBJECT
private:
    QVector<QString> locationNamesRus;
    QVector<QString> locationNamesEng;
    QVector<QPointF> locationPoints;


private:
    void loadLocations();
    void loadGraph(QString path, QVector<QVector<int> > & graph);
    void loadLocationNames(QVector<QString>& locationNames, QString path);
    Loader();

public:

    QVector<QVector<int> > roadSeasGraph;
    QVector<QVector<int> > railWayGraph;
    QVector<QVector<int> > landParam;

    static Loader& get();
    QString getLocationName(int i, QString language = "rus");
    QPointF getLocationPoint(int i);
    QVector<int> getNeighbours(int locationNumber);
};

#endif // LOADER_H
