#include "Sensor.h"
#include <QDebug>

Sensor::Sensor(const QString &name, QObject *parent)
    : QObject(parent), sensorName(name) {
}

void Sensor::newData(int value) {
    SensorMetric metric;
    metric.name = sensorName;
    metric.value = value;

    qDebug() << sensorName << ": Name =" << metric.name << ", Value =" << metric.value;

    emit dataReady(metric);
}

QString Sensor::getName() const {
    return sensorName;
}
