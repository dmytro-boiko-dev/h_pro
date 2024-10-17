#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>

class Logger : public QObject {
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

    Q_INVOKABLE void logToFile(const QString& input, const QString& result);
};

#endif // LOGGER_H
