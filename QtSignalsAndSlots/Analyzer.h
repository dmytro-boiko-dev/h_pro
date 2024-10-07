#ifndef ANALYZER_H
#define ANALYZER_H

#include <QObject>
#include <QList>
#include "SensorMetric.h"

class Analyzer : public QObject {
    Q_OBJECT
public:
    Analyzer(int maxMemorySize, QObject* parent = nullptr);

    void reportPrint() const;

public slots:
    void analyzeData(const SensorMetric& aSensorMetric);

private:
    QList<SensorMetric> memory;
    int maxMemorySize;  // Store the maximum memory size
};

#endif // ANALYZER_H
