#include "gameapplication.h"
#include "QsLog.h"
#include "loader.h"
#include "movementcalculator.h"
#include "parameters.h"


GameApplication::GameApplication():
    gameManager(nullptr),
    server(nullptr),
    client(nullptr)
{
    Loader& loader = Loader::get();
    MovementCalculator::create(loader.roadSeasGraph,
                               loader.railWayGraph, loader.landParam);
    gameManager = new GameManager;
    Guimanager* guimanager = gameManager->getGuimanager();
    engine.rootContext()->setContextProperty("guimanager", guimanager);
    engine.load(QUrl(QStringLiteral("qrc:/GUI/main.qml")));

    connect( guimanager, SIGNAL(playClicked()), this, SLOT(onPlayClicked()) );
    connect( guimanager, SIGNAL(mainMenuClicked()), this, SLOT(onMainMenuClicked()) );

//TODO disconnect client before client deleting
}

GameApplication::~GameApplication()
{
    reset();
}

void GameApplication::reset()
{
    QLOG_INFO() << "GameApplication::reset()";
    if (gameManager != nullptr)
    {
        gameManager->reset();
    }
    if (server != nullptr)
    {
        delete server;
        server = nullptr;
    }
    if (client != nullptr)
    {
        client->close();
        disconnect( gameManager, SIGNAL(sendAction(Action)), client, SLOT(sendData(Action)) );
        disconnect( client, SIGNAL(actionIsReceived(Action)), gameManager, SLOT(receiveAction(Action)) );
        delete client;
        client = nullptr;
    }

}

void GameApplication::runGame()
{
    QLOG_DEBUG() << "GameApplication::run()";
    Parameters & param = Parameters::get();
    if (Parameters::MULTI_PLAYER == param.mode)
    {
        client = new Client;
        connect( gameManager, SIGNAL(sendAction(Action)), client, SLOT(sendData(Action)) );
        connect( client, SIGNAL(actionIsReceived(Action)), gameManager, SLOT(receiveAction(Action)) );
    }
    if (param.isServer)
    {
        QLOG_INFO() << "start server";
        server = new Server;
        server->start(); //first time hang app on 2 seconds
    }
    if (client->state() != QTcpSocket::ConnectedState) //???
    {
        client->connectToHost(param.serverIP, param.port);
        if (client->waitForConnected(1000))
        {
            QLOG_INFO() << "client is connected!";
        }
    }
    emit gameManager->getGuimanager()->paint();
    if (gameManager != nullptr)
    {
        emit gameManager->getGuimanager()->gameChoosed();
    }
}

void GameApplication::runMainMenu()
{
    QLOG_DEBUG() << "GameApplication::runMainMenu()";
    reset();
    if (gameManager != nullptr)
    {
        emit gameManager->getGuimanager()->menuChoosed();
    }
}

void GameApplication::onPlayClicked()
{
    runGame();
}

void GameApplication::onMainMenuClicked()
{
    runMainMenu();
}
