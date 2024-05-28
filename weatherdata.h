#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <iostream>
#include <vector>
#include <jsoncpp/json/json.h>
#include "settings.h"

Json::Value getJsonResponse(std::string apiUrl);
class WeatherData
{
public:
    //WeatherData();
    virtual void setSelectedVariables(const std::vector<std::string>& variables) = 0;
    virtual std::vector<std::string> getSelectedVariables() const = 0;

    virtual void setLatitude(double latitude) = 0;
    virtual double getLatitude() const = 0;
    virtual void setLongitude(double longitude) = 0;
    virtual double getLongitude() const = 0;

    virtual Json::Value fetchData() = 0;
    virtual bool isDataLoaded() const = 0;
    virtual std::string buildRequestURL() = 0;

    virtual void clearData() = 0;

protected:
    std::vector<std::string> selectedHourlyVariables_;
    std::vector<std::string> hourlyVariables_;
    std::vector<std::string> additionalVariables_;
    std::vector<std::string> solarRadiationVariables_;

    double latitude_;
    double longitude_;
    bool dataLoaded_;
    settings requestSettings_;
};

#endif // WEATHERDATA_H
