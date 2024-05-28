#include "UserInterface.h"



UserInterface::UserInterface()
{

}

void UserInterface::print(const std::string& message) {
  std::cout << message;
}

std::string UserInterface::getInput() {
  std::string input;
  std::getline(std::cin, input);
  return input;
}

void UserInterface::showMenu(const std::vector<std::string>& options) {

    std::cout << "What would you like to do:\n";
    for (int i = 0; i < options.size(); ++i) {
      std::cout << i + 1 << ". " << options[i] << "\n";
    }
    print("\nYou choose option: ");
}

void UserInterface::showMenu(const std::vector<std::string>& options, std::string prompt, std::string bottomPrompt ) {

    print(prompt + "\n");
    for (int i = 0; i < options.size(); ++i) {
      std::cout << i + 1 << ". " << options[i] << "\n";
    }
    print("\n" + bottomPrompt);
}

void UserInterface::clearConsole() {
  std::system("clear");
}

void UserInterface::showtitle(const std::string& title) {
    int consoleWidth = 80; // determine console width
    //std::string title = "Weather Data Application";
    int padding = (consoleWidth - title.length()) / 2;
    std::cout << "\033[1;31m"; // Set color to bold red
    std::cout << std::setw(padding) << "" << title << std::endl;
    std::cout << "\033[0m"; // Reset color
}

void UserInterface::printErr(const std::string& error) {
    std::cout << "\033[1;31m"; // Set color to bold red
    std::cout << error << std::endl;
    std::cout << "\033[0m"; // Reset color
}

void UserInterface::enterToContinue() {
    print ("\nHit ENTER to Continue");
    getInput();
    clearConsole();
}

bool UserInterface::isNumber(const std::string& str) {
  try {
    std::stoi(str); // Attempt conversion
    return true;
  } catch (const std::invalid_argument& e) {
    return false; // Conversion failed, not a number
  } catch (const std::out_of_range& e) {
    return false; // Out of integer range, not a number
  }
}

std::vector<std::string> UserInterface::getSelectedVariables(std::vector<std::string> availableVariables){
    print ("Available hourly variables:\n");
    for (int i = 0; i < availableVariables.size(); i++) {
        std::cout << i + 1 << ". " << availableVariables[i] << std::endl;
    }

    std::string selectedIndices;
    print ("Enter the indices of the variables you want to select (comma-separated): ");
    selectedIndices = getInput();

    std::vector<std::string>  selectedVariables;
    std::stringstream ss(selectedIndices);
    std::string index;
    while (getline(ss, index, ',')) {
        int i = stoi(index) - 1;
        if (i >= 0 && i < availableVariables.size()) {
            selectedVariables.push_back(availableVariables[i]);
        }
    }
    return selectedVariables;
}


//Old display datafunctions used to be here

void UserInterface::displayData(Json::Value forecastData, std::vector<std::string> selectedVariables, bool isHourly) const {
    std::cout << "Weather Forecast Data:" << std::endl;
    std::cout << "Latitude : " << std::fixed << std::setprecision(3) << forecastData["latitude"].asDouble() << std::endl;
    std::cout << "Longitude: " << std::fixed << std::setprecision(3) << forecastData["longitude"].asDouble() << std::endl;
    std::cout << std::endl;

    std::string dataType = isHourly ? "Hourly" : "Daily";
    std::string timeLabel = isHourly ? "Time" : "Date";
    std::string dataKey = isHourly ? "hourly" : "daily";

    std::cout << dataType << " Data:" << std::endl;

    const size_t maxVariablesPerTable = 4;
    const size_t numTables = (selectedVariables.size() + maxVariablesPerTable - 1) / maxVariablesPerTable;

    for (size_t tableIndex = 0; tableIndex < numTables; ++tableIndex) {
        const size_t startIndex = tableIndex * maxVariablesPerTable;
        const size_t endIndex = std::min(startIndex + maxVariablesPerTable, selectedVariables.size());
        const auto tableVariables = std::vector<std::string>(selectedVariables.begin() + startIndex, selectedVariables.begin() + endIndex);

        // Print table header
        std::cout << "+-----------------------+";
        for (const auto& variable : tableVariables) {
            std::cout << "--------------------------+";
        }
        std::cout << std::endl;

        std::cout << "| " << std::left << std::setw(21) << timeLabel << " |";
        for (const auto& variable : tableVariables) {
            std::cout << " " << std::left << std::setw(24) << variable << " |";
        }
        std::cout << std::endl;

        std::cout << "+-----------------------+";
        for (const auto& variable : tableVariables) {
            std::cout << "--------------------------+";
        }
        std::cout << std::endl;

        // Print table data
        const auto& data = forecastData[dataKey];
        for (size_t i = 0; i < data["time"].size(); ++i) {
            std::cout << "| " << std::left << std::setw(21) << data["time"].get(i, Json::Value::null).asString() << " |";
            for (const auto& variable : tableVariables) {
                std::cout << " " << std::right << std::setw(23);
                if (data[variable].get(i, Json::Value::null).isDouble()) {
                    std::cout << std::fixed << std::setprecision(3) << data[variable].get(i, Json::Value::null).asDouble();
                } else {
                    std::cout << data[variable].get(i, Json::Value::null).asString();
                }
                std::cout << " |";
            }
            std::cout << std::endl;
        }

        std::cout << "+-----------------------+";
        for (const auto& variable : tableVariables) {
            std::cout << "--------------------------+";
        }
        std::cout << std::endl << std::endl;
    }
}


void UserInterface::displayCurrentAirQualityData(const Json::Value& airQualityData, const std::vector<std::string>& selectedVariables) const {
    std::cout << "Current Air Quality Data:" << std::endl;

    std::cout << "Latitude : " << std::fixed << std::setprecision(3) << airQualityData["latitude"].asDouble() << std::endl;
    std::cout << "Longitude: " << std::fixed << std::setprecision(3) << airQualityData["longitude"].asDouble() << std::endl;
    std::cout << std::endl;

    std::cout << "Current Data:" << std::endl;

    const auto& currentData = airQualityData["current"];

    // Print table header
    std::cout << "+-----------------------+";
    for (const auto& variable : selectedVariables) {
        std::cout << "--------------------------+";
    }
    std::cout << std::endl;

    std::cout << "| " << std::left << std::setw(21) << "Time" << " |";
    for (const auto& variable : selectedVariables) {
        std::cout << " " << std::left << std::setw(24) << variable << " |";
    }
    std::cout << std::endl;

    std::cout << "+-----------------------+";
    for (const auto& variable : selectedVariables) {
        std::cout << "--------------------------+";
    }
    std::cout << std::endl;

    // Print table data
    std::cout << "| " << std::left << std::setw(21) << currentData["time"].asString() << " |";
    for (const auto& variable : selectedVariables) {
        std::cout << " " << std::right << std::setw(23);
        if (currentData[variable].isDouble()) {
            std::cout << std::fixed << std::setprecision(1) << currentData[variable].asDouble();
        } else {
            std::cout << currentData[variable].asInt();
        }
        std::cout << " |";
    }
    std::cout << std::endl;

    std::cout << "+-----------------------+";
    for (const auto& variable : selectedVariables) {
        std::cout << "--------------------------+";
    }
    std::cout << std::endl;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
























