// Defines resource inventory management using a vector of Resource objects.
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
#include <string>
#include "Resource.h"

class ResourceManager {
private:
    std::vector<Resource> resources;

public:
    bool loadResources(const std::string& filename);
    void displayResources() const;
    const std::vector<Resource>& getResources() const;
    void sortResourcesByName();
    Resource* findResource(const std::string& resourceID);
    bool updateAvailability(const std::string& resourceID,
                            const std::string& status);
};

#endif