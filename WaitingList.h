#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include"Reservation.h"

#include <queue>
using namespace std;

class WaitingList {
private:
    queue<Reservation> waitingQueue;

public:
    WaitingList();
    void addToList(const Reservation& item);
    void removeFromList();
    Reservation getFrontItem() const;
    bool isListEmpty() const;
    void displayList() const;
};

#endif // WAITINGLIST_H