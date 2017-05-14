#include "gameapplication.h"
#include "QsLog.h"
#include "loader.h"
#include "movementcalculator.h"


GameApplication::GameApplication(): gameManager(nullptr)
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

}

GameApplication::~GameApplication()
{
    reset();
}

void GameApplication::reset()
{
    QLOG_DEBUG() << "GameApplication::reset()";
    if (gameManager != nullptr)
    {
        gameManager->reset();
//        delete gameManager;
//        gameManager = nullptr;
    }
}

void GameApplication::runGame()
{
    QLOG_DEBUG() << "GameApplication::run()";
    emit gameManager->getGuimanager()->paint();
    if (gameManager != nullptr)
    {
        emit gameManager->getGuimanager()->gameChoosed();
    }
}

void GameApplication::runMainMenu()
{
    QLOG_DEBUG() << "GameApplication::runMainMenu()";
    gameManager->reset();
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
