#include "Sensor.h"
#include <QDebug>

Sensor::Sensor(QObject* parent): QObject(parent) {}

void Sensor::newData(int value) {
    SensorMetric metric;
    metric.name = "Sensor_" + QString::number(rand() % 10 + 1);  // random sensor name
    metric.value = value;

    qDebug() << "New data generated: Name =" << metric.name << ", Value =" << metric.value;

    // emit the signal to notify that new data is ready
    emit dataReady(metric);
}

#include "moc_Sensor.cpp"
