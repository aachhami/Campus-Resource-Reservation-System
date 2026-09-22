#pragma once

#include <string>

class ResourceManager;
class WaitingList;
class CancellationHistory;

struct reservation {
    std::string ReservationID;
    std::string StudentID;
    std::string StudentName;
    std::string ResourceID;
    std::string Date;

    reservation* next;
    reservation* prev;

    reservation()
        : next(nullptr),
          prev(nullptr) {
    }

    reservation(
        const std::string& reservationID,
        const std::string& studentID,
        const std::string& studentName,
        const std::string& resourceID,
        const std::string& date)
        : ReservationID(reservationID),
          StudentID(studentID),
          StudentName(studentName),
          ResourceID(resourceID),
          Date(date),
          next(nullptr),
          prev(nullptr) {
    }

    reservation(const reservation& other)
        : ReservationID(other.ReservationID),
          StudentID(other.StudentID),
          StudentName(other.StudentName),
          ResourceID(other.ResourceID),
          Date(other.Date),
          next(nullptr),
          prev(nullptr) {
    }

    reservation& operator=(
        const reservation& other) {

        if (this != &other) {

            ReservationID =
                other.ReservationID;

            StudentID =
                other.StudentID;

            StudentName =
                other.StudentName;

            ResourceID =
                other.ResourceID;

            Date =
                other.Date;

            next = nullptr;
            prev = nullptr;
        }

        return *this;
    }
};

class reservationList {
private:
    reservation* head;
    reservation* tail;

    reservation* findReservation(
        const std::string& reservationID
    );

    bool removeReservationFromList(
        const std::string& reservationID
    );

    bool removeReservationFromFile(
        const std::string& reservationID
    );

    bool appendReservationToFile(
        const reservation& item
    );

public:
    reservationList();

    void addReserv(
        const std::string& ReservationID,
        const std::string& StudentID,
        const std::string& StudentName,
        const std::string& ResourceID,
        const std::string& Date
    );

    void displayReserv();

    void getReserv();

    bool reservationIDExists(
        const std::string& reservationID
    ) const;

    void newReservation(
        ResourceManager& resourceManager,
        WaitingList& waitingList
    );

    void cancelReserv(
        ResourceManager& resourceManager,
        WaitingList& waitingList,
        CancellationHistory& cancellationHistory
    );

    void undoCancellation(
        ResourceManager& resourceManager,
        WaitingList& waitingList,
        CancellationHistory& cancellationHistory
    );

    ~reservationList();
};