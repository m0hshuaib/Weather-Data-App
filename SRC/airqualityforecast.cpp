#include "airqualityforecast.h"

AirQualityForecast::AirQualityForecast()
{
    hourlyVariables_ = {
        "pm10",
        "pm2_5",
        "carbon_monoxide",
        "nitrogen_dioxide",
        "sulphur_dioxide",
        "ozone",
        "aerosol_optical_depth",
        "dust",
        "uv_index",
        "uv_index_clear_sky",
        "ammonia",
        "alder_pollen",
        "birch_pollen",
        "grass_pollen",
        "mugwort_pollen",
        "olive_pollen",
        "ragweed_pollen"
        };

    currentAirQualityVariables_ = {
        "european_aqi",
        "us_aqi","pm10",
        "pm2_5","carbon_monoxide",
        "nitrogen_dioxide",
        "sulphur_dioxide",
        "ozone",
        "aerosol_optical_depth",
        "dust",
        "uv_index",
        "uv_index_clear_sky",
        "ammonia",
        "alder_pollen",
        "birch_pollen",
        "grass_pollen",
        "mugwort_pollen",
        "olive_pollen",
        "ragweed_pollen"
        };

    europeanAirQualityIndexVariables_ = {
        "european_aqi","european_aqi_pm2_5","european_aqi_pm10","european_aqi_nitrogen_dioxide","european_aqi_ozone","european_aqi_sulphur_dioxide"

        };




}




std::string AirQualityForecast::buildRequestURL() {
    std::string url = "https://air-quality-api.open-meteo.com/v1/air-quality?";
    url += "latitude=" + std::to_string(latitude_);
    url += "&longitude=" + std::to_string(longitude_);


    if (requestSettings_.getStartDate() != "" && requestSettings_.getEndDate() != ""){
        url += "&start_date=" + requestSettings_.getStartDate();
        url += "&end_date=" + requestSettings_.getEndDate();
    }
    url += "&timezone=" + requestSettings_.getTimeZone();
    url += "&timeformat=" + requestSettings_.getTimeFormat();
    url += "&domains=" + requestSettings_.getAirQualityDomain();

    std::string hourlyVariables;
    if (!selectedHourlyVariables_.empty()) {
        for (const auto& variable : selectedHourlyVariables_) {
            hourlyVariables += variable + ",";
        }
        url += "&hourly=" + hourlyVariables;

    }

    std::string currentVariables;
    if (!selectedCurrentVariables_.empty()) {
        for (const auto& variable : selectedCurrentVariables_) {
            currentVariables += variable + ",";
        }
        url += "&current=" + currentVariables;
    }

    std::cout << url << std::endl;
    return url;
}

const std::vector<std::string> &AirQualityForecast::getEuropeanAirQualityIndexVariables() const
{
    return europeanAirQualityIndexVariables_;
}

const std::vector<std::string> &AirQualityForecast::getCurrentAirQualityVariables() const
{
    return currentAirQualityVariables_;
}

void AirQualityForecast::setSelectedCurrentVariables(const std::vector<std::string> &newSelectedCurrentVariables)
{
    selectedCurrentVariables_ = newSelectedCurrentVariables;
}
