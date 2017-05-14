#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "gamemanager.h"
#include "client.h"
#include "server.h"

class GameApplication : QObject
{
    Q_OBJECT

public:
    GameApplication();
    ~GameApplication();
    void reset();
    void runGame();
    void runMainMenu();

private:
    GameManager * gameManager;
    Client * client;
    Server * server;
    QQmlApplicationEngine engine;

public slots:
    void onPlayClicked();
    void onMainMenuClicked();

signals:
    void sceneShow(bool isShown);
};

#endif // GAMEAPPLICATION_H
