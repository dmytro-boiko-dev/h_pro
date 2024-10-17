#include "Logger.h"
#include <QDateTime>
#include <QTextStream>
#include <QDebug>

Logger::Logger(QObject* parent)
    : QObject(parent) {
    QString filename = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".log";
    file.setFileName(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open log file: " << filename;
    } else {
        qDebug() << "Logging data to file: " << filename;
    }
}

Logger::~Logger() {
    if (file.isOpen()) {
        file.close();
    }
}

void Logger::writeData(const SensorMetric& aSensorMetric) {
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString logEntry = QString("%1 | name=%2 | value=%3 \n")
                           .arg(timestamp)
                           .arg(aSensorMetric.name)
                           .arg(aSensorMetric.value);

    qDebug() << logEntry;

    // write the log entry to the file
    if (file.isOpen()) {
        QTextStream out(&file);
        out << logEntry;
        out.flush();  // ensure that data is written immediately
    } else {
        qDebug() << "Log file is not open!";
    }
}
