#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H


#include "location.h"

class LocationManager : public Location {
public:
    LocationManager();

    void addLocation(const Location& location);
    void removeLocation(int id);
    void updateLocation(int id, double lat, double lon);
    void saveLocations();


    std::vector<Location> loadLocations();
    std::vector<Location> getAllLocations() const;//What does const mean here?
    std::string retrieveLocationName(int lat, int lon);


    bool addNewLocation(int id, double lat, double lon, std::string backUpName);
    bool uniqueName(std::string name);
    bool uniqueLatLon(double lat, double lon);
    bool uniqueID(int id);

    void setSelectedLocation(Location location);
    Location getSelectedLocation();
    std::vector<Location> getFavouriteLocations();
    void updateSelectedLocation();
    void updateSelectedLocationFavourite(bool favourite);
    void updateSelectedLocationName(std::string name);
    void updateSelectedLocationLatitude(double lat);
    void updateSelectedLocationLongitude(double lon);
private:
    std::vector<Location> locations_;
    Location selectedLocation_;
};


#endif // LOCATIONMANAGER_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
