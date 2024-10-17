#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Logger.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Logger logger;

    QQmlApplicationEngine engine;

    // expose Logger to QML
    engine.rootContext()->setContextProperty("logger", &logger);

    // fail check
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("QtCalc", "Main");

    return app.exec();
}

