#include "WaitingList.h"
#include <iostream>
#include <stdexcept>

WaitingList::WaitingList() {
}

void WaitingList::addToList(const reservation& item) {
    waitingQueue.push(item);
}

void WaitingList::removeFromList() {
    if (!waitingQueue.empty()) {
        waitingQueue.pop();
    }
    else {
        std::cout << "Waiting list is empty." << std::endl;
    }
}

reservation WaitingList::getFrontItem() const {
    if (waitingQueue.empty()) {
        throw std::runtime_error("Waiting list is empty.");
    }

    return waitingQueue.front();
}

bool WaitingList::isListEmpty() const {
    return waitingQueue.empty();
}

void WaitingList::displayList() const {
    if (waitingQueue.empty()) {
        std::cout << "Waiting list is empty." << std::endl;
        return;
    }

    std::queue<reservation> tempQueue = waitingQueue;

    std::cout << "\n===== Waiting List =====\n";

    while (!tempQueue.empty()) {
        const reservation& item = tempQueue.front();

        std::cout << "Reservation ID: " << item.ReservationID
                  << " | Student ID: " << item.StudentID
                  << " | Student Name: " << item.StudentName
                  << " | Resource ID: " << item.ResourceID
                  << " | Date: " << item.Date
                  << '\n';

        tempQueue.pop();
    }
}