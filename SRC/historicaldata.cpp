#include "historicaldata.h"

HistoricalData::HistoricalData()
{
    hourlyVariables_ = {
        "temperature_2m",
                "relative_humidity_2m",
                "dew_point_2m",
                "apparent_temperature",
                "precipitation",
                "rain",
                "snowfall",
                "snow_depth",
                "weather_code",
                "pressure_msl",
                "surface_pressure",
                "cloud_cover",
                "cloud_cover_low",
                "cloud_cover_mid",
                "cloud_cover_high",
                "et0_fao_evapotranspiration",
                "vapour_pressure_deficit",
                "wind_speed_10m",
                "wind_speed_100m",
                "wind_direction_10m",
                "wind_direction_100m",
                "wind_gusts_10m",
                "soil_temperature_0_to_7cm",
                "soil_temperature_7_to_28cm",
                "soil_temperature_28_to_100cm",
                "soil_temperature_100_to_255cm",
                "soil_moisture_0_to_7cm",
                "soil_moisture_7_to_28cm",
                "soil_moisture_28_to_100cm",
                "soil_moisture_100_to_255cm"
        };

    additionalVariables_ = {"is_day","sunshine_duration"};

    dailyVariables_ = {"weather_code",
                       "temperature_2m_max",
                       "temperature_2m_min",
                       "temperature_2m_mean",
                       "apparent_temperature_max",
                       "apparent_temperature_min",
                       "apparent_temperature_mean",
                       "sunrise",
                       "sunset",
                       "daylight_duration",
                       "sunshine_duration",
                       "precipitation_sum",
                       "rain_sum",
                       "snowfall_sum",
                       "precipitation_hours",
                       "wind_speed_10m_max",
                       "wind_gusts_10m_max",
                       "wind_direction_10m_dominant",
                       "shortwave_radiation_sum",
                       "et0_fao_evapotranspiration"
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

}




std::string HistoricalData::buildRequestURL() {
    std::string url = "https://archive-api.open-meteo.com/v1/archive?";
    url += "latitude=" + std::to_string(latitude_);
    url += "&longitude=" + std::to_string(longitude_);


    if (requestSettings_.getStartDate() != "" && requestSettings_.getEndDate() != ""){
        url += "&start_date=" + requestSettings_.getStartDate();
        url += "&end_date=" + requestSettings_.getEndDate();
    }
    url += "&timezone=" + requestSettings_.getTimeZone();
    url += "&temperature_unit=" + requestSettings_.getTemperatureUnit();
    url += "&windspeed_unit=" + requestSettings_.getWindSpeedUnit();
    url += "&precipitation_unit=" + requestSettings_.getPrecipitationUnit();
    url += "&timeformat=" + requestSettings_.getTimeFormat();
    url += "&models=" + requestSettings_.getReanalysisModel();

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





































//what does this class need to do ?
