#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "QsLog.h"
#include "gamemanager.h"
#include "loader.h"
#include "guimanager.h"


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
    GameManager manager;

    Guimanager* guimanager = manager.getGuimanager();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("loader", &Loader::get());
    engine.rootContext()->setContextProperty("guimanager", guimanager);
    engine.load(QUrl(QStringLiteral("qrc:/GUI/main.qml")));
    emit manager.getGuimanager()->paint(manager.getGameState(), manager.getPrevGameState());

    return a.exec();
}
