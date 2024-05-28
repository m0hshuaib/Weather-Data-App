#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Location {
public:
    // Constructor
    Location(int id, double latitude, double longitude, std::string name);
    Location();

    // Getters
    int getId() const;
    const std::string& getName() const;
    double getLatitude() const;
    double getLongitude() const;
    bool isFavourite() const;

    // Setters
    void setName(const std::string& name);
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    void setFavourite(bool favourite);
    void setId(int id);
private:
    int id_;
    std::string name_;
    double latitude_;
    double longitude_;
    bool favourite_;
};

#endif // LOCATION_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
