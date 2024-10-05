#include "Logger.h"
#include <QDateTime>
#include <QTextStream>
#include <QDebug>

Logger::Logger(QObject* parent)
    : QObject(parent) {
    // create file with current timestump as a name
    QString filename = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".log";

    // open log file for writing
    file.setFileName(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open log file: " << filename;
    } else {
        qDebug() << "Logging data to file: " << filename;
    }
}

Logger::~Logger() {
    // close the file when the Logger object is destroyed
    if (file.isOpen()) {
        file.close();
    }
}

void Logger::writeData(const SensorMetric& aSensorMetric) {
    // current time
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    // Prepare the log entry
    QString logEntry = QString("%1 | name=%2 | value=%3")
                           .arg(timestamp)
                           .arg(aSensorMetric.name)
                           .arg(aSensorMetric.value);

    // 1. print the log entry to the console
    qDebug() << logEntry;

    // 2. write the log entry to the file
    if (file.isOpen()) {
        QTextStream out(&file);
        out << logEntry << '\n';  // write log entry and add new line separator
        out.flush();
    } else {
        qDebug() << "Log file is not open!";
    }
}

#include "moc_Logger.cpp"
