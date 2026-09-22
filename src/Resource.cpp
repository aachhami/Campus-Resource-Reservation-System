// Implements the Resource class constructors, accessors, and availability update operation.
#include "../include/Resource.h"

Resource::Resource()
    : resourceID(""), name(""), type(""), availability("") {
}

Resource::Resource(const std::string& id,
                   const std::string& resourceName,
                   const std::string& resourceType,
                   const std::string& status)
    : resourceID(id),
      name(resourceName),
      type(resourceType),
      availability(status) {
}

std::string Resource::getResourceID() const {
    return resourceID;
}

std::string Resource::getName() const {
    return name;
}

std::string Resource::getType() const {
    return type;
}

std::string Resource::getAvailability() const {
    return availability;
}

void Resource::setAvailability(const std::string& status) {
    availability = status;
}