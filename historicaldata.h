#ifndef HISTORICALDATA_H
#define HISTORICALDATA_H

#include "WeatherForecastData.h"

class HistoricalData : public WeatherForecastData
{
public:
    HistoricalData();
    std::string buildRequestURL() override;
};

#endif // HISTORICALDATA_H
