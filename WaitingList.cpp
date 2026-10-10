// Implements FIFO waiting-list operations and automatic resource assignment processing.
#include "WaitingList.h"

#include <iostream>
#include <stdexcept>
#include <map>

WaitingList::WaitingList() {
}

void WaitingList::addToList(
    const reservation& item) {

    waitingQueue.push(item);
}

void WaitingList::addToFront(
    const reservation& item) {

    std::queue<reservation> temp;

    temp.push(item);

    std::queue<reservation> copy =
        waitingQueue;

    while (!copy.empty()) {

        temp.push(copy.front());

        copy.pop();
    }

    waitingQueue = temp;
}

void WaitingList::removeFromList() {

    if (waitingQueue.empty()) {

        std::cout
            << "Waiting list is empty.\n";

        return;
    }

    waitingQueue.pop();
}

reservation WaitingList::getFrontItem() const {

    if (waitingQueue.empty()) {

        throw std::runtime_error(
            "Waiting list is empty."
        );
    }

    return waitingQueue.front();
}

bool WaitingList::isListEmpty() const {

    return waitingQueue.empty();
}

bool WaitingList::containsReservationID(
    const std::string& reservationID) const {

    std::queue<reservation> temp =
        waitingQueue;

    while (!temp.empty()) {

        if (temp.front().ReservationID ==
            reservationID) {

            return true;
        }

        temp.pop();
    }

    return false;
}

bool WaitingList::getNextForResource(
    const std::string& resourceID,
    reservation& nextReservation) {

    std::queue<reservation> tempQueue;

    bool found = false;

    while (!waitingQueue.empty()) {

        reservation current =
            waitingQueue.front();

        waitingQueue.pop();

        if (!found &&
            current.ResourceID == resourceID) {

            nextReservation = current;

            found = true;
        }
        else {

            tempQueue.push(current);
        }
    }

    waitingQueue = tempQueue;

    return found;
}

void WaitingList::displayList() const {

    if (waitingQueue.empty()) {

        std::cout
            << "Waiting list is empty.\n";

        return;
    }

    std::queue<reservation> temp =
        waitingQueue;

    std::cout
        << "\n===== Waiting List =====\n";

    while (!temp.empty()) {

        const reservation& item =
            temp.front();

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

        temp.pop();
    }
}

// Reports the number of waiting requests for each resource.
// A copy of the queue preserves the original FIFO order.
void WaitingList::displayWaitingStatistics() const {

    std::queue<reservation> temp = waitingQueue;

    if (temp.empty()) {
        std::cout << "\nNo students are currently waiting.\n";
        return;
    }

    std::map<std::string, int> counts;

    while (!temp.empty()) {
        counts[temp.front().ResourceID]++;
        temp.pop();
    }

    std::cout << "\n===== Waiting List Statistics =====\n";

    int total = 0;

    for (const auto& entry : counts) {
        std::cout << "Resource ID: " << entry.first
                  << " | Students Waiting: " << entry.second
                  << '\n';

        total += entry.second;
    }

    std::cout << "Total Waiting Requests: " << total << '\n';
}

// Counts waiting requests for a specific resource.
// Copies the queue to preserve the original FIFO order.
int WaitingList::countWaitingForResource(
    const std::string& resourceID) const {

    std::queue<reservation> temp = waitingQueue;
    int count = 0;

    while (!temp.empty()) {

        if (temp.front().ResourceID == resourceID) {
            count++;
        }

        temp.pop();
    }

    return count;
}