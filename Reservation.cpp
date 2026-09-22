#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <limits>

#include "Reservation.h"
#include "WaitingList.h"
#include "include/ResourceManager.h"


// Add a reservation to the end of the linked list
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

    // First reservation in the linked list
    if (head == nullptr) {
        head = newReserv;
        tail = newReserv;
    }
    else {
        // Add to the end of the linked list
        tail->next = newReserv;
        newReserv->prev = tail;
        tail = newReserv;
    }
}


// Display all active reservations
void reservationList::displayReserv() {

    if (head == nullptr) {
        std::cout << "\nNo active reservations.\n";
        return;
    }

    reservation* current = head;

    std::cout << "\n===== Active Reservations =====\n";

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


// Load professor-provided reservations from file
void reservationList::getReserv() {

    std::ifstream file("data/reservations.txt");

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

        std::string ReservationID;
        std::string StudentID;
        std::string StudentName;
        std::string ResourceID;
        std::string Date;

        std::getline(ss, ReservationID, '|');
        std::getline(ss, StudentID, '|');
        std::getline(ss, StudentName, '|');
        std::getline(ss, ResourceID, '|');
        std::getline(ss, Date);

        addReserv(
            ReservationID,
            StudentID,
            StudentName,
            ResourceID,
            Date
        );
    }

    file.close();
}


// Create a new reservation.
// If the resource is unavailable, place the request
// into the FIFO waiting list.
void reservationList::newReservation(
    ResourceManager& resourceManager,
    WaitingList& waitingList) {

    std::string ReservationID;
    std::string StudentID;
    std::string StudentName;
    std::string ResourceID;
    std::string Date;


    std::cout << "Enter Reservation ID: ";
    std::cin >> ReservationID;

    std::cout << "Enter Student ID: ";
    std::cin >> StudentID;

    std::cout << "Enter Student Name: ";

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    std::getline(
        std::cin,
        StudentName
    );

    std::cout << "Enter Resource ID: ";
    std::cin >> ResourceID;

    std::cout << "Enter Date (MM/DD/YYYY): ";
    std::cin >> Date;


    // Find the requested resource
    Resource* resource =
        resourceManager.findResource(ResourceID);


    // Resource ID does not exist
    if (resource == nullptr) {

        std::cout
            << "Resource ID not found.\n";

        return;
    }


    // Resource is unavailable:
    // put the request into the waiting queue
    if (resource->getAvailability() != "Available") {

        reservation waitingReservation(
            ReservationID,
            StudentID,
            StudentName,
            ResourceID,
            Date
        );

        waitingList.addToList(
            waitingReservation
        );

        std::cout
            << "Resource is unavailable.\n";

        std::cout
            << "Reservation request added to waiting list.\n";

        return;
    }


    // Save the active reservation to the file
    std::ofstream file(
        "data/reservations.txt",
        std::ios::app
    );

    if (!file.is_open()) {

        std::cout
            << "Error: Could not update reservation file.\n";

        return;
    }

    file
        << ReservationID << "|"
        << StudentID << "|"
        << StudentName << "|"
        << ResourceID << "|"
        << Date << '\n';

    file.close();


    // Add reservation to the active linked list
    addReserv(
        ReservationID,
        StudentID,
        StudentName,
        ResourceID,
        Date
    );


    // The resource is now reserved
    resourceManager.updateAvailability(
        ResourceID,
        "Unavailable"
    );


    std::cout
        << "Reservation created successfully.\n";
}


// Cancel a reservation.
//
// After cancellation:
// 1. Check whether somebody is waiting for that resource.
// 2. If yes, assign it to the first matching person.
// 3. If nobody is waiting, mark the resource Available.
void reservationList::cancelReserv(
    ResourceManager& resourceManager,
    WaitingList& waitingList) {

    std::cout
        << "Enter Reservation ID to cancel: ";

    std::string ReservationID;
    std::cin >> ReservationID;


    // Find reservation in linked list
    reservation* current = head;

    while (
        current != nullptr &&
        current->ReservationID != ReservationID
    ) {

        current = current->next;
    }


    // Reservation was not found
    if (current == nullptr) {

        std::cout
            << "Reservation ID not found.\n";

        return;
    }


    // Save the Resource ID before deleting the node
    std::string cancelledResourceID =
        current->ResourceID;


    // First update reservations.txt
    std::ifstream file(
        "data/reservations.txt"
    );

    std::ofstream tempFile(
        "data/reservations_temp.txt"
    );


    if (!file.is_open() ||
        !tempFile.is_open()) {

        std::cout
            << "Error updating reservation file.\n";

        return;
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


        // Keep every reservation except
        // the one being cancelled
        if (fileReservationID != ReservationID) {

            tempFile
                << line
                << '\n';
        }
    }


    file.close();
    tempFile.close();


    // Replace the old reservation file
    std::remove(
        "data/reservations.txt"
    );

    if (std::rename(
            "data/reservations_temp.txt",
            "data/reservations.txt"
        ) != 0) {

        std::cout
            << "Error replacing reservation file.\n";

        return;
    }


    // Remove reservation from linked list
    if (current->prev != nullptr) {

        current->prev->next =
            current->next;
    }
    else {

        // Current node is the head
        head = current->next;
    }


    if (current->next != nullptr) {

        current->next->prev =
            current->prev;
    }
    else {

        // Current node is the tail
        tail = current->prev;
    }


    delete current;


    std::cout
        << "Reservation "
        << ReservationID
        << " canceled successfully.\n";


    // Check the FIFO waiting list for the
    // first person waiting for this resource
    reservation nextWaitingReservation;


    if (waitingList.getNextForResource(
            cancelledResourceID,
            nextWaitingReservation
        )) {


        // Save automatically assigned reservation
        // to reservations.txt
        std::ofstream reservationFile(
            "data/reservations.txt",
            std::ios::app
        );


        if (!reservationFile.is_open()) {

            std::cout
                << "Error: Could not save waiting-list reservation.\n";

            // Put the request back into the waiting list
            waitingList.addToList(
                nextWaitingReservation
            );

            return;
        }


        reservationFile
            << nextWaitingReservation.ReservationID << "|"
            << nextWaitingReservation.StudentID << "|"
            << nextWaitingReservation.StudentName << "|"
            << nextWaitingReservation.ResourceID << "|"
            << nextWaitingReservation.Date << '\n';


        reservationFile.close();


        // Add automatically assigned reservation
        // to the active linked list
        addReserv(
            nextWaitingReservation.ReservationID,
            nextWaitingReservation.StudentID,
            nextWaitingReservation.StudentName,
            nextWaitingReservation.ResourceID,
            nextWaitingReservation.Date
        );


        // Resource remains unavailable because it
        // was immediately assigned to another student
        resourceManager.updateAvailability(
            cancelledResourceID,
            "Unavailable"
        );


        std::cout
            << "Resource "
            << cancelledResourceID
            << " automatically assigned to "
            << nextWaitingReservation.StudentName
            << " from the waiting list.\n";
    }
    else {

        // Nobody is waiting, so resource becomes available
        resourceManager.updateAvailability(
            cancelledResourceID,
            "Available"
        );


        std::cout
            << "Resource "
            << cancelledResourceID
            << " is now available.\n";
    }
}


// Destructor - delete all linked-list nodes
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