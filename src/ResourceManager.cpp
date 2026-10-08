// Implements resource file loading, display, lookup, and availability updates.
#include "../include/ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

// Merge Sort helper functions for sorting resources by name.
namespace {

void mergeResources(
    std::vector<Resource>& resources,
    std::vector<Resource>& temp,
    int left,
    int mid,
    int right) {

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {

        if (resources[i].getName() <=
            resources[j].getName()) {

            temp[k] = resources[i];
            i++;
        }
        else {
            temp[k] = resources[j];
            j++;
        }

        k++;
    }

    while (i <= mid) {
        temp[k] = resources[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = resources[j];
        j++;
        k++;
    }

    for (int index = left; index <= right; index++) {
        resources[index] = temp[index];
    }
}

void mergeSortResources(
    std::vector<Resource>& resources,
    std::vector<Resource>& temp,
    int left,
    int right) {

    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSortResources(resources, temp, left, mid);
    mergeSortResources(resources, temp, mid + 1, right);

    mergeResources(resources, temp, left, mid, right);
}

} // End anonymous namespace


// Sort all resources alphabetically using Merge Sort.
void ResourceManager::sortResourcesByName() {

    if (resources.empty()) {
        std::cout << "\nNo resources available to sort.\n";
        return;
    }

    std::vector<Resource> temp = resources;

    mergeSortResources(
        resources,
        temp,
        0,
        static_cast<int>(resources.size()) - 1
    );

    std::cout << "\nResources sorted alphabetically by name.\n";

    displayResources();
}

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