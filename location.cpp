#include "location.h"

Location::Location(int id, double latitude, double longitude, std::string name) :
    id_(id),
    name_(name),
    latitude_(latitude),
    longitude_(longitude),
    favourite_(false) {}

Location::Location() : id_(0), name_(""), latitude_(0), longitude_(0), favourite_(false) {}

int Location::getId() const {
    return id_;
}

const std::string& Location::getName() const {
    return name_;
}

double Location::getLatitude() const {
    return latitude_;
}

double Location::getLongitude() const {
    return longitude_;
}

bool Location::isFavourite() const {
    return favourite_;
}

void Location::setName(const std::string& name) {
    name_ = name;
}

void Location::setLatitude(double latitude) {
    latitude_ = latitude;
}

void Location::setLongitude(double longitude) {
    longitude_ = longitude;
}

void Location::setFavourite(bool favourite) {
    favourite_ = favourite;
}

void Location::setId(int id) {
    id_ = id;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
