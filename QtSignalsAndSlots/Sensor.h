#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include "SensorMetric.h"

class Sensor : public QObject {
    Q_OBJECT

public:
    Sensor(const QString &name, QObject *parent = nullptr);

    void newData(int value);

    QString getName() const;

signals:
    void dataReady(const SensorMetric& aSensorMetric);

private:
    QString sensorName;
};

#endif // SENSOR_H
