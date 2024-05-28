#include "JSONParser.h"
#include <iostream>


JSONParser::JSONParser()
{
}

Json::Value JSONParser::parseJSON(const std::string& json) {
    Json::Value root;
    Json::Reader reader;

    try {
        bool parsingSuccessful = reader.parse(json, root);
        if (!parsingSuccessful) {
            throw std::runtime_error("JSON parsing failed");
        }
    } catch (const std::exception& e) {
        // Handle the exception
        std::cerr << "Error: " << e.what() << std::endl;
        root = Json::nullValue;
    }

    return root;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
