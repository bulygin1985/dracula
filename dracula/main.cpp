#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCommandLineParser>
#include <assert.h>
#include <QStringList>

#include "QsLog.h"
#include "gamemanager.h"
#include "loader.h"
#include "guimanager.h"
#include "movementcalculator.h"
#include "parameters.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    freopen("error.log", "w", stderr); // redirect assert to error.log
    // init the logging mechanism
    QsLogging::Logger& logger = QsLogging::Logger::instance();

    // set minimum log level and file name
    logger.setLoggingLevel(QsLogging::ErrorLevel );
    const QString sLogPath(QDir(a.applicationDirPath()).filePath("log.txt"));

    // Create log destinations
    QsLogging::DestinationPtr fileDestination(
    QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
    QsLogging::DestinationPtr debugDestination(
    QsLogging::DestinationFactory::MakeDebugOutputDestination() );

    // set log destinations on the logger
    logger.addDestination(debugDestination);
    logger.addDestination(fileDestination);

    QLOG_INFO() << "Program start";

    Parameters& param = Parameters::get();
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.setApplicationDescription("Fury of Dracula computer game");
    parser.addOption({{"m", "mode"}, "game mode : single_player, multi_player", "multi_player"});
    parser.addOption({{"w", "who"}, "who are you ? Set in number, f.e. -w 1 -w 2 -w 3, or -w dracula, -w hunters -w all", "all"});

    parser.process(a);

    QString modeString = parser.value("mode");
    if (modeString == "single_player") param.mode = Parameters::SINGLE_PLAYER;
    else if (modeString == "multi_player") param.mode = Parameters::MULTI_PLAYER;

    QString whoString = parser.value("who");

    if (whoString == "dracula") param.whoAreYou << 0;
    else if (whoString == "hunters") param.whoAreYou << 1 << 2 << 3 << 4;
    else if (whoString == "all")  param.whoAreYou << 0 << 1 << 2 << 3 << 4;

    if (param.whoAreYou.isEmpty())  //whoAreYou is not set yet
    {
        QStringList whoList = parser.values("who");
        bool isOk = true;
        for (QString numString : whoList)
        {
            int num = numString.toInt(&isOk);
            if (isOk) param.whoAreYou << num;
        }
    }

    if (param.whoAreYou.isEmpty())
    {
        param.whoAreYou << 0 << 1 << 2 << 3 << 4;
    }

    QLOG_ERROR() << "param.whoAreYou = " << param.whoAreYou;
    QLOG_ERROR() << "param.mode = " <<param.mode;


    GameManager manager;
    Loader& loader = Loader::get();
    MovementCalculator::create(loader.roadSeasGraph,
                               loader.railWayGraph, loader.landParam);

    Guimanager* guimanager = manager.getGuimanager();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("guimanager", guimanager);
    engine.load(QUrl(QStringLiteral("qrc:/GUI/main.qml")));
    emit manager.getGuimanager()->paint();

    return a.exec();
}
