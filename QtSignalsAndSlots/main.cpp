#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCommandLineParser>
#include <QProcessEnvironment>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QTimer>
#include "Sensor.h"
#include "Logger.h"
#include "Analyzer.h"

// load default config if none is found at the given path
void loadDefaultConfigIfNeeded(const QString& configPath) {
    if (!QFile::exists(configPath)) {
        qDebug() << "Config file not found at:" << configPath;
        QFile resourceFile(":/config.json");
        if (!resourceFile.open(QIODevice::ReadOnly)) {
            qDebug() << "Could not open default config from resources";
            return;
        }
        QFile outFile(configPath);
        if (outFile.open(QIODevice::WriteOnly)) {
            outFile.write(resourceFile.readAll());
            outFile.close();
            qDebug() << "Default config copied to:" << configPath;
        }
    }
}

// load configuration from the config file
QJsonObject loadConfig(const QString& configPath) {
    QFile file(configPath);
    if (!file.exists()) {
        qDebug() << "Config file does not exist:" << configPath;
        return {};
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open config file:" << configPath;
        return {};
    }

    QByteArray configData = file.readAll();
    QJsonParseError parseError;
    QJsonDocument configDoc = QJsonDocument::fromJson(configData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON parsing error:" << parseError.errorString();
        return {};
    }

    return configDoc.object();
}

// apply environment variables to the config
void applyEnvironmentVariables(QJsonObject& config) {
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    if (env.contains("SENSOR_INTERVAL")) {
        config["sensor_interval"] = env.value("SENSOR_INTERVAL").toInt();
    }
    if (env.contains("MAX_MEMORY_SIZE")) {
        config["max_memory_size"] = env.value("MAX_MEMORY_SIZE").toInt();
    }
    if (env.contains("LOG_FILE_PATH")) {
        config["log_file_path"] = env.value("LOG_FILE_PATH");
    }
}

// apply command line arguments to the config
void applyCommandLineArgs(QCommandLineParser& parser, QJsonObject& config) {
    if (parser.isSet("sensor-interval")) {
        config["sensor_interval"] = parser.value("sensor-interval").toInt();
    }
    if (parser.isSet("max-memory-size")) {
        config["max_memory_size"] = parser.value("max-memory-size").toInt();
    }
    if (parser.isSet("log-file-path")) {
        config["log_file_path"] = parser.value("log-file-path");
    }
}

int main(int argc, char *argv[]) {

    // create app loop
    QCoreApplication app(argc, argv);

    // command line parser setup
    QCommandLineParser parser;
    parser.setApplicationDescription("Sensor application with config support");
    parser.addHelpOption();

    // set command line options
    QCommandLineOption configFileOption(QStringList() << "c" << "config",
                                        QCoreApplication::translate("main", "Use the specified config file."),
                                        QCoreApplication::translate("main", "config"));
    parser.addOption(configFileOption);

    parser.addOption(QCommandLineOption("sensor-interval", "Set sensor interval", "milliseconds"));
    parser.addOption(QCommandLineOption("max-memory-size", "Set max memory size", "size"));
    parser.addOption(QCommandLineOption("log-file-path", "Set log file path", "path"));

    parser.process(app);

    // determine config path
    QString configPath;

    // 1. check if a config file path was provided as a command-line argument
    if (parser.isSet("config")) {
        configPath = parser.value("config");
        qDebug() << "Using config file from command line argument:" << configPath;
    } else {
        // use the path where the executable is located as the default
        configPath = QCoreApplication::applicationDirPath() + "/config.json";
        qDebug() << "Using default config path:" << configPath;
    }

    // 2. ensure config exists, load from resources if needed
    loadDefaultConfigIfNeeded(configPath);

    // load the configuration
    QJsonObject config = loadConfig(configPath);

    if (config.isEmpty()) {
        qDebug() << "Config file is empty or could not be loaded.";
    } else {
        qDebug() << "Config file loaded successfully.";
    }

    // apply environment variables
    applyEnvironmentVariables(config);

    // apply command line arguments
    applyCommandLineArgs(parser, config);

    // print the final configuration
    qDebug() << "Final Configuration:";
    qDebug().noquote() << QJsonDocument(config).toJson(QJsonDocument::Indented);

    // set up application components
    Sensor sensor;
    Logger logger;
    Analyzer analyzer(config.contains("max_memory_size") ? config["max_memory_size"].toInt() : 10000);

    // Use values from config, with fallback defaults if not present
    int sensorInterval = config.contains("sensor_interval") ? config["sensor_interval"].toInt() : 2000;  // fefault 2000ms
    int randomLimit = config.contains("random_limit") ? config["random_limit"].toInt() : 100;            // fefault random limit 100
    int printTimeout = config.contains("print_timeout") ? config["print_timeout"].toInt() : 10000;        // default 10 seconds

    // Connect signals and slots
    QObject::connect(&sensor, &Sensor::dataReady, &logger, &Logger::writeData);
    QObject::connect(&sensor, &Sensor::dataReady, &analyzer, &Analyzer::analyzeData);

    // timer to generate sensor data
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&sensor, randomLimit]() {
        int value = rand() % randomLimit; // generate random data based on config
        sensor.newData(value);
    });
    timer.start(sensorInterval); // renerate data every interval

    // print current data at print timeout
    QTimer::singleShot(printTimeout, [&analyzer]() {
        analyzer.reportPrint();
    });

    // start app
    return app.exec();
}
