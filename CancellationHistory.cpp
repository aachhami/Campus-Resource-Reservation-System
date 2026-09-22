#include "CancellationHistory.h"

#include <iostream>
#include <stdexcept>

void CancellationHistory::pushCancellation(
    const reservation& cancelled,
    bool hadAutomaticAssignment,
    const reservation& automaticAssignment) {

    history.push(
        CancellationRecord(
            cancelled,
            hadAutomaticAssignment,
            automaticAssignment
        )
    );
}

bool CancellationHistory::isEmpty() const {
    return history.empty();
}

CancellationRecord
CancellationHistory::getLatestCancellation() const {

    if (history.empty()) {
        throw std::runtime_error(
            "Cancellation history is empty."
        );
    }

    return history.top();
}

void CancellationHistory::popLatestCancellation() {

    if (!history.empty()) {
        history.pop();
    }
}

void CancellationHistory::displayHistory() const {

    if (history.empty()) {
        std::cout
            << "Cancellation history is empty.\n";
        return;
    }

    std::stack<CancellationRecord> temp = history;

    std::cout
        << "\n===== Cancellation History =====\n";

    while (!temp.empty()) {

        const reservation& item =
            temp.top().cancelledReservation;

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