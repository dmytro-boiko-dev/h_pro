#include "Analyzer.h"
#include <QDebug>

Analyzer::Analyzer(int maxMemorySize, QObject* parent)
    : QObject(parent), maxMemorySize(maxMemorySize) {
}

void Analyzer::reportPrint() const {
    for (const auto& metric : memory) {
        qDebug() << "Stored Data - Name:" << metric.name << "Value:" << metric.value;
    }
}

void Analyzer::analyzeData(const SensorMetric& aSensorMetric) {
    if (memory.size() >= maxMemorySize) {
        memory.pop_front();  // remove the oldest data if the limit is reached
    }
    memory.append(aSensorMetric);  // store new data in memory
}

#include "moc_Analyzer.cpp"
