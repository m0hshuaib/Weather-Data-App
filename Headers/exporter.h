#ifndef EXPORTER_H
#define EXPORTER_H

#include <iostream>
#include <jsoncpp/json/json.h>

class Exporter
{
public:
    Exporter();
    void exportToJSON(const std::string& filename, Json::Value forecastData);
    void exportToCSV(const std::string &filename, Json::Value forecastData);
};

#endif // EXPORTER_H
