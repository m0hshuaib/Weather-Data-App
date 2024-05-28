TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -ljsoncpp -lcurl

SOURCES += \
        JSONParser.cpp \
        LocationManager.cpp \
        UserInterface.cpp \
        WeatherForecastData.cpp \
        airqualityforecast.cpp \
        exporter.cpp \
        historicaldata.cpp \
        location.cpp \
        main.cpp \
        settings.cpp \
        weatherapp.cpp

HEADERS += \
    JSONParser.h \
    LocationManager.h \
    UserInterface.h \
    WeatherForecastData.h \
    airqualityforecast.h \
    exporter.h \
    historicaldata.h \
    location.h \
    settings.h \
    weatherapp.h \
    weatherdata.h
