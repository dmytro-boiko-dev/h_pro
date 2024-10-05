#include <QCoreApplication>
#include <QTimer>
#include "Sensor.h"
#include "Logger.h"
#include "Analyzer.h"
#include "Config.h"

int main(int argc, char *argv[]) {

    // create app loop
    QCoreApplication a(argc, argv);

    Sensor sensor;
    Logger logger;
    Analyzer analyzer;

    // connect signals and slots
    QObject::connect(&sensor, &Sensor::dataReady, &logger, &Logger::writeData);
    QObject::connect(&sensor, &Sensor::dataReady, &analyzer, &Analyzer::analyzeData);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&sensor]() {
        int value = rand() % Config::RandomLimit; // generate random data
        sensor.newData(value);
    });
    timer.start(Config::GenerateTimeout); // generate data every 2 seconds

    // print current data every 10 seconds
    QTimer::singleShot(Config::PrintTimeout, [&analyzer]() {
        analyzer.reportPrint();
    });

    return a.exec(); // start app loop
}
