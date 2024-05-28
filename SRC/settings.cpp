#include "settings.h"

settings::settings()
{
    temperatureUnit = "celsius";
    temperatureUnits = {"celsius", "fahrenheit"};

    windSpeedUnit = "kmh";
    windSpeedUnits = {"kmh", "ms", "mph", "kn"};

    precipitationUnit = "mm";
    precipitationUnits = {"mm", "inch"};

    timeFormat = "iso8601";
    timeFormats = {"iso8601", "unixtime"};

    pastDays = 0; // maximum is 92
    forecastDays = 1; // maximum is 16

    startDate = ""; // yyyy-mm-dd
    endDate = "";

    timeZone = "GMT";
    timeZones = {
        "UTC", "GMT", "EST", "EDT", "CST", "CDT", "MST", "MDT", "PST", "PDT",
        "AKST", "AKDT", "HST", "HAST", "HADT", "SST", "SDT", "CHST", "AEST",
        "AEDT", "ACST", "ACDT", "AWST", "NZST", "NZDT", "IST", "CET", "CEST",
        "EET", "EEST", "MSK", "MSD", "JST", "KST", "HKT", "AWST", "WIB", "WIT",
        "WITA", "ICT", "IDT", "NPT", "IST", "PKT", "BST", "AFT", "IRDT", "IRST",
        "GET", "TJT", "UZT", "YEKT", "ORAT", "NOVT", "BTT", "KRAT", "MAGT", "SAKT",
        "VLAT", "YAKT", "CHOT", "ANAST", "ANAT", "IRKST", "IRKT", "ULAT", "HOVT",
        "HOVST", "KRAT", "NOVST", "OMST", "OMSST", "YEKST", "YEKT", "MMT", "WAST",
        "CAST", "CADT", "NCAST", "NCADT", "DAVT", "DDUT", "TFT", "SCT", "MVT", "MUT",
        "RET", "MHT", "MART", "SYOT", "VOST", "ALMT", "AQTT", "TMT", "GMT+1", "GMT+2",
        "GMT+3", "GMT+4", "GMT+5", "GMT+6", "GMT+7", "GMT+8", "GMT+9", "GMT+10",
        "GMT+11", "GMT+12", "GMT-1", "GMT-2", "GMT-3", "GMT-4", "GMT-5", "GMT-6",
        "GMT-7", "GMT-8", "GMT-9", "GMT-10", "GMT-11", "GMT-12"
    };

    weatherModel = "best_match";
    weatherModels = {"best_match", "ecmwf_ifs04", "gfs_global", "gem_seamless"};

    reanalysisModel = "best_match";
    reanalysisModels = {"best_match", "ecmwf_ifs", "era5"};

    airQualityDomain = "auto";
    airQualityDomains = {"auto", "cams_europe", "cams_global"};
}

std::string settings::getTemperatureUnit() {
    return temperatureUnit;
}

std::string settings::getWindSpeedUnit() {
    return windSpeedUnit;
}

std::string settings::getPrecipitationUnit() {
    return precipitationUnit;
}

std::string settings::getTimeFormat() {
    return timeFormat;
}

int settings::getPastDays() {
    return pastDays;
}

int settings::getForecastDays() {
    return forecastDays;
}

std::string settings::getStartDate() {
    return startDate;
}

std::string settings::getEndDate() {
    return endDate;
}

std::string settings::getTimeZone() {
    return timeZone;
}

std::string settings::getWeatherModel() {
    return weatherModel;
}

std::string settings::getReanalysisModel() {
    return reanalysisModel;
}

std::string settings::getAirQualityDomain() {
    return airQualityDomain;
}

bool settings::setTemperatureUnit(std::string unit) {
    if (std::find(temperatureUnits.begin(), temperatureUnits.end(), unit) != temperatureUnits.end()) {
        temperatureUnit = unit;
    } else {
        // Handle invalid unit
        return false;
    }
    return true;
}

bool settings::setWindSpeedUnit(std::string unit) {
    if (std::find(windSpeedUnits.begin(), windSpeedUnits.end(), unit) != windSpeedUnits.end()) {
        windSpeedUnit = unit;
    } else {
        // Handle invalid unit
        return false;
    }
    return true;
}

bool settings::setPrecipitationUnit(std::string unit) {
    if (std::find(precipitationUnits.begin(), precipitationUnits.end(), unit) != precipitationUnits.end()) {
        precipitationUnit = unit;
    } else {
        // Handle invalid unit
        return false;
    }
    return true;
}

bool settings::setTimeFormat(std::string format) {
    if (std::find(timeFormats.begin(), timeFormats.end(), format) != timeFormats.end()) {
        timeFormat = format;
    } else {
        // Handle invalid unit
        return false;
    }
    return true;
}

void settings::setPastDays(int days) {
    pastDays = std::clamp(days, 0, 92); // Clamp to allowed range
}

void settings::setForecastDays(int days) {
    forecastDays = std::clamp(days, 1, 16); // Clamp to allowed range
}

bool settings::setStartDate(std::string date) {
    // Validation for date format
    if (isValidDate(date)){
        startDate = date;
        return true;
    }
    return false;
}

bool settings::setEndDate(std::string date) {
    // Validation for date format
    if (isValidDate(date)){
        endDate = date;
        return true;
    }
    return false;
}

bool settings::setTimeZone(std::string zone) {
    if (std::find(timeZones.begin(), timeZones.end(), zone) != timeZones.end()) {
        timeZone = zone;
    } else {
        // Handle invalid zone
        return false;
    }
    return true;
}

bool settings::setWeatherModel(std::string model) {
    if (std::find(weatherModels.begin(), weatherModels.end(), model) != weatherModels.end()) {
        weatherModel = model;
    } else {
        // Handle invalid model
        return false;
    }
    return true;
}

bool settings::setReanalysisModel(std::string model) {
    if (std::find(reanalysisModels.begin(), reanalysisModels.end(), model) != reanalysisModels.end()) {
        reanalysisModel = model;
    } else {
        // Handle invalid model
        return false;
    }
    return true;
}

bool settings::setAirQualityDomain(std::string domain) {
    if (std::find(airQualityDomains.begin(), airQualityDomains.end(), domain) != airQualityDomains.end()) {
        airQualityDomain = domain;
    } else {
        // Handle invalid domain
        return false;
    }
    return true;
}

bool settings::isValidDate(std::string date){
    // Check for correct format (YYYY-MM-DD)
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false; // Invalid format
    }

    // Check year, month, and day components
    try {
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));

        // Ensure valid date values
        if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
            return false; // Invalid date
        }

        return true;
    } catch (std::invalid_argument&) {
        return false; // Invalid format (non-numeric characters)
    }
}

