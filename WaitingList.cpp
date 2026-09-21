#include "WaitingList.h"
#include <iostream>

WaitingList::WaitingList() {
    // Constructor
}

void WaitingList::addToList(const Reservation& item) {
    //if resource is not available, add to waiting list
    waitingQueue.push(item);
}

void WaitingList::removeFromList() {
    if (!waitingQueue.empty()) {
        waitingQueue.pop();
    } else {
        cout << "Waiting list is empty. Cannot remove item." << endl;
    }
}

Reservation WaitingList::getFrontItem() const {
    if (!waitingQueue.empty()) {
        return waitingQueue.front();
    } else {
        // Return a default-constructed Reservation or handle the error appropriately
        return Reservation();
    }
}

bool WaitingList::isListEmpty() const {
    return waitingQueue.empty();
}

void WaitingList::displayList() const {
    if (waitingQueue.empty()) {
        cout << "Waiting list is empty." << endl;
        return;
    }

    queue<Reservation> tempQueue = waitingQueue; // Create a copy to display items
    cout << "Waiting List:" << endl;
    while (!tempQueue.empty()) {
        cout << tempQueue.front() << endl;
        tempQueue.pop();
    }
}