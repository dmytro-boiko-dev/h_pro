# QT Signals & Slots app

This app is an example of using Qt and signals system to send data between app components.

## Structure

~~~
/Root
├── CMakeLists.txt              # CMake configuration file
├── .gitignore                  # Git ignore file to exclude build and temporary files
├── main.cpp                    # Entry point of your application
├── Sensor.h                    # Header file for the Sensor class
├── Sensor.cpp                  # Implementation file for the Sensor class
├── Logger.h                    # Header file for the Logger class
├── Logger.cpp                  # Implementation file for the Logger class
├── Analyzer.h                  # Header file for the Analyzer class
├── Analyzer.cpp                # Implementation file for the Analyzer class
├── SensorMetric.h              # Header file defining the SensorMetric struct
└── Config.hpp                  # Header file containing static configuration values

~~~


### Build

to build the project from CLI run:
```
mkdir build
cd build
cmake ..
cmake --build .
```

---

Made with Qt 6.7.2 and Qt Creator 14.0.1  
https://www.qt.io
