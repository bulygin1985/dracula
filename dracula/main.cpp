#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "QsLog.h"
#include "gamemanager.h"
#include "loader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    freopen("error.log", "w", stderr); // redirect assert to error.log
    // init the logging mechanism
    QsLogging::Logger& logger = QsLogging::Logger::instance();

    // set minimum log level and file name
    logger.setLoggingLevel(QsLogging::DebugLevel );
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
    QLOG_INFO() << "Lord new location number is " << manager.gameState.getHunter(1)->getLocationNum();


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("loader", &Loader::get());
    engine.load(QUrl(QStringLiteral("qrc:/GUI/main.qml")));


    return a.exec();
}
