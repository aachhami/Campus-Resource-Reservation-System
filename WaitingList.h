#pragma once

#include <queue>
#include "Reservation.h"

class WaitingList {
private:
    std::queue<reservation> waitingQueue;

public:
    WaitingList();

    void addToList(const reservation& item);
    void removeFromList();
    reservation getFrontItem() const;
    bool isListEmpty() const;
    void displayList() const;
};