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
    QVector<QString> locationNamesRus;
    QVector<QString> locationNamesEng;


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
    Q_INVOKABLE QPointF getLocationPoint(int i); //TODO -> to GuiManager
    Q_INVOKABLE QString getLocationName(int i, QString language = "rus");
};

#endif // LOADER_H
