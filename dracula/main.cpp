#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDir>

#include "QsLog.h"
#include "gamemanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    freopen("error.log", "w", stderr); // redirect assert to error.log
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
    Lord lord;
    QLOG_INFO() << "Lord name is " << lord.getName();
    GameManager manager;
    Action action("location", 5);
    manager.processAction(action);
    QLOG_INFO() << "Dracula new location number is " << manager.gameState.getDracula()->getLocationNum();
    exit(0);
    return a.exec();
}
