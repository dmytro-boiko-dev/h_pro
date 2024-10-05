#include <QCoreApplication>
#include <QTimer>
#include "Sensor.h"
#include "Logger.h"
#include "Analyzer.h"

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
        int value = rand() % 100; // generate random data
        sensor.newData(value);
    });
    timer.start(2000); // generate data every 2 seconds

    // print current data every 10 seconds
    QTimer::singleShot(10000, [&analyzer]() {
        analyzer.reportPrint();
    });

    return a.exec(); // start app loop
}
