#include "MainWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QProgressBar>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), sensorCount(0) {
    setupUI();
}

MainWindow::~MainWindow() {
    for (Sensor* sensor : sensorMap.values()) {
        delete sensor;
    }
}

void MainWindow::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Sensor List", this);
    sensorListWidget = new QListWidget(this);

    int sensorNameWidth = 128;
    int valueWidth = 64;
    int progressBarWidth = 256;

    logTableWidget = new QTableWidget(0, 3, this);  // 3 columns
    logTableWidget->setHorizontalHeaderLabels({"Sensor Name", "Value", "Progress"});
    logTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    logTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    logTableWidget->setColumnWidth(0, sensorNameWidth);
    logTableWidget->setColumnWidth(1, valueWidth);
    logTableWidget->setColumnWidth(2, progressBarWidth);

    // total window width
    int totalWidth = sensorNameWidth + valueWidth + progressBarWidth;
    int scrollbarWidth = 64; // blank space for skrollbar
    totalWidth += scrollbarWidth;

    setMinimumWidth(totalWidth);

    QPushButton *addButton = new QPushButton("Add Sensor", this);
    QPushButton *removeButton = new QPushButton("Remove Sensor", this);
    QPushButton *simulateButton = new QPushButton("Simulate", this);

    layout->addWidget(label);
    layout->addWidget(sensorListWidget);
    layout->addWidget(logTableWidget);
    layout->addWidget(addButton);
    layout->addWidget(removeButton);
    layout->addWidget(simulateButton);

    setLayout(layout);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addSensor);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeSensor);
    connect(simulateButton, &QPushButton::clicked, this, &MainWindow::simulateSensor);
}

void MainWindow::addSensor() {
    sensorCount++;
    QString sensorName = QString("Sensor %1").arg(sensorCount);

    Sensor *newSensor = new Sensor(sensorName);
    sensorMap.insert(sensorName, newSensor);

    sensorListWidget->addItem(sensorName);
    qDebug() << sensorName << "added and started.";

    // start the sensor with a timer
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [newSensor, this]() {
        int value = rand() % 100;  // random sensor data
        newSensor->newData(value);
        logToTable(newSensor->getName(), value);
    });
    timer->start(2000);  // trigger sensor data generationevery 2 seconds

    // store the timer in the sensor's QObject tree for auto-deletion
    newSensor->setParent(timer);
}

void MainWindow::removeSensor() {
    QListWidgetItem *selectedItem = sensorListWidget->currentItem();
    if (selectedItem) {
        QString sensorName = selectedItem->text();
        Sensor *sensorToRemove = sensorMap.value(sensorName);

        if (sensorToRemove) {
            sensorMap.remove(sensorName);

            // find and stop the associated timer before deleting the sensor
            QObject *parentTimer = sensorToRemove->parent();
            if (QTimer *timer = qobject_cast<QTimer*>(parentTimer)) {
                timer->stop();
                timer->deleteLater();
            }

            // schedule sensor deletion to ensure it's done safely
            sensorToRemove->deleteLater();
            qDebug() << sensorName << "stopped and removed.";
        }

        // remove the item from the  widget list
        delete selectedItem;

        if (sensorListWidget->count() == 0) {
            sensorCount = 0;
            qDebug() << "All sensors removed. Counter reset.";
        }
    } else {
        qDebug() << "No sensor selected for removal.";
    }
}

void MainWindow::logToTable(const QString &sensorName, int value) {

    int currentRow = logTableWidget->rowCount();
    logTableWidget->insertRow(currentRow);

    logTableWidget->setItem(currentRow, 0, new QTableWidgetItem(sensorName));
    logTableWidget->setItem(currentRow, 1, new QTableWidgetItem(QString::number(value)));

    QProgressBar *progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
    progressBar->setValue(value);

    // insert the progress bar into the 3rd column
    logTableWidget->setCellWidget(currentRow, 2, progressBar);

    // logTableWidget->resizeColumnsToContents();

    // autoscroll down
    logTableWidget->scrollToBottom();

    qDebug() << sensorName << "generated value" << value;
}


void MainWindow::simulateSensor() {
    qDebug() << "Simulation started...";
}
