#include "../include/ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

bool ResourceManager::loadResources(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error: Could not open resource file." << std::endl;
        return false;
    }

    resources.clear();

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        std::string id;
        std::string name;
        std::string type;
        std::string availability;

        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, type, '|');
        std::getline(ss, availability);

        Resource resource(id, name, type, availability);
        resources.push_back(resource);
    }

    file.close();
    return true;
}

void ResourceManager::displayResources() const {
    if (resources.empty()) {
        std::cout << "No resources available." << std::endl;
        return;
    }

    std::cout << "\n===== Resources =====\n";

    for (const Resource& resource : resources) {
        std::cout << "ID: " << resource.getResourceID()
                  << " | Name: " << resource.getName()
                  << " | Type: " << resource.getType()
                  << " | Status: " << resource.getAvailability()
                  << '\n';
    }
}

Resource* ResourceManager::findResource(const std::string& resourceID) {
    for (Resource& resource : resources) {
        if (resource.getResourceID() == resourceID) {
            return &resource;
        }
    }

    return nullptr;
}

bool ResourceManager::updateAvailability(
    const std::string& resourceID,
    const std::string& status) {

    Resource* resource = findResource(resourceID);

    if (resource == nullptr) {
        return false;
    }

    resource->setAvailability(status);
    return true;
}