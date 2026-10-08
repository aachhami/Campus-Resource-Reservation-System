// Implements reservation loading, creation, cancellation, linked-list operations, and undo functionality.
#include "Reservation.h"
#include "WaitingList.h"
#include "CancellationHistory.h"
#include "include/ResourceManager.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

reservationList::reservationList()
    : head(nullptr),
      tail(nullptr) {
}

void reservationList::addReserv(
    const std::string& ReservationID,
    const std::string& StudentID,
    const std::string& StudentName,
    const std::string& ResourceID,
    const std::string& Date) {

    reservation* newReserv =
        new reservation(
            ReservationID,
            StudentID,
            StudentName,
            ResourceID,
            Date
        );

    if (head == nullptr) {

        head = newReserv;
        tail = newReserv;
    }
    else {

        tail->next = newReserv;

        newReserv->prev = tail;

        tail = newReserv;
    }
}

reservation* reservationList::findReservation(
    const std::string& reservationID) {

    reservation* current = head;

    while (current != nullptr) {

        if (current->ReservationID ==
            reservationID) {

            return current;
        }

        current = current->next;
    }

    return nullptr;
}

bool reservationList::reservationIDExists(
    const std::string& reservationID) const {

    reservation* current = head;

    while (current != nullptr) {

        if (current->ReservationID ==
            reservationID) {

            return true;
        }

        current = current->next;
    }

    return false;
}

void reservationList::displayReserv() {

    if (head == nullptr) {

        std::cout
            << "\nNo active reservations.\n";

        return;
    }

    std::cout
        << "\n===== Active Reservations =====\n";

    reservation* current = head;

    while (current != nullptr) {

        std::cout
            << current->ReservationID << "|"
            << current->StudentID << "|"
            << current->StudentName << "|"
            << current->ResourceID << "|"
            << current->Date << '\n';

        current = current->next;
    }
}

void reservationList::getReserv() {

    std::ifstream file(
        "data/reservations.txt"
    );

    if (!file.is_open()) {

        std::cout
            << "Error: Could not open reservation file.\n";

        return;
    }

    std::string line;

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        std::string reservationID;
        std::string studentID;
        std::string studentName;
        std::string resourceID;
        std::string date;

        std::getline(
            ss,
            reservationID,
            '|'
        );

        std::getline(
            ss,
            studentID,
            '|'
        );

        std::getline(
            ss,
            studentName,
            '|'
        );

        std::getline(
            ss,
            resourceID,
            '|'
        );

        std::getline(
            ss,
            date
        );

        addReserv(
            reservationID,
            studentID,
            studentName,
            resourceID,
            date
        );
    }
}

// Linear search for an active reservation by its ID.
void reservationList::searchReservation() {

    std::string reservationID;

    std::cout << "\nEnter Reservation ID to search: ";
    std::cin >> reservationID;

    reservation* result = findReservation(reservationID);

    if (result == nullptr) {
        std::cout << "\nReservation not found.\n";
        return;
    }

    std::cout << "\n===== Reservation Found =====\n";

    std::cout << "Reservation ID: "
              << result->ReservationID << '\n';

    std::cout << "Student ID: "
              << result->StudentID << '\n';

    std::cout << "Student Name: "
              << result->StudentName << '\n';

    std::cout << "Resource ID: "
              << result->ResourceID << '\n';

    std::cout << "Reservation Date: "
              << result->Date << '\n';
}

bool reservationList::appendReservationToFile(
    const reservation& item) {

    std::ofstream file(
        "data/reservations.txt",
        std::ios::app
    );

    if (!file.is_open()) {
        return false;
    }

    file
        << item.ReservationID << "|"
        << item.StudentID << "|"
        << item.StudentName << "|"
        << item.ResourceID << "|"
        << item.Date << '\n';

    return true;
}

bool reservationList::removeReservationFromFile(
    const std::string& reservationID) {

    std::ifstream file(
        "data/reservations.txt"
    );

    std::ofstream tempFile(
        "data/reservations_temp.txt"
    );

    if (!file.is_open() ||
        !tempFile.is_open()) {

        return false;
    }

    std::string line;

    while (std::getline(file, line)) {

        std::stringstream ss(line);

        std::string fileReservationID;

        std::getline(
            ss,
            fileReservationID,
            '|'
        );

        if (fileReservationID !=
            reservationID) {

            tempFile
                << line
                << '\n';
        }
    }

    file.close();
    tempFile.close();

    if (std::remove(
            "data/reservations.txt"
        ) != 0) {

        std::remove(
            "data/reservations_temp.txt"
        );

        return false;
    }

    if (std::rename(
            "data/reservations_temp.txt",
            "data/reservations.txt"
        ) != 0) {

        return false;
    }

    return true;
}

bool reservationList::removeReservationFromList(
    const std::string& reservationID) {

    reservation* current =
        findReservation(reservationID);

    if (current == nullptr) {

        return false;
    }

    if (current->prev != nullptr) {

        current->prev->next =
            current->next;
    }
    else {

        head = current->next;
    }

    if (current->next != nullptr) {

        current->next->prev =
            current->prev;
    }
    else {

        tail = current->prev;
    }

    delete current;

    return true;
}

void reservationList::newReservation(
    ResourceManager& resourceManager,
    WaitingList& waitingList) {

    std::string reservationID;
    std::string studentID;
    std::string studentName;
    std::string resourceID;
    std::string date;

    std::cout
        << "Enter Reservation ID: ";

    std::cin >> reservationID;

    if (reservationIDExists(
            reservationID
        ) ||
        waitingList.containsReservationID(
            reservationID
        )) {

        std::cout
            << "Error: Reservation ID already exists.\n";

        return;
    }

    std::cout
        << "Enter Student ID: ";

    std::cin >> studentID;

    std::cout
        << "Enter Student Name: ";

    std::cin.ignore(
        std::numeric_limits<
            std::streamsize>::max(),
        '\n'
    );

    std::getline(
        std::cin,
        studentName
    );

    std::cout
        << "Enter Resource ID: ";

    std::cin >> resourceID;

    Resource* resource =
        resourceManager.findResource(
            resourceID
        );

    if (resource == nullptr) {

        std::cout
            << "Error: Resource ID not found.\n";

        return;
    }

    std::cout
        << "Enter Date (MM/DD/YYYY): ";

    std::cin >> date;

    reservation request(
        reservationID,
        studentID,
        studentName,
        resourceID,
        date
    );

    if (resource->getAvailability() !=
        "Available") {

        waitingList.addToList(
            request
        );

        std::cout
            << "Resource is unavailable.\n";

        std::cout
            << "Reservation request added to waiting list.\n";

        return;
    }

    if (!appendReservationToFile(
            request
        )) {

        std::cout
            << "Error: Could not update reservation file.\n";

        return;
    }

    addReserv(
        request.ReservationID,
        request.StudentID,
        request.StudentName,
        request.ResourceID,
        request.Date
    );

    resourceManager.updateAvailability(
        resourceID,
        "Unavailable"
    );

    std::cout
        << "Reservation created successfully.\n";
}

void reservationList::cancelReserv(
    ResourceManager& resourceManager,
    WaitingList& waitingList,
    CancellationHistory& cancellationHistory) {

    std::string reservationID;

    std::cout
        << "Enter Reservation ID to cancel: ";

    std::cin >> reservationID;

    reservation* current =
        findReservation(
            reservationID
        );

    if (current == nullptr) {

        std::cout
            << "Reservation ID not found.\n";

        return;
    }

    reservation cancelled =
        *current;

    if (!removeReservationFromFile(
            reservationID
        )) {

        std::cout
            << "Error updating reservation file.\n";

        return;
    }

    removeReservationFromList(
        reservationID
    );

    reservation assignedFromWaiting;

    bool hadAutomaticAssignment =
        waitingList.getNextForResource(
            cancelled.ResourceID,
            assignedFromWaiting
        );

    if (hadAutomaticAssignment) {

        if (!appendReservationToFile(
                assignedFromWaiting
            )) {

            waitingList.addToFront(
                assignedFromWaiting
            );

            appendReservationToFile(
                cancelled
            );

            addReserv(
                cancelled.ReservationID,
                cancelled.StudentID,
                cancelled.StudentName,
                cancelled.ResourceID,
                cancelled.Date
            );

            std::cout
                << "Error: Could not save waiting-list reservation.\n";

            return;
        }

        addReserv(
            assignedFromWaiting.ReservationID,
            assignedFromWaiting.StudentID,
            assignedFromWaiting.StudentName,
            assignedFromWaiting.ResourceID,
            assignedFromWaiting.Date
        );

        resourceManager.updateAvailability(
            cancelled.ResourceID,
            "Unavailable"
        );
    }
    else {

        resourceManager.updateAvailability(
            cancelled.ResourceID,
            "Available"
        );
    }

    cancellationHistory.pushCancellation(
        cancelled,
        hadAutomaticAssignment,
        assignedFromWaiting
    );

    std::cout
        << "Reservation "
        << reservationID
        << " canceled successfully.\n";

    std::cout
        << "Added to cancellation history.\n";

    if (hadAutomaticAssignment) {

        std::cout
            << "Resource "
            << cancelled.ResourceID
            << " automatically assigned to "
            << assignedFromWaiting.StudentName
            << " from the waiting list.\n";
    }
    else {

        std::cout
            << "Resource "
            << cancelled.ResourceID
            << " is now available.\n";
    }
}

void reservationList::undoCancellation(
    ResourceManager& resourceManager,
    WaitingList& waitingList,
    CancellationHistory& cancellationHistory) {

    if (cancellationHistory.isEmpty()) {

        std::cout
            << "Cancellation history is empty. Nothing to undo.\n";

        return;
    }

    CancellationRecord record =
        cancellationHistory
            .getLatestCancellation();

    const reservation& cancelled =
        record.cancelledReservation;

    if (reservationIDExists(
            cancelled.ReservationID
        ) ||
        waitingList.containsReservationID(
            cancelled.ReservationID
        )) {

        std::cout
            << "Cannot undo: Reservation ID "
            << cancelled.ReservationID
            << " is already in use.\n";

        return;
    }

    if (record.hadAutomaticAssignment) {

        const reservation& assigned =
            record.automaticAssignment;

        if (!removeReservationFromFile(
                assigned.ReservationID
            )) {

            std::cout
                << "Error: Could not reverse automatic assignment.\n";

            return;
        }

        if (!removeReservationFromList(
                assigned.ReservationID
            )) {

            appendReservationToFile(
                assigned
            );

            std::cout
                << "Error: Could not reverse automatic assignment.\n";

            return;
        }

        waitingList.addToFront(
            assigned
        );
    }

    if (!appendReservationToFile(
            cancelled
        )) {

        if (record.hadAutomaticAssignment) {

            reservation assigned =
                record.automaticAssignment;

            waitingList.getNextForResource(
                assigned.ResourceID,
                assigned
            );

            appendReservationToFile(
                record.automaticAssignment
            );

            addReserv(
                record.automaticAssignment.ReservationID,
                record.automaticAssignment.StudentID,
                record.automaticAssignment.StudentName,
                record.automaticAssignment.ResourceID,
                record.automaticAssignment.Date
            );
        }

        std::cout
            << "Error: Could not restore cancelled reservation.\n";

        return;
    }

    addReserv(
        cancelled.ReservationID,
        cancelled.StudentID,
        cancelled.StudentName,
        cancelled.ResourceID,
        cancelled.Date
    );

    resourceManager.updateAvailability(
        cancelled.ResourceID,
        "Unavailable"
    );

    cancellationHistory
        .popLatestCancellation();

    std::cout
        << "Reservation "
        << cancelled.ReservationID
        << " restored successfully.\n";
}

reservationList::~reservationList() {

    reservation* current = head;

    while (current != nullptr) {

        reservation* next =
            current->next;

        delete current;

        current = next;
    }

    head = nullptr;
    tail = nullptr;
}