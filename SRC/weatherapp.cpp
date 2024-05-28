#include "weatherapp.h"
#include "UserInterface.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <cstdlib>



WeatherApp::WeatherApp() {

    startDateEntered_ = false;
    endDataEntered_ = false;
}


void WeatherApp::homePage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Use Weather Forecast System",
        "Use Historical Data System",
        "Use Air Quality Forecast System",
        "Manage Locations",
        "Quit"
      };

    while(!endLoop){
        ui.showtitle("EASY WEATHER: HOME");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)){
            switch (stoi(userInput)) {
              case 1:
                if (selectedLocationName_ != ""){
                    ui.clearConsole();
                    weatherForecastPage();
                    endLoop = true;
                } else {
                    ui.clearConsole();
                    ui.printErr("ERROR: Please select a location first");
                }
                break;
            case 2:
                if (selectedLocationName_ != ""){
                    ui.clearConsole();
                    historicalDataPage();
                    endLoop = true;
                } else {
                    ui.clearConsole();
                    ui.printErr("ERROR: Please select a location first");
                }
              break;
            case 3:
                if (selectedLocationName_ != ""){
                    ui.clearConsole();
                    airQualityForecastPage();
                    endLoop = true;
                } else {
                    ui.clearConsole();
                    ui.printErr("ERROR: Please select a location first");
                }
              break;
              case 4:
                ui.clearConsole();
                manageLocationsPage();
                endLoop = true;
                break;
              case 5:
                ui.print ("\nGoodbye !");
                endLoop = true;
                break;
              default:
                ui.clearConsole();
                ui.printErr("Error: Enter a valid option");
                break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option\n");
        }
    }
}


//________________________________________________________________START OF WEATHER FORECAST SYSTEM CODE


void WeatherApp::weatherForecastPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "View Hourly Forecast Data",
        "View Daily Data",
        "Change Data Settings",
        "Go Back"
      };

    while(!endLoop){
        ui.showtitle("EASY WEATHER: Weather Forecast System");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)){
            switch (stoi(userInput)) {
              case 1:
                ui.clearConsole();
                hourlyWeatherForecastPage();
                break;
              case 2:
                ui.clearConsole();
                dailyWeatherForecastPage();
                break;
              case 3:
                ui.clearConsole();
                weatherForecastSettingsPage();
                endLoop = true;
                break;
              case 4:
                ui.clearConsole();
                homePage();
                endLoop = true;
                break;
              default:
                ui.clearConsole();
                ui.printErr("Error: Enter a valid option");
                break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option\n");
        }
    }
}


