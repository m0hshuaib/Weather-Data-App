#include "WeatherForecastData.h"
#include "JSONParser.h"
#include <curl/curl.h>
#include <fstream>
#include <sstream>
#include <iomanip>

WeatherForecastData::WeatherForecastData() {
    dataLoaded_ = false;
    hourlyVariables_ = {
            "temperature_2m", "relativehumidity_2m", "dewpoint_2m", "apparent_temperature",
            "pressure_msl", "surface_pressure", "cloudcover", "cloudcover_low",
            "cloudcover_mid", "cloudcover_high", "windspeed_10m", "windspeed_80m",
            "windspeed_120m", "windspeed_180m", "winddirection_10m", "winddirection_80m",
            "winddirection_120m", "winddirection_180m", "windgusts_10m", "shortwave_radiation",
            "direct_radiation", "direct_normal_irradiance", "diffuse_radiation", "vapor_pressure_deficit",
            "cape", "evapotranspiration", "et0_fao_evapotranspiration", "precipitation",
            "snowfall", "rain", "showers", "weathercode",
            "snow_depth", "freezinglevel_height", "visibility", "soil_temperature_0cm",
            "soil_temperature_6cm", "soil_temperature_18cm", "soil_temperature_54cm", "soil_moisture_0_1cm",
            "soil_moisture_1_3cm", "soil_moisture_3_9cm", "soil_moisture_9_27cm", "soil_moisture_27_81cm"
        };

    additionalVariables_ = {"uv_index","uv_index_clear_sky","is_day","cape","freezing_level_height","sunshine_duration"};

    pressureLevelVariables_ = {
        "temperature_1000hPa", "temperature_975hPa", "temperature_950hPa", "temperature_925hPa",
        "temperature_900hPa", "temperature_850hPa", "temperature_800hPa", "temperature_700hPa",
        "temperature_600hPa", "temperature_500hPa", "temperature_400hPa", "temperature_300hPa",
        "temperature_250hPa", "temperature_200hPa", "temperature_150hPa", "temperature_100hPa",
        "temperature_70hPa", "temperature_50hPa", "temperature_30hPa",

        "relative_humidity_1000hPa", "relative_humidity_975hPa", "relative_humidity_950hPa",
        "relative_humidity_925hPa", "relative_humidity_900hPa", "relative_humidity_850hPa",
        "relative_humidity_800hPa", "relative_humidity_700hPa", "relative_humidity_600hPa",
        "relative_humidity_500hPa", "relative_humidity_400hPa", "relative_humidity_300hPa",
        "relative_humidity_250hPa", "relative_humidity_200hPa", "relative_humidity_150hPa",
        "relative_humidity_100hPa", "relative_humidity_70hPa", "relative_humidity_50hPa",
        "relative_humidity_30hPa",

        "dew_point_1000hPa", "dew_point_975hPa", "dew_point_950hPa", "dew_point_925hPa",
        "dew_point_900hPa", "dew_point_850hPa", "dew_point_800hPa", "dew_point_700hPa",
        "dew_point_600hPa", "dew_point_500hPa", "dew_point_400hPa", "dew_point_300hPa",
        "dew_point_250hPa", "dew_point_200hPa", "dew_point_150hPa", "dew_point_100hPa",
        "dew_point_70hPa", "dew_point_50hPa", "dew_point_30hPa",

        "cloud_cover_1000hPa", "cloud_cover_975hPa", "cloud_cover_950hPa", "cloud_cover_925hPa",
        "cloud_cover_900hPa", "cloud_cover_850hPa", "cloud_cover_800hPa", "cloud_cover_700hPa",
        "cloud_cover_600hPa", "cloud_cover_500hPa", "cloud_cover_400hPa", "cloud_cover_300hPa",
        "cloud_cover_250hPa", "cloud_cover_200hPa", "cloud_cover_150hPa", "cloud_cover_100hPa",
        "cloud_cover_70hPa", "cloud_cover_50hPa", "cloud_cover_30hPa",

        "wind_speed_1000hPa", "wind_speed_975hPa", "wind_speed_950hPa", "wind_speed_925hPa",
        "wind_speed_900hPa", "wind_speed_850hPa", "wind_speed_800hPa", "wind_speed_700hPa",
        "wind_speed_600hPa", "wind_speed_500hPa", "wind_speed_400hPa", "wind_speed_300hPa",
        "wind_speed_250hPa", "wind_speed_200hPa", "wind_speed_150hPa", "wind_speed_100hPa",
        "wind_speed_70hPa", "wind_speed_50hPa", "wind_speed_30hPa",

        "wind_direction_1000hPa", "wind_direction_975hPa", "wind_direction_950hPa", "wind_direction_925hPa",
        "wind_direction_900hPa", "wind_direction_850hPa", "wind_direction_800hPa", "wind_direction_700hPa",
        "wind_direction_600hPa", "wind_direction_500hPa", "wind_direction_400hPa", "wind_direction_300hPa",
        "wind_direction_250hPa", "wind_direction_200hPa", "wind_direction_150hPa", "wind_direction_100hPa",
        "wind_direction_70hPa", "wind_direction_50hPa", "wind_direction_30hPa",

        "geopotential_height_1000hPa", "geopotential_height_975hPa", "geopotential_height_950hPa",
        "geopotential_height_925hPa", "geopotential_height_900hPa", "geopotential_height_850hPa",
        "geopotential_height_800hPa", "geopotential_height_700hPa", "geopotential_height_600hPa",
        "geopotential_height_500hPa", "geopotential_height_400hPa", "geopotential_height_300hPa",
        "geopotential_height_250hPa", "geopotential_height_200hPa", "geopotential_height_150hPa",
        "geopotential_height_100hPa", "geopotential_height_70hPa", "geopotential_height_50hPa",
        "geopotential_height_30hPa"
    };

    solarRadiationVariables_ = {"shortwave_radiation",
                                "direct_radiation",
                                "diffuse_radiation",
                                "direct_normal_irradiance",
                                "global_tilted_irradiance",
                                "terrestrial_radiation",
                                "shortwave_radiation_instant",
                                "direct_radiation_instant",
                                "diffuse_radiation_instant",
                                "direct_normal_irradiance_instant",
                                "global_tilted_irradiance_instant",
                                "terrestrial_radiation_instant"};

    dailyVariables_ = {"weather_code",
                       "temperature_2m_max",
                       "temperature_2m_min",
                       "apparent_temperature_max",
                       "apparent_temperature_min",
                       "sunrise",
                       "sunset",
                       "daylight_duration",
                       "sunshine_duration",
                       "uv_index_max",
                       "uv_index_clear_sky_max",
                       "precipitation_sum",
                       "rain_sum",
                       "showers_sum",
                       "snowfall_sum",
                       "precipitation_hours",
                       "precipitation_probability_max",
                       "wind_speed_10m_max",
                       "wind_gusts_10m_max",
                       "wind_direction_10m_dominant",
                       "shortwave_radiation_sum",
                       "et0_fao_evapotranspiration"
                      };

}

