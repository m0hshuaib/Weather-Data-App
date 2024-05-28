#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <jsoncpp/json/json.h>

class JSONParser
{
public:
    JSONParser();
    Json::Value parseJSON(const std::string& json);
};

#endif // JSONPARSER_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
