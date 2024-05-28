#ifndef WEATHERFORECASTDATA_H
#define WEATHERFORECASTDATA_H

#include <iostream>
#include <vector>
#include "settings.h"
#include "weatherdata.h"
#include <jsoncpp/json/json.h>

class WeatherForecastData : public WeatherData
{
public:
    WeatherForecastData();


    void setSelectedVariables(const std::vector<std::string>& variables) override;
    std::vector<std::string> getSelectedVariables() const override;
    std::string buildRequestURL() override;

    void setLatitude(double latitude) override;
    double getLatitude() const override;
    void setLongitude(double longitude) override;
    double getLongitude() const override;

    Json::Value fetchData() override;
    bool isDataLoaded() const override;

    void clearData() override;

    void setForecastDays(int days);
    int getForecastDays() const;

    void setWeatherModel(const std::string& model);
    std::string getWeatherModel() const;

    void setRequestSettings(settings weatherForecastSettings);
    std::vector<std::string> getHourlyVariables() const;

    std::vector<std::string> getAdditionalVariables() const;
    std::vector<std::string> getPressureLevelVariables() const;
    std::vector<std::string> getSolarRadiationVariables() const;
    const std::vector<std::string> &getDailyVariables() const;

    void setSelectedDailyVariables(const std::vector<std::string> &newSelectedDailyVariables);

protected:
    Json::Value forecastData_;
    std::vector<std::string> pressureLevelVariables_;
    std::vector<std::string> dailyVariables_;
    std::vector<std::string> selectedDailyVariables_;


};

#endif // WEATHERFORECASTDATA_H
