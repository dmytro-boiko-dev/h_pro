#include "Analyzer.h"
#include <QDebug>

Analyzer::Analyzer(QObject* parent) : QObject(parent) {}

void Analyzer::reportPrint() const {
    for (const auto& metric : memory) {
        qDebug() << "Stored Data - Name:" << metric.name << "Value:" << metric.value;
    }
}

void Analyzer::analyzeData(const SensorMetric& aSensorMetric) {
    if (memory.size() >= 10000) {
        memory.pop_front();  // remove oldest data if we exceed the limit
    }
    memory.append(aSensorMetric);  // store new data in memory
}

#include "moc_Analyzer.cpp"