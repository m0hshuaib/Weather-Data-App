                                                            #ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <vector>
#include <algorithm>


class settings
{
public:
    settings();

    // Getters (without const)
    std::string getTemperatureUnit();
    std::string getWindSpeedUnit();
    std::string getPrecipitationUnit();
    std::string getTimeFormat();
    int getPastDays();
    int getForecastDays();
    std::string getStartDate();
    std::string getEndDate();
    std::string getTimeZone();
    std::string getWeatherModel();
    std::string getReanalysisModel();
    std::string getAirQualityDomain();

    // Setters with validation
    bool setTemperatureUnit( std::string unit);
    bool setWindSpeedUnit( std::string unit);
    bool setPrecipitationUnit( std::string unit);
    bool setTimeFormat( std::string format);
    void setPastDays(int days);
    void setForecastDays(int days);
    bool setStartDate( std::string date);
    bool setEndDate( std::string date);
    bool setTimeZone( std::string zone);
    bool setWeatherModel( std::string model);
    bool setReanalysisModel( std::string model);
    bool setAirQualityDomain( std::string domain);

    bool isValidDate(std::string date);
private:
    std::string temperatureUnit;
    std::vector<std::string> temperatureUnits;

    std::string windSpeedUnit;
    std::vector<std::string> windSpeedUnits;

    std::string precipitationUnit;
    std::vector<std::string> precipitationUnits;

    std::string timeFormat;
    std::vector<std::string> timeFormats;

    int pastDays;
    int forecastDays;

    std::string startDate;
    std::string endDate;

    std::string timeZone;
    std::vector<std::string> timeZones;

    std::string weatherModel;
    std::vector<std::string> weatherModels;

    std::string reanalysisModel;
    std::vector<std::string> reanalysisModels;

    std::string airQualityDomain;
    std::vector<std::string> airQualityDomains;
};

#endif // SETTINGS_H
