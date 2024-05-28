#include "LocationManager.h"
#include "JSONParser.h"


Json::Value getJsonResponse(std::string apiUrl);

LocationManager::LocationManager()
{

}

void LocationManager::addLocation(const Location& location) {
    locations_.push_back(location);
}

void LocationManager::removeLocation(int id) {
    for(int i = 0; i < locations_.size(); i++) {
        if(locations_[i].getId() == id) {
            locations_.erase(locations_.begin() + i);
            saveLocations();
            break;
        }
    }
}

void LocationManager::updateLocation(int id, double lat, double lon) {
    for(Location& loc : locations_) {
        if(loc.getId() == id) {
            loc.setLatitude(lat);
            loc.setLongitude(lon);
            break;
        }
    }
}

std::vector<Location> LocationManager::getAllLocations() const {
    return locations_;
}

void LocationManager::setSelectedLocation(Location location)  {
    selectedLocation_ = location;
}

void LocationManager::updateSelectedLocationFavourite(bool favourite)  {
    selectedLocation_.setFavourite(favourite);
}

void LocationManager::updateSelectedLocationName(std::string name)  {
    selectedLocation_.setName(name);
}

void LocationManager::updateSelectedLocationLatitude(double lat)  {
    selectedLocation_.setLatitude(lat);
}

void LocationManager::updateSelectedLocationLongitude(double lon)  {
    selectedLocation_.setLongitude(lon);
}

Location LocationManager::getSelectedLocation()  {
   return selectedLocation_;
}

void LocationManager::saveLocations() {

  std::ofstream fout("locations.bin", std::ios::binary);

  if(!fout) {
    std::cerr << "Error opening locations file for writing" << std::endl;
    return;
  }

  int num_locations = locations_.size();
  fout.write((char*)&num_locations, sizeof(int));

  for (const auto& loc : locations_) {

    int id = loc.getId();
    fout.write((char*)&id, sizeof(int));

    std::string name = loc.getName();
    int name_length = name.size();
    fout.write((char*)&name_length, sizeof(int));
    fout.write(name.data(), name_length);

    double lat = loc.getLatitude();
    double lon = loc.getLongitude();
    bool fav = loc.isFavourite();

    fout.write((char*)&lat, sizeof(double));
    fout.write((char*)&lon, sizeof(double));
    fout.write((char*)&fav, sizeof(bool));
  }

  fout.close();
}

std::vector<Location> LocationManager::loadLocations() {

  //std::vector<Location> locations_;

  std::ifstream fin("locations.bin", std::ios::binary);
  if(!fin) {
    std::cerr << "Error opening locations file for reading" << std::endl;
    return {};
  }

  int num_locations;
  fin.read((char*)&num_locations, sizeof(int));

  for(int i = 0; i < num_locations; ++i) {

    Location loc;

    int id;
    fin.read((char*)&id, sizeof(int));
    loc.setId(id);

    int name_length;
    fin.read((char*)&name_length, sizeof(int));

    std::vector<char> name(name_length);
    fin.read(name.data(), name_length);
    loc.setName(std::string(name.begin(), name.end()));

    double lat;
    fin.read((char*)&lat, sizeof(double));
    loc.setLatitude(lat);

    double lon;
    fin.read((char*)&lon, sizeof(double));
    loc.setLongitude(lon);

    bool fav;
    fin.read((char*)&fav, sizeof(bool));
    loc.setFavourite(fav);

    locations_.push_back(loc);
  }

  fin.close();

  return locations_;
}

std::string LocationManager::retrieveLocationName(int lat, int lon) {
    std::string name;
    Json::Value jsonResponse_;

    try {
        jsonResponse_ = getJsonResponse("http://api.geonames.org/findNearbyPlaceNameJSON?lat=" + std::to_string(lat) + "&lng=" + std::to_string(lon) + "&username=t0401193");
        name = jsonResponse_["geonames"][0]["toponymName"].asString() + "-" + jsonResponse_["geonames"][0]["countryName"].asString();
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred while retrieving location name: " << e.what() << std::endl;
        name = "-"; // Set a default value or handle the error case appropriately
    }

    return name;
}

bool LocationManager::addNewLocation(int id, double lat, double lon, std::string backUpName) {
    std::string locationName = retrieveLocationName(lat, lon);

    if (locationName == "-"){
        locationName = backUpName;
    }

    Location newLocation(id, lat, lon, locationName);
    addLocation(newLocation);
    saveLocations();
}

bool LocationManager::uniqueID(int id) {
  for(const auto& loc : locations_) {
    if(loc.getId() == id) {
      return false;
    }
  }
  return true;
}

// Check if lat/lon combination is unique
bool LocationManager::uniqueLatLon(double lat, double lon) {
  for(const auto& loc : locations_) {
    if(loc.getLatitude() == lat &&
       loc.getLongitude() == lon) {
         return false;
    }
  }
  return true;
}

bool LocationManager::uniqueName(std::string name) {
  for(const auto& loc : locations_) {
    if(loc.getName() == name) {
      return false;
    }
  }
  return true;
}

std::vector<Location> LocationManager::getFavouriteLocations() {

    std::vector<Location> favouriteLocations;

     // Find favourite locations
     for(const auto& loc : locations_) {
       if(loc.isFavourite()) {
          favouriteLocations.push_back(loc);
       }
     }
     return favouriteLocations;
}

void LocationManager::updateSelectedLocation() {
  for(int i = 0; i < locations_.size(); i++) {
    if(locations_[i].getId() == selectedLocation_.getId()) {
      locations_[i] = selectedLocation_;
      break;
    }
  }

  saveLocations();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
