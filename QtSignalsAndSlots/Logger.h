#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include "SensorMetric.h"

class Logger : public QObject {
    Q_OBJECT
public:
    Logger(QObject* parent = nullptr);
    ~Logger();

public slots:
    void writeData(const SensorMetric& aSensorMetric);

private:
    QFile file;
};

#endif // LOGGER_H
