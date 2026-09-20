#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <queue>
using namespace std;

class WaitingList {
private:
    queue<string> waitingQueue;

public:
    WaitingList();
    void addToList(const string& item);
    void removeFromList();
    string getFrontItem() const;
    bool isListEmpty() const;
};

#endif // WAITINGLIST_H