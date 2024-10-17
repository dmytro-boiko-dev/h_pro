#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QMap>
#include "Sensor.h"
// #include "Logger.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void logToTable(const QString &sensorName, int value);  // Method to log to the table

private:
    void setupUI();

    QListWidget *sensorListWidget;
    QTableWidget *logTableWidget;
    int sensorCount;
    QMap<QString, Sensor*> sensorMap;  // list of currently running sensors

private slots:
    void addSensor();
    void removeSensor();
    void simulateSensor();
};

#endif // MAINWINDOW_H
