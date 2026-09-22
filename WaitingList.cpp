#include "WaitingList.h"

#include <iostream>
#include <queue>
#include <stdexcept>


WaitingList::WaitingList() {
}


// Add a reservation request to the back of the FIFO queue
void WaitingList::addToList(const reservation& item) {
    waitingQueue.push(item);
}


// Remove the reservation at the front of the queue
void WaitingList::removeFromList() {

    if (!waitingQueue.empty()) {
        waitingQueue.pop();
    }
    else {
        std::cout << "Waiting list is empty." << std::endl;
    }
}


// Get the reservation at the front of the queue
reservation WaitingList::getFrontItem() const {

    if (waitingQueue.empty()) {
        throw std::runtime_error("Waiting list is empty.");
    }

    return waitingQueue.front();
}


// Check whether the waiting list is empty
bool WaitingList::isListEmpty() const {
    return waitingQueue.empty();
}


// Find and remove the FIRST person waiting
// for a particular resource.
//
// All other reservations remain in their
// original FIFO order.
bool WaitingList::getNextForResource(
    const std::string& resourceID,
    reservation& nextReservation) {

    std::queue<reservation> tempQueue;

    bool found = false;

    while (!waitingQueue.empty()) {

        reservation current =
            waitingQueue.front();

        waitingQueue.pop();

        // Take only the first matching reservation
        if (!found &&
            current.ResourceID == resourceID) {

            nextReservation = current;
            found = true;
        }
        else {

            // Keep all other reservations
            tempQueue.push(current);
        }
    }

    // Restore remaining reservations
    waitingQueue = tempQueue;

    return found;
}


// Display all reservations currently waiting
void WaitingList::displayList() const {

    if (waitingQueue.empty()) {

        std::cout
            << "Waiting list is empty."
            << std::endl;

        return;
    }

    // Copy the queue so displaying it does not
    // remove anything from the real waiting queue.
    std::queue<reservation> tempQueue =
        waitingQueue;

    std::cout
        << "\n===== Waiting List =====\n";

    while (!tempQueue.empty()) {

        reservation item =
            tempQueue.front();

        std::cout
            << "Reservation ID: "
            << item.ReservationID

            << " | Student ID: "
            << item.StudentID

            << " | Student Name: "
            << item.StudentName

            << " | Resource ID: "
            << item.ResourceID

            << " | Date: "
            << item.Date

            << '\n';

        tempQueue.pop();
    }
}