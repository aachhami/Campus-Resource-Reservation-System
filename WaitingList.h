// Defines the FIFO waiting-list queue used for unavailable resource requests.
#pragma once

#include <queue>
#include <string>

#include "Reservation.h"

class WaitingList {
private:
    std::queue<reservation> waitingQueue;

public:
    WaitingList();

    void addToList(
        const reservation& item
    );

    void addToFront(
        const reservation& item
    );

    void removeFromList();

    reservation getFrontItem() const;

    bool isListEmpty() const;

    bool containsReservationID(
        const std::string& reservationID
    ) const;

    bool getNextForResource(
        const std::string& resourceID,
        reservation& nextReservation
    );

    void displayList() const;
    void displayWaitingStatistics() const;
    int countWaitingForResource(const std::string& resourceID) const;
};