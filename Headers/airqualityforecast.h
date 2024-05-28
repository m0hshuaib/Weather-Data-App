#ifndef AIRQUALITYFORECAST_H
#define AIRQUALITYFORECAST_H

#include "WeatherForecastData.h"

class AirQualityForecast: public WeatherForecastData
{
public:
    AirQualityForecast();
    std::string buildRequestURL() override;
    const std::vector<std::string> &getEuropeanAirQualityIndexVariables() const;
    const std::vector<std::string> &getCurrentAirQualityVariables() const;

    void setSelectedCurrentVariables(const std::vector<std::string> &newSelectedCurrentVariables);

private:
    std::vector<std::string> europeanAirQualityIndexVariables_;
    std::vector<std::string> currentAirQualityVariables_;
    std::vector<std::string> selectedCurrentVariables_;



};

#endif // AIRQUALITYFORECAST_H
