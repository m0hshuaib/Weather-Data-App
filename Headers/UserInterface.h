#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <jsoncpp/json/json.h>



class UserInterface
{
public:
    UserInterface();
    void print(const std::string& message);
    std::string getInput();
    void showMenu(const std::vector<std::string>& options);
    void clearConsole();
    void showtitle(const std::string& title);
    void printErr(const std::string& error);
    void enterToContinue();

    bool isNumber(const std::string &str);
    void showMenu(const std::vector<std::string> &options, std::string prompt, std::string bottomPrompt);
    std::vector<std::string> getSelectedVariables(std::vector<std::string> availableVariables);
    void displayData(Json::Value forecastData, std::vector<std::string> selectedVariables, bool isHourly) const;
    void displayCurrentAirQualityData(const Json::Value &airQualityData, const std::vector<std::string> &selectedVariables) const;
};

#endif // USERINTERFACE_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
