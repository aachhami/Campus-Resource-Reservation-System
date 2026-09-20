#include "WaitingList.h"
#include <iostream>

WaitingList::WaitingList() {
    // Constructor
}

void WaitingList::addToList(const string& item) {
    waitingQueue.push(item);
}

void WaitingList::removeFromList() {
    if (!waitingQueue.empty()) {
        waitingQueue.pop();
    } else {
        cout << "Waiting list is empty. Cannot remove item." << endl;
    }
}

string WaitingList::getFrontItem() const {
    if (!waitingQueue.empty()) {
        return waitingQueue.front();
    } else {
        return "Waiting list is empty.";
    }
}

bool WaitingList::isListEmpty() const {
    return waitingQueue.empty();
}

