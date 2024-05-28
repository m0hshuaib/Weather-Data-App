#ifndef WEATHERAPP_H
#define WEATHERAPP_H

#include "location.h"
#include "LocationManager.h"
#include "WeatherForecastData.h"
#include "historicaldata.h"
#include "airqualityforecast.h"
#include "UserInterface.h"
#include "exporter.h"
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <string>
#include <vector>

class WeatherApp
{
public:
    WeatherApp();
    virtual void homePage();
    void manageLocationsPage();
    void addNewLocationPage();
    void selectLocationPage();
    void manageSelectedLocationPage();
    void selectFavouriteLocationPage();
    void updateSelectedLocationFavorite(bool favourite);
    void updateLocationName();
    void updateLatitude();
    void updateLongitude();
    void updateLocationDataPage();
    void deleteSelectedLocation();
    void weatherForecastPage();
    void hourlyWeatherForecastPage();
    void weatherForecastSettingsPage();
    void dailyWeatherForecastPage();
    void historicalDataPage();
    void hourlyHistoricalDataPage();
    void historicalDataSettingsPage();
    void dailyHistoricalDataPage();
    void airQualityForecastPage();
    void hourlyAirQualityForecastPage();
    void airQualityForecastSettingsPage();
    void currentAirQualityDataPage();
private:
    UserInterface ui;
    LocationManager locationManager_;
    std::string selectedLocationName_;
    WeatherForecastData weatherForecast_;
    AirQualityForecast airQualityForecast_;
    settings weatherForecastSettings_;
    settings historicalDataSettings_;
    settings airQualityForecastSettings_;

    //settings historicalDataSettings_;
    //settings airQualityForecastSettings_;
    WeatherForecastData weatherForecastData_;
    HistoricalData historicalData_;
    Exporter exporter_;
    bool startDateEntered_;
    bool endDataEntered_;
};
Json::Value getJsonResponse(std::string apiUrl);

#endif // WEATHERAPP_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
