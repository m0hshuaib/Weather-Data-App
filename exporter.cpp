#include "exporter.h"
#include <fstream>
#include <sstream>
#include <iomanip>

Exporter::Exporter()
{
}

void Exporter::exportToJSON(const std::string& filename, Json::Value forecastData) {
    try {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << forecastData.toStyledString();
            file.close();
            std::cout << "Data exported to " << filename << std::endl;
        } else {
            throw std::runtime_error("Unable to open file " + filename);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error exporting JSON: " << e.what() << std::endl;
    }
}

void Exporter::exportToCSV(const std::string& filename, Json::Value forecastData) {
    try {
        std::ofstream file(filename);
        if (file.is_open()) {
            const auto& hourlyData = forecastData["hourly"];

            // Write header
            file << "Time,";
            for (const auto& variable : hourlyData.getMemberNames()) {
                if (variable != "time") {
                    file << variable << ",";
                }
            }
            file << std::endl;

            // Write data
            for (size_t i = 0; i < hourlyData["time"].size(); ++i) {
                file << hourlyData["time"].get(i, Json::Value::null).asString() << ",";
                for (const auto& variable : hourlyData.getMemberNames()) {
                    if (variable != "time") {
                        file << std::fixed << std::setprecision(3) << hourlyData[variable].get(i, Json::Value::null).asDouble() << ",";
                    }
                }
                file << std::endl;
            }
            file.close();
            std::cout << "Data exported to " << filename << std::endl;
        } else {
            throw std::runtime_error("Unable to open file " + filename);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error exporting CSV: " << e.what() << std::endl;
    }
}