void WeatherForecastData::setSelectedVariables(const std::vector<std::string>& variables) {
    selectedHourlyVariables_ = variables;
}

std::vector<std::string> WeatherForecastData::getSelectedVariables() const {
    return selectedHourlyVariables_;
}

std::vector<std::string> WeatherForecastData::getHourlyVariables() const {
    return hourlyVariables_;
}

std::vector<std::string> WeatherForecastData::getAdditionalVariables() const {
    return additionalVariables_;
}

std::vector<std::string> WeatherForecastData::getPressureLevelVariables() const {
    return pressureLevelVariables_;
}

std::vector<std::string> WeatherForecastData::getSolarRadiationVariables() const {
    return solarRadiationVariables_;
}

const std::vector<std::string> &WeatherForecastData::getDailyVariables() const
{
    return dailyVariables_;
}

void WeatherForecastData::setSelectedDailyVariables(const std::vector<std::string> &newSelectedDailyVariables)
{
    selectedDailyVariables_ = newSelectedDailyVariables;
}


std::string WeatherForecastData::buildRequestURL() {
    std::string url = "https://api.open-meteo.com/v1/forecast?";
    url += "latitude=" + std::to_string(latitude_);
    url += "&longitude=" + std::to_string(longitude_);

    std::string hourlyVariables;
    if (!selectedHourlyVariables_.empty()) {
        for (const auto& variable : selectedHourlyVariables_) {
            hourlyVariables += variable + ",";
        }
        url += "&hourly=" + hourlyVariables;

    }

    std::string dailyVariables;
    if (!selectedDailyVariables_.empty()) {
        for (const auto& variable : selectedDailyVariables_) {
            dailyVariables += variable + ",";
        }
        url += "&daily=" + dailyVariables;
    }

    std::cout << url << std::endl;
    return url;
}

void WeatherForecastData::setLatitude(double latitude) {
    latitude_ = latitude;
}

double WeatherForecastData::getLatitude() const {
    return latitude_;
}

void WeatherForecastData::setLongitude(double longitude) {
    longitude_ = longitude;
}

double WeatherForecastData::getLongitude() const {
    return longitude_;
}

void WeatherForecastData::setRequestSettings(settings weatherForecastSettings) {
    requestSettings_ = weatherForecastSettings;
}


Json::Value WeatherForecastData::fetchData() {
    std::string url = buildRequestURL();
    forecastData_ = getJsonResponse(url);
    dataLoaded_ = true;

    return forecastData_;
}

bool WeatherForecastData::isDataLoaded() const {
    return dataLoaded_;
}

void WeatherForecastData::clearData() {
    forecastData_.clear();
    dataLoaded_ = false;
}
