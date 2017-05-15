#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <assert.h>
#include <QStringList>

#include "QsLog.h"
#include "parameters.h"
#include "gameapplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    freopen("error.log", "w", stderr); // redirect assert to error.log
    // init the logging mechanism
    QsLogging::Logger& logger = QsLogging::Logger::instance();

    // set minimum log level and file name
    logger.setLoggingLevel(QsLogging::InfoLevel );
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
    parser.addOption({{"s", "server"}, "start server at the computer"});

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
    if (parser.isSet("server"))
    {
        param.isServer = true;
    }

//    if (param.whoAreYou.isEmpty()) //default value
//    {
//        param.whoAreYou << 0 << 1 << 2 << 3 << 4;
//    }

    QLOG_INFO() << "param.whoAreYou = " << param.whoAreYou;
    QLOG_INFO() << "param.mode = " <<param.mode;

    GameApplication gameApplication;
//    gameApplication.runMainMenu();
    gameApplication.runGame();

    return a.exec();
}
