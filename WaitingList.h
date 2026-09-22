#pragma once

#include <queue>
#include <string>
#include "Reservation.h"

class WaitingList {
private:
    std::queue<reservation> waitingQueue;

public:
    WaitingList();

    // Add a reservation request to the back of the queue
    void addToList(const reservation& item);

    // Remove the reservation at the front of the queue
    void removeFromList();

    // Return the reservation at the front
    reservation getFrontItem() const;

    // Check whether the waiting list is empty
    bool isListEmpty() const;

    // Find and remove the first waiting reservation
    // for a specific resource
    bool getNextForResource(
        const std::string& resourceID,
        reservation& nextReservation
    );

    // Display all waiting reservations
    void displayList() const;
};