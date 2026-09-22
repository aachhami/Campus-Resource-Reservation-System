// Defines a campus resource and its ID, name, type, and availability information.
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
private:
    std::string resourceID;
    std::string name;
    std::string type;
    std::string availability;

public:
    Resource();
    Resource(const std::string& id,
             const std::string& resourceName,
             const std::string& resourceType,
             const std::string& status);

    std::string getResourceID() const;
    std::string getName() const;
    std::string getType() const;
    std::string getAvailability() const;

    void setAvailability(const std::string& status);
};

#endif