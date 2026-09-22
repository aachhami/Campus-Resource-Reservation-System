// Defines the stack used to store cancelled reservations for LIFO undo operations.
#pragma once

#include <stack>
#include "Reservation.h"

struct CancellationRecord {
    reservation cancelledReservation;
    bool hadAutomaticAssignment;
    reservation automaticAssignment;

    CancellationRecord()
        : hadAutomaticAssignment(false) {}

    CancellationRecord(
        const reservation& cancelled,
        bool hadAssignment = false,
        const reservation& assigned = reservation())
        : cancelledReservation(cancelled),
          hadAutomaticAssignment(hadAssignment),
          automaticAssignment(assigned) {}
};

class CancellationHistory {
private:
    std::stack<CancellationRecord> history;

public:
    void pushCancellation(
        const reservation& cancelled,
        bool hadAutomaticAssignment = false,
        const reservation& automaticAssignment = reservation()
    );

    bool isEmpty() const;

    CancellationRecord getLatestCancellation() const;

    void popLatestCancellation();

    void displayHistory() const;
};