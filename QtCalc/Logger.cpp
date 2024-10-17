#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDateTime>
#include <QDebug>

Logger::Logger(QObject *parent)
    : QObject(parent)
{
}

void Logger::logToFile(const QString& input, const QString& result) {

    QDir logDir("logs");
    if (!logDir.exists()) {
        logDir.mkpath(".");
    }

    // open the log file in append mode
    QFile logFile("logs/calculator.log");
    if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Unable to open log file for writing.";
        return;
    }

    // text stream to write to the file
    QTextStream out(&logFile);

    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    out << "[" << currentTime << "] Input: " << input << ", Result: " << result << "\n";

    logFile.close();
}
