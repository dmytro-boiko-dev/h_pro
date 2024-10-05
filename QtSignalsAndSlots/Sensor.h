#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include "SensorMetric.h"

class Sensor : public QObject {
    Q_OBJECT
public:
    Sensor(QObject* parent = nullptr);

    void newData(int value);

signals:
    void dataReady(const SensorMetric& aSensorMetric);
};

#endif // SENSOR_H
