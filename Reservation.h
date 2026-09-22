#pragma once

#include <iostream>
#include <string>

class ResourceManager;
class WaitingList;

struct reservation {
    std::string ReservationID;
    std::string StudentID;
    std::string StudentName;
    std::string ResourceID;
    std::string Date;

    reservation* next;
    reservation* prev;

    // Default constructor
    reservation()
        : ReservationID(""),
          StudentID(""),
          StudentName(""),
          ResourceID(""),
          Date(""),
          next(nullptr),
          prev(nullptr) {
    }

    // Constructor with reservation information
    reservation(
        const std::string& ReservationID,
        const std::string& StudentID,
        const std::string& StudentName,
        const std::string& ResourceID,
        const std::string& Date)
        : ReservationID(ReservationID),
          StudentID(StudentID),
          StudentName(StudentName),
          ResourceID(ResourceID),
          Date(Date),
          next(nullptr),
          prev(nullptr) {
    }

    // Copy constructor
    reservation(const reservation& other)
        : ReservationID(other.ReservationID),
          StudentID(other.StudentID),
          StudentName(other.StudentName),
          ResourceID(other.ResourceID),
          Date(other.Date),
          next(nullptr),
          prev(nullptr) {
    }

    // Assignment operator
    reservation& operator=(const reservation& other) {

        if (this != &other) {
            ReservationID = other.ReservationID;
            StudentID = other.StudentID;
            StudentName = other.StudentName;
            ResourceID = other.ResourceID;
            Date = other.Date;

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

public:
    reservationList()
        : head(nullptr),
          tail(nullptr) {
    }

    void addReserv(
        const std::string& ReservationID,
        const std::string& StudentID,
        const std::string& StudentName,
        const std::string& ResourceID,
        const std::string& Date
    );

    void displayReserv();

    void getReserv();

    // Cancel reservation and process waiting list
    void cancelReserv(
        ResourceManager& resourceManager,
        WaitingList& waitingList
    );

    // Create reservation or add request to waiting list
    void newReservation(
        ResourceManager& resourceManager,
        WaitingList& waitingList
    );

    ~reservationList();
};