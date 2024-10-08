cmake_minimum_required(VERSION 3.16)

project(QtSignalsAndSlots LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


# Add executable target
add_executable(QtSignalsAndSlots
    main.cpp
    Sensor.cpp
    Logger.cpp
    Analyzer.cpp
    Sensor.h
    Logger.h
    Analyzer.h
    SensorMetric.h
    Config.h
    README.md
    .gitignore
)

target_link_libraries(QtSignalsAndSlots Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS QtSignalsAndSlots
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