void WeatherApp::hourlyWeatherForecastPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Select Hourly Variables",
        "Select Additional Variables",
        "Select Solar Radiation Variables",
        "Select Pressure Level Variables",
        "View Data",
        "Export Data",
        "Go Back"
    };


    // Set default settings
    weatherForecastData_.setLatitude(locationManager_.getSelectedLocation().getLatitude());
    weatherForecastData_.setLongitude(locationManager_.getSelectedLocation().getLongitude());

    std::vector<std::string> availableVariables;
    std::vector<std::string> selectedVariables;
    Json::Value forecastData;
    bool variablesSelected;


    while (!endLoop) {
        ui.showtitle("EASY WEATHER: Hourly Weather Forecast");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)) {
            switch (std::stoi(userInput)) {

                case 1:
                    availableVariables = weatherForecastData_.getHourlyVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    weatherForecastData_.setSelectedVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 2:
                    availableVariables = weatherForecastData_.getAdditionalVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    weatherForecastData_.setSelectedVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 3:
                    availableVariables = weatherForecastData_.getSolarRadiationVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    weatherForecastData_.setSelectedVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 4:
                    availableVariables = weatherForecastData_.getPressureLevelVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    weatherForecastData_.setSelectedVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 5:

                    if (variablesSelected){
                        forecastData = weatherForecastData_.fetchData();
                        ui.displayData(forecastData, selectedVariables, true);

                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 6:
                    if (variablesSelected) {
                        forecastData = weatherForecastData_.fetchData();
                        std::string filename;
                        ui.print("Enter filename for JSON export: ");
                        filename = ui.getInput()+ ".json";
                        exporter_.exportToJSON(filename, forecastData );

                        ui.print("Enter filename for CSV export: ");
                        filename = ui.getInput()+ ".csv";
                        exporter_.exportToCSV(filename, forecastData);
                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 7:
                    ui.clearConsole();
                    endLoop = true;
                    break;
                default:
                    ui.clearConsole();
                    ui.printErr("Error: Enter a valid option");
                    break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option");
        }
    }
}


void WeatherApp::dailyWeatherForecastPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Select Daily Variables",
        "View Data",
        "Export Data",
        "Go Back"
    };

    // Set default settings
    weatherForecastData_.setLatitude(locationManager_.getSelectedLocation().getLatitude());
    weatherForecastData_.setLongitude(locationManager_.getSelectedLocation().getLongitude());

    std::vector<std::string> availableVariables;
    std::vector<std::string> selectedVariables;
    Json::Value forecastData;
    bool variablesSelected;


    while (!endLoop) {
        ui.showtitle("EASY WEATHER: Daily Weather Data");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)) {
            switch (std::stoi(userInput)) {

                case 1:
                    availableVariables = weatherForecastData_.getDailyVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    weatherForecastData_.setSelectedDailyVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 2:

                    if (variablesSelected){
                        forecastData = weatherForecastData_.fetchData();
                        ui.displayData(forecastData, selectedVariables, false);

                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 3:
                    if (variablesSelected) {
                        forecastData = weatherForecastData_.fetchData();
                        std::string filename;
                        ui.print("Enter filename for JSON export: ");
                        filename = ui.getInput()+ ".json";
                        exporter_.exportToJSON(filename, forecastData );

                        ui.print("Enter filename for CSV export: ");
                        filename = ui.getInput()+ ".csv";
                        exporter_.exportToCSV(filename, forecastData);
                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 4:
                    ui.clearConsole();
                    endLoop = true;
                    break;
                default:
                    ui.clearConsole();
                    ui.printErr("Error: Enter a valid option");
                    break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option");
        }
    }
}



void WeatherApp::weatherForecastSettingsPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Temperature unit: " + weatherForecastSettings_.getTemperatureUnit(),
        "Wind Speed Unit: " + weatherForecastSettings_.getWindSpeedUnit(),
        "Precipitation Unit: " + weatherForecastSettings_.getPrecipitationUnit(),
        "Time Format: " + weatherForecastSettings_.getTimeFormat(),
        "Past Days: " + std::to_string(weatherForecastSettings_.getPastDays()),
        "Forecast Days: " + std::to_string(weatherForecastSettings_.getForecastDays()),
        "Time Zone: " + weatherForecastSettings_.getTimeZone(),
        "Weather Model: " + weatherForecastSettings_.getWeatherModel(),
        "Start Date: " + weatherForecastSettings_.getStartDate(),
        "End Date: " + weatherForecastSettings_.getEndDate(),
        "Save and Go Back"
      };

    while(!endLoop){
        ui.showtitle("EASY WEATHER: Weather Forecast Settings");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu, "Select a setting to change: \n", "You choose option: ");
        userInput = ui.getInput();

        if (ui.isNumber(userInput)){
            switch (stoi(userInput)) {
              case 1:
                while (true){
                    ui.print("Type (celsius) or (fahrenheit): ");
                    userInput = ui.getInput();
                    if (weatherForecastSettings_.setTemperatureUnit(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
                break;
              case 2:
                while (true){
                    ui.print("Type (kmh) or (ms) or (mph) or (kn): ");
                    userInput = ui.getInput();
                    if (weatherForecastSettings_.setWindSpeedUnit(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
                break;
              case 3:
                  while (true){
                      ui.print("Type (mm) or (inch): ");
                      userInput = ui.getInput();
                      if (weatherForecastSettings_.setPrecipitationUnit(userInput)){
                          ui.print("\nUpdated Successfully");
                          ui.enterToContinue();
                          ui.clearConsole();
                          break;
                      }
                      ui.printErr("Error: Enter a valid option\n");
                  }
              break;
            case 4:
                while (true){
                    ui.print("Type (iso8601) or (unixtime): ");
                    userInput = ui.getInput();
                    if (weatherForecastSettings_.setTimeFormat(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 5:
                while (true){
                    ui.print("Enter Number of Past Days: ");
                    userInput = ui.getInput();
                    if (ui.isNumber(userInput)){
                        if (stoi(userInput) <= 92) {
                            weatherForecastSettings_.setPastDays(stoi(userInput));
                            ui.print("\nUpdated Successfully");
                            ui.enterToContinue();
                            ui.clearConsole();
                            break;
                        }

                    }
                    ui.printErr("Error: Enter a digit that is less than 93\n");
                }
            break;
            case 6:
                while (true){
                    ui.print("Enter Number of Forecast Days: ");
                    userInput = ui.getInput();
                    if (ui.isNumber(userInput)){
                        if (stoi(userInput) <= 16) {
                            weatherForecastSettings_.setForecastDays(stoi(userInput));
                            ui.print("\nUpdated Successfully");
                            ui.enterToContinue();
                            ui.clearConsole();
                            break;
                        }

                    }
                    ui.printErr("Error: Enter a digit that is less than 17\n");
                }
            break;
            case 7:
                while (true){
                    ui.print("Enter a Timezone (e.g GMT): ");
                    userInput = ui.getInput();
                    if (weatherForecastSettings_.setTimeZone(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid Timezone\n");
                }
            break;
            case 8:
                while (true){
                    ui.print("Type (best_match) or (ecmwf_ifs04) or (gfs_global) or (gem_seamless): ");
                    userInput = ui.getInput();
                    if (weatherForecastSettings_.setWeatherModel(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 9:
                while (true){
                    ui.print("Enter a Date (yyyy-mm-dd): ");
                    userInput = ui.getInput();
                    if (weatherForecastSettings_.setStartDate(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 10:
                while (true){
                    ui.print("Enter a Date (yyyy-mm-dd): ");
                    userInput = ui.getInput();
                    if (weatherForecastSettings_.setEndDate(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 11:
                ui.clearConsole();
                weatherForecastData_.setRequestSettings(weatherForecastSettings_);
                weatherForecastPage();
                endLoop = true;
                break;
          default:
            // Code to be executed if expression doesn't match any case
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option");
            break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option\n");
        }
    }
}


//________________________________________________________________END OF WEATHER FORECAST SYSTEM CODE






//________________________________________________________________START OF HISTORICAL DATA SYSTEM CODE


void WeatherApp::historicalDataPage()
{
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "View Hourly Forecast Data",
        "View Daily Data",
        "Change Data Settings",
        "Go Back"
      };

    while(!endLoop){
        ui.showtitle("EASY WEATHER: Historical Data System");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)){
            switch (stoi(userInput)) {
              case 1:
                ui.clearConsole();
                if (startDateEntered_ && endDataEntered_){
                    hourlyHistoricalDataPage();
                }else{
                    ui.printErr("Error: Please select a start and end date first\n");
                }

                break;
              case 2:
                ui.clearConsole();
                if (startDateEntered_ && endDataEntered_){
                    dailyHistoricalDataPage();
                }else{
                    ui.printErr("Error: Please select a start and end date first\n");
                }
                break;
              case 3:
                ui.clearConsole();
                historicalDataSettingsPage();
                endLoop = true;
                break;
              case 4:
                ui.clearConsole();
                homePage();
                endLoop = true;
                break;
              default:
                ui.clearConsole();
                ui.printErr("Error: Enter a valid option");
                break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option\n");
        }
    }
}


void WeatherApp::hourlyHistoricalDataPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Select Hourly Variables",
        "Select Additional Variables",
        "Select Solar Radiation Variables",
        "View Data",
        "Export Data",
        "Go Back"
    };


    // Set default settings
    historicalData_.setLatitude(locationManager_.getSelectedLocation().getLatitude());
    historicalData_.setLongitude(locationManager_.getSelectedLocation().getLongitude());

    std::vector<std::string> availableVariables;
    std::vector<std::string> selectedVariables;
    Json::Value forecastData;
    bool variablesSelected;


    while (!endLoop) {
        ui.showtitle("EASY WEATHER: Hourly Historical Data");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)) {
            switch (std::stoi(userInput)) {

                case 1:
                    availableVariables = historicalData_.getHourlyVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    historicalData_.setSelectedVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 2:
                    availableVariables = historicalData_.getAdditionalVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    historicalData_.setSelectedVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 3:
                    availableVariables = historicalData_.getSolarRadiationVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    historicalData_.setSelectedVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 4:

                    if (variablesSelected){
                        forecastData = historicalData_.fetchData();
                        ui.displayData(forecastData, selectedVariables, true);

                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 5:
                    if (variablesSelected) {
                        forecastData = historicalData_.fetchData();
                        std::string filename;
                        ui.print("Enter filename for JSON export: ");
                        filename = ui.getInput()+ ".json";
                        exporter_.exportToJSON(filename, forecastData );

                        ui.print("Enter filename for CSV export: ");
                        filename = ui.getInput()+ ".csv";
                        exporter_.exportToCSV(filename, forecastData);
                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 6:
                    ui.clearConsole();
                    endLoop = true;
                    break;
                default:
                    ui.clearConsole();
                    ui.printErr("Error: Enter a valid option");
                    break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option");
        }
    }
}

void WeatherApp::historicalDataSettingsPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Temperature unit: " + historicalDataSettings_.getTemperatureUnit(),
        "Wind Speed Unit: " + historicalDataSettings_.getWindSpeedUnit(),
        "Precipitation Unit: " + historicalDataSettings_.getPrecipitationUnit(),
        "Time Format: " + historicalDataSettings_.getTimeFormat(),
        "Time Zone: " + historicalDataSettings_.getTimeZone(),
        "Reanalysis Model: " + historicalDataSettings_.getReanalysisModel(),
        "Start Date: " + historicalDataSettings_.getStartDate(),
        "End Date: " + historicalDataSettings_.getEndDate(),
        "Save and Go Back"
      };

    while(!endLoop){
        ui.showtitle("EASY WEATHER: Historical Data Settings");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu, "Select a setting to change: \n", "You choose option: ");
        userInput = ui.getInput();

        if (ui.isNumber(userInput)){
            switch (stoi(userInput)) {
              case 1:
                while (true){
                    ui.print("Type (celsius) or (fahrenheit): ");
                    userInput = ui.getInput();
                    if (historicalDataSettings_.setTemperatureUnit(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
                break;
              case 2:
                while (true){
                    ui.print("Type (kmh) or (ms) or (mph) or (kn): ");
                    userInput = ui.getInput();
                    if (historicalDataSettings_.setWindSpeedUnit(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
                break;
              case 3:
                  while (true){
                      ui.print("Type (mm) or (inch): ");
                      userInput = ui.getInput();
                      if (historicalDataSettings_.setPrecipitationUnit(userInput)){
                          ui.print("\nUpdated Successfully");
                          ui.enterToContinue();
                          ui.clearConsole();
                          break;
                      }
                      ui.printErr("Error: Enter a valid option\n");
                  }
              break;
            case 4:
                while (true){
                    ui.print("Type (iso8601) or (unixtime): ");
                    userInput = ui.getInput();
                    if (historicalDataSettings_.setTimeFormat(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 5:
                while (true){
                    ui.print("Enter a Timezone (e.g GMT): ");
                    userInput = ui.getInput();
                    if (historicalDataSettings_.setTimeZone(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid Timezone\n");
                }
            break;
            case 6:
                while (true){//best_match,ecmwf_ifs,era5_seamless,era5,era5_land,cerra
                    ui.print("Type (best_match) or (ecmwf_ifs) or (era5): ");
                    userInput = ui.getInput();
                    if (historicalDataSettings_.setReanalysisModel(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 7:
                while (true){
                    ui.print("Enter a Date (yyyy-mm-dd): ");
                    userInput = ui.getInput();
                    if (historicalDataSettings_.setStartDate(userInput)){
                        ui.print("\nUpdated Successfully");
                        startDateEntered_ = true;
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 8:
                while (true){
                    ui.print("Enter a Date (yyyy-mm-dd): ");
                    userInput = ui.getInput();
                    if (historicalDataSettings_.setEndDate(userInput)){
                        ui.print("\nUpdated Successfully");
                        endDataEntered_ = true;
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 9:
                ui.clearConsole();
                historicalData_.setRequestSettings(historicalDataSettings_);
                historicalDataPage();
                endLoop = true;
                break;
          default:
            // Code to be executed if expression doesn't match any case
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option");
            break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option\n");
        }
    }
}


void WeatherApp::dailyHistoricalDataPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Select Daily Variables",
        "View Data",
        "Export Data",
        "Go Back"
    };

    // Set default settings
    historicalData_.setLatitude(locationManager_.getSelectedLocation().getLatitude());
    historicalData_.setLongitude(locationManager_.getSelectedLocation().getLongitude());

    std::vector<std::string> availableVariables;
    std::vector<std::string> selectedVariables;
    Json::Value forecastData;
    bool variablesSelected;


    while (!endLoop) {
        ui.showtitle("EASY WEATHER: Daily Historical Data");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)) {
            switch (std::stoi(userInput)) {

                case 1:
                    availableVariables = historicalData_.getDailyVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    historicalData_.setSelectedDailyVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 2:

                    if (variablesSelected){
                        forecastData = historicalData_.fetchData();
                        ui.displayData(forecastData, selectedVariables, false);
                        //weatherForecastData_.displayData();

                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 3:
                    if (variablesSelected) {
                        forecastData = historicalData_.fetchData();
                        std::string filename;
                        ui.print("Enter filename for JSON export: ");
                        filename = ui.getInput()+ ".json";
                        exporter_.exportToJSON(filename, forecastData );

                        ui.print("Enter filename for CSV export: ");
                        filename = ui.getInput()+ ".csv";
                        exporter_.exportToCSV(filename, forecastData);
                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 4:
                    ui.clearConsole();
                    endLoop = true;
                    break;
                default:
                    ui.clearConsole();
                    ui.printErr("Error: Enter a valid option");
                    break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option");
        }
    }
}


//________________________________________________________________END OF HISTORICAL DATA SYSTEM CODE







//________________________________________________________________START OF AIR QUALITY FORECAST SYSTEM CODE


void WeatherApp::airQualityForecastPage()
{
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "View Hourly Forecast Data",
        "View Current Air Quality Forecast Data",
        "Change Data Settings",
        "Go Back"
      };

    while(!endLoop){
        ui.showtitle("EASY WEATHER: Air Quality Forecast System");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)){
            switch (stoi(userInput)) {
              case 1:
                // Code to be executed if expression is equal to value1
                ui.clearConsole();
                hourlyAirQualityForecastPage();

                break;
              case 2:
                // Code to be executed if expression is equal to value1
                ui.clearConsole();
                currentAirQualityDataPage();

                break;
              case 3:
                // Code to be executed if expression is equal to value2
                ui.clearConsole();
                airQualityForecastSettingsPage();
                endLoop = true;
                break;
              case 4:
                // Code to be executed if expression is equal to value2
                ui.clearConsole();
                homePage();
                endLoop = true;
                break;
              default:
                // Code to be executed if expression doesn't match any case
                ui.clearConsole();
                ui.printErr("Error: Enter a valid option");
                break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option\n");
        }
    }
}


void WeatherApp::hourlyAirQualityForecastPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Select Hourly Variables",
        "Select European Air Quality Index Variables",
        "View Data",
        "Export Data",
        "Go Back"
    };


    // Set default settings
    airQualityForecast_.setLatitude(locationManager_.getSelectedLocation().getLatitude());
    airQualityForecast_.setLongitude(locationManager_.getSelectedLocation().getLongitude());

    std::vector<std::string> availableVariables;
    std::vector<std::string> selectedVariables;
    Json::Value forecastData;
    bool variablesSelected;


    while (!endLoop) {
        ui.showtitle("EASY WEATHER: Hourly Air Quality Forecast");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)) {
            switch (std::stoi(userInput)) {

                case 1:
                    availableVariables = airQualityForecast_.getHourlyVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    airQualityForecast_.setSelectedVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 2:
                    availableVariables = airQualityForecast_.getEuropeanAirQualityIndexVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    airQualityForecast_.setSelectedVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 3:

                    if (variablesSelected){
                        forecastData = airQualityForecast_.fetchData();
                        ui.displayData(forecastData, selectedVariables, true);
                        //historicalData_.displayData();

                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 4:
                    if (variablesSelected) {
                        forecastData = airQualityForecast_.fetchData();
                        std::string filename;
                        ui.print("Enter filename for JSON export: ");
                        filename = ui.getInput()+ ".json";
                        //historicalData_.exportToJSON(filename + ".json");
                        exporter_.exportToJSON(filename, forecastData );

                        ui.print("Enter filename for CSV export: ");
                        filename = ui.getInput()+ ".csv";
                        //historicalData_.exportToCSV(filename + ".csv");
                        exporter_.exportToCSV(filename, forecastData);
                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 5:
                    ui.clearConsole();
                    endLoop = true;
                    break;
                default:
                    ui.clearConsole();
                    ui.printErr("Error: Enter a valid option");
                    break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option");
        }
    }
}

void WeatherApp::airQualityForecastSettingsPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Time Format: " + airQualityForecastSettings_.getTimeFormat(),
        "Time Zone: " + airQualityForecastSettings_.getTimeZone(),
        "Air Quality Domain: " + airQualityForecastSettings_.getAirQualityDomain(),
        "Start Date: " + airQualityForecastSettings_.getStartDate(),
        "End Date: " + airQualityForecastSettings_.getEndDate(),
        "Save and Go Back"
      };

    while(!endLoop){
        ui.showtitle("EASY WEATHER: Weather Forecast Settings");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu, "Select a setting to change: \n", "You choose option: ");
        userInput = ui.getInput();

        if (ui.isNumber(userInput)){
            switch (stoi(userInput)) {

            case 1:
                while (true){
                    ui.print("Type (iso8601) or (unixtime): ");
                    userInput = ui.getInput();
                    if (airQualityForecastSettings_.setTimeFormat(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 2:
                while (true){
                    ui.print("Enter a Timezone (e.g GMT): ");
                    userInput = ui.getInput();
                    if (airQualityForecastSettings_.setTimeZone(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid Timezone\n");
                }
            break;
            case 3:
                while (true){
                    ui.print("Type (cams_global) or (cams_europe): ");
                    userInput = ui.getInput();
                    if (airQualityForecastSettings_.setAirQualityDomain(userInput)){
                        ui.print("\nUpdated Successfully");
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 4:
                while (true){
                    ui.print("Enter a Date (yyyy-mm-dd): ");
                    userInput = ui.getInput();
                    if (airQualityForecastSettings_.setStartDate(userInput)){
                        ui.print("\nUpdated Successfully");
                        startDateEntered_ = true;
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 5:
                while (true){
                    ui.print("Enter a Date (yyyy-mm-dd): ");
                    userInput = ui.getInput();
                    if (airQualityForecastSettings_.setEndDate(userInput)){
                        ui.print("\nUpdated Successfully");
                        endDataEntered_ = true;
                        ui.enterToContinue();
                        ui.clearConsole();
                        break;
                    }
                    ui.printErr("Error: Enter a valid option\n");
                }
            break;
            case 6:
                ui.clearConsole();
                airQualityForecast_.setRequestSettings(airQualityForecastSettings_);
                airQualityForecastPage();
                endLoop = true;
                break;
          default:
            // Code to be executed if expression doesn't match any case
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option");
            break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option\n");
        }
    }
}


void WeatherApp::currentAirQualityDataPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Select Current Variables",
        "View Data",
        "Export Data",
        "Go Back"
    };

    // Set default settings
    airQualityForecast_.setLatitude(locationManager_.getSelectedLocation().getLatitude());
    airQualityForecast_.setLongitude(locationManager_.getSelectedLocation().getLongitude());

    std::vector<std::string> availableVariables;
    std::vector<std::string> selectedVariables;
    Json::Value forecastData;
    bool variablesSelected;


    while (!endLoop) {
        ui.showtitle("EASY WEATHER: Current Air Quality Forecast Data");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)) {
            switch (std::stoi(userInput)) {

                case 1:
                    availableVariables = airQualityForecast_.getCurrentAirQualityVariables();
                    selectedVariables = ui.getSelectedVariables(availableVariables);
                    airQualityForecast_.setSelectedCurrentVariables(selectedVariables);
                    variablesSelected = true;
                    ui.enterToContinue();
                    break;
                case 2:

                    if (variablesSelected){
                        forecastData = airQualityForecast_.fetchData();
                        ui.displayCurrentAirQualityData(forecastData, selectedVariables);
                        //weatherForecastData_.displayData();

                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 3:
                    if (variablesSelected) {
                        forecastData = airQualityForecast_.fetchData();
                        std::string filename;
                        ui.print("Enter filename for JSON export: ");
                        filename = ui.getInput()+ ".json";
                        exporter_.exportToJSON(filename, forecastData );

                        ui.print("Enter filename for CSV export: ");
                        filename = ui.getInput()+ ".csv";
                        exporter_.exportToCSV(filename, forecastData);
                    } else {
                        ui.clearConsole();
                        ui.printErr("Error: Please select variables first");
                    }
                    ui.enterToContinue();
                    break;
                case 4:
                    ui.clearConsole();
                    endLoop = true;
                    break;
                default:
                    ui.clearConsole();
                    ui.printErr("Error: Enter a valid option");
                    break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option");
        }
    }
}


//________________________________________________________________END OF AIR QUALITY FORECAST SYSTEM CODE






//________________________________________________________________START OF MANAGE LOCATIONS CODE
void WeatherApp::manageLocationsPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Select a favourite location",
        "Select other location",
        "Add new location",
        "Manage Selected location",
        "Go back"
      };

    while(!endLoop){
        ui.showtitle("EASY WEATHER: Manage Locations");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)){
            switch (stoi(userInput)) {
              case 1:
                // Code to be executed if expression is equal to value1
                ui.clearConsole();
                selectFavouriteLocationPage();
                break;
              case 2:
                // Code to be executed if expression is equal to value2
                ui.clearConsole();
                selectLocationPage();
                break;
              case 3:
                // Code to be executed if expression is equal to value2
                ui.clearConsole();
                addNewLocationPage();
                break;
              case 4:
                // Code to be executed if expression is equal to value2
                ui.clearConsole();
                if (selectedLocationName_ == ""){
                    ui.printErr("ERROR: Please select a location first\n");
                    break;
                }
                manageSelectedLocationPage();
                endLoop = true;
                break;
              case 5:
                // Code to be executed if expression is equal to value2
                ui.clearConsole();
                homePage();
                endLoop = true;
                break;
              default:
                // Code to be executed if expression doesn't match any case
                ui.clearConsole();
                ui.printErr("Error: Enter a valid option");
                break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option\n");
        }
    }
}


void WeatherApp::addNewLocationPage() {

    std::string userInput, userInput1, backUpName;
    double lat, lon;
    int id;
    bool endLoop = false;


    //Get valid id from user
    while(!endLoop){

        ui.showtitle("EASY WEATHER: Add New Location");
        ui.print("Enter a unique two-digit ID: ");
        userInput = ui.getInput();


        if (ui.isNumber(userInput) && userInput.size() == 2 && locationManager_.uniqueID(stoi(userInput))){
            id = stoi(userInput);
            ui.print("Id saved: " + userInput + "\n");
            endLoop = true;
            }

         else {
            ui.clearConsole();
            ui.printErr("Error: ID Already Taken or Invalid\n");
        }
    }

    ui.clearConsole();
    endLoop = false;


    //Get valid lat-lon pair from user
    while(!endLoop){

        ui.showtitle("EASY WEATHER: Add New Location");
        ui.print("Enter Latitude: ");
        userInput = ui.getInput();
        ui.print("\nEnter Longitude: ");
        userInput1 = ui.getInput();

          bool isValid = true;

          if(ui.isNumber(userInput) && ui.isNumber(userInput1)){
              lat = stod(userInput);
              lon = stod(userInput1);

            if(lat >= -90 && lat <= 90 && lon >= -180 && lon <= 180 && locationManager_.uniqueLatLon(lat, lon)){
                endLoop = true;
            }
            else{
              isValid = false;
            }

          } else {
            isValid = false;
          }

          if(!isValid) {
              ui.clearConsole();
              ui.printErr("Error: Latidude and Longitude Already Used or Invalid\n");
          }
    }

    ui.clearConsole();
    endLoop = false;


    //Get valid back-up location name from user
    while(!endLoop){

          ui.showtitle("EASY WEATHER: Add New Location");
          ui.print("Enter a back-up location name: ");
          userInput = ui.getInput();


        bool isValid = true;

        if(userInput.size() <= 15 && locationManager_.uniqueName(userInput)){
            backUpName = userInput;
            endLoop = true;

        } else {
          isValid = false;
        }

        if(!isValid) {
            ui.clearConsole();
            ui.printErr("Error: Name already used or longer than 15 charachters\n");
        }

    }

    locationManager_.addNewLocation( id,  lat,  lon, backUpName);
    ui.print("New location added:\nName: " + locationManager_.retrieveLocationName(lat,lon) + "\nID: " + std::to_string(id) + "\n");
    ui.enterToContinue();

}


void WeatherApp::selectFavouriteLocationPage() {

  ui.showtitle("EASY WEATHER: Select a favourite location");
  std::vector<Location> favourites;
  favourites = locationManager_.getFavouriteLocations();


  if(favourites.size() == 0) {
    ui.print("No favourite locations found!");
    ui.enterToContinue();
    return;
  }

  ui.print("Favourite Locations:\n");
  for(int i = 0; i < favourites.size(); i++) {
    ui.print(std::to_string(i+1) + ". " + favourites[i].getName() +
             " (ID: " + std::to_string(favourites[i].getId()) + ")\n");
  }

  bool selected = false;
  while(!selected) {
    ui.print("\nSelect a favourite location: ");
    std::string input = ui.getInput();

    if(ui.isNumber(input) &&
       stoi(input) > 0 && stoi(input) <= favourites.size()) {

      locationManager_.setSelectedLocation(favourites[stoi(input)-1]);
      selected = true;
    }
    else {
      ui.printErr("Invalid selection!");
    }
  }

  selectedLocationName_ = locationManager_.getSelectedLocation().getName();
  ui.print("\nSelected: " + selectedLocationName_ + "\n");
  ui.enterToContinue();
}




void WeatherApp::selectLocationPage() {

      ui.showtitle("EASY WEATHER: Select a location");
      std::string input;
      ui.print("Enter location ID or name: ");
      input = ui.getInput();

      std::vector<Location> matches;

      // Find matches
      for(const auto& loc : locationManager_.getAllLocations()) {
        if(std::to_string(loc.getId()).find(input) != std::string::npos ||
           loc.getName().find(input) != std::string::npos) {
             matches.push_back(loc);
        }
      }

      if(matches.size() == 0) {
        ui.printErr("No matching locations found!");
        return;
      }

      // Display matches
      ui.print("\n\nMatching Locations:\n\n");
      for(int i = 0; i < matches.size(); i++) {
        ui.print(std::to_string(i+1) + ". " + matches[i].getName() + " (ID: " +
                 std::to_string(matches[i].getId()) + ")" + "\n");
      }

      bool selected = false;
      while(!selected) {
        ui.print("\n\nSelect a location: ");
        input = ui.getInput();

        if(ui.isNumber(input) && stoi(input) > 0 && stoi(input) <= matches.size()) {
          locationManager_.setSelectedLocation(matches[stoi(input)-1]); //sets selected location to location selected by user
          selected = true;
        }
        else {
          ui.printErr("Invalid selection!");
        }
      }

      selectedLocationName_ = locationManager_.getSelectedLocation().getName();
      ui.print("Selected: " + selectedLocationName_ + "\n");
      ui.enterToContinue();
    }



void WeatherApp::manageSelectedLocationPage() {
    std::string userInput;
    bool endLoop = false;

    std::vector<std::string> mainMenu = {
        "Set location as favourite",
        "Remove location from favourite",
        "Update location data",
        "Delete location",
        "Go back"
      };

    while(!endLoop){
        ui.showtitle("EASY WEATHER: Manage Selected Location");
        ui.showtitle("Location: " + selectedLocationName_);
        ui.showMenu(mainMenu);
        userInput = ui.getInput();

        if (ui.isNumber(userInput)){
            switch (stoi(userInput)) {
              case 1:
                ui.clearConsole();
                updateSelectedLocationFavorite(true);
                ui.print("Location: " + selectedLocationName_ + " was set as a favorite!\n");
                ui.enterToContinue();
                break;
              case 2:
                ui.clearConsole();
                updateSelectedLocationFavorite(false);
                ui.print("Location: " + selectedLocationName_ + " was removed favorite!\n");
                ui.enterToContinue();
                break;
              case 3:
                ui.clearConsole();
                updateLocationDataPage();
                break;
              case 4:
                ui.clearConsole();
                deleteSelectedLocation();
                manageLocationsPage();
                endLoop = true;
                break;
              case 5:
                ui.clearConsole();
                manageLocationsPage();
                endLoop = true;
                break;
              default:
                ui.clearConsole();
                ui.printErr("Error: Enter a valid option");
                break;
            }
        } else {
            ui.clearConsole();
            ui.printErr("Error: Enter a valid option\n");
        }
    }
}


void WeatherApp::updateSelectedLocationFavorite(bool favourite) {

  // Set the favorite flag to true/false
  locationManager_.updateSelectedLocationFavourite(favourite);

  // Update selected location in the location manager
  locationManager_.updateSelectedLocation();

}


void WeatherApp::updateLocationDataPage() {


  bool endLoop = false;

  while(!endLoop) {

    ui.clearConsole();
    ui.showtitle("Update Location Data");

    std::vector<std::string> mainMenu = {
        "Update Name",
        "Update Latitude",
        "Update Longitude",
        "Save and Go Back"
      };
    ui.showMenu(mainMenu);

    std::string input = ui.getInput();

    if(ui.isNumber(input)) {

      switch(stoi(input)) {

        case 1:
          updateLocationName();
          break;

        case 2:
          updateLatitude();
          break;

        case 3:
          updateLongitude();
          break;

        case 4:
          locationManager_.updateSelectedLocation();
          endLoop = true;
          break;

        default:
          ui.printErr("Invalid option!");
      }
    }
    else {
      ui.printErr("Invalid input!");
    }
  }

  ui.print("Location updated!");
  ui.enterToContinue();
}

void WeatherApp::updateLocationName() {

  ui.print("Enter new name: ");
  std::string name = ui.getInput();

  if(name.size() <= 30 && locationManager_.uniqueName(name)) {
    locationManager_.updateSelectedLocationName(name);
    selectedLocationName_ = name;
    ui.print("Name updated!\n");
    ui.enterToContinue();
  }
  else {
    ui.printErr("Invalid name!");
  }
}

void WeatherApp::updateLatitude() {

  // Get valid latitude
  double lat;
  bool isValid;

  do {
    ui.print("Enter new latitude: ");
    std::string input = ui.getInput();

    isValid = true;

    if(ui.isNumber(input)) {
     lat = stod(input);

     if(lat < -90 || lat > 90) {
       isValid = false;
     }

    } else {
     isValid = false;
    }

    if(!isValid) {
     ui.printErr("Invalid latitude!");
    }

  } while(!isValid);

  // Check if new lat/lon pair is unique
  if(locationManager_.uniqueLatLon(lat, locationManager_.getSelectedLocation().getLongitude())) {
    locationManager_.updateSelectedLocationLatitude(lat);
    ui.print("latitude updated!\n");
    ui.enterToContinue();
  }
  else {
    ui.printErr("Latitude/Longitude pair already exists!");
  }
}

void WeatherApp::updateLongitude() {

  // Get valid longitude
  double lon;
  bool isValid;

  do {
    ui.print("Enter new longitude: ");
    std::string input = ui.getInput();

    isValid = true;

    if(ui.isNumber(input)) {
     lon = stod(input);

     if(lon < -180 || lon > 180) {
       isValid = false;
     }

    } else {
     isValid = false;
    }

    if(!isValid) {
     ui.printErr("Invalid longitude!");
    }

  } while(!isValid);

  // Check if new lat/lon pair is unique
  if(locationManager_.uniqueLatLon(locationManager_.getSelectedLocation().getLongitude(), lon)) {
    locationManager_.updateSelectedLocationLongitude(lon);
    ui.print("longitude updated!\n");
    ui.enterToContinue();
  }
  else {
    ui.printErr("Latitude/Longitude pair already exists!");
  }
}


void WeatherApp::deleteSelectedLocation() {

  Location selected = locationManager_.getSelectedLocation();
   ui.showtitle("EASY WEATHER: Delete Selected Location");

  ui.print("\nAre you sure you want to delete location: " +
           selectedLocationName_ + " (y/n)?");

  std::string confirmation = ui.getInput();

  if(confirmation == "y") {

    ui.print("Deleting location...");

    int id = selected.getId();
    locationManager_.removeLocation(id);
    selectedLocationName_ = "";

    ui.print("Location deleted successfully!");

  } else {
    ui.print("\nDelete cancelled");
  }

  ui.enterToContinue();
}
//________________________________________________________________END OF MANAGE LOCATIONS CODE



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
