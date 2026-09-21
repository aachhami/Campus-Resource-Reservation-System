#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "Reservation.h"

void reservationList::addReserv(
    const std::string& ReservationID,
    const std::string& StudentID,
    const std::string& StudentName,
    const std::string& ResourceID,
    const std::string& Date) {

    reservation* newReserv =
        new reservation(ReservationID, StudentID, StudentName, ResourceID, Date);

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

void reservationList::displayReserv() {

    if (head == nullptr) {
        std::cout << "\nNo active reservations.\n";
        return;
    }

    reservation* current = head;

    std::cout << "\n===== Active Reservations =====\n";

    while (current != nullptr) {
        std::cout << current->ReservationID << "|"
                  << current->StudentID << "|"
                  << current->StudentName << "|"
                  << current->ResourceID << "|"
                  << current->Date << '\n';

        current = current->next;
    }
}

void reservationList::getReserv() {

    std::ifstream file("data/reservations.txt");

    if (!file.is_open()) {
        std::cout << "Error: Could not open reservation file.\n";
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

void reservationList::cancelReserv() {

    std::cout << "Enter Reservation ID to cancel: ";

    std::string ReservationID;
    std::cin >> ReservationID;

    // Find the reservation in the linked list.
    reservation* current = head;

    while (current != nullptr &&
           current->ReservationID != ReservationID) {

        current = current->next;
    }

    if (current == nullptr) {
        std::cout << "Reservation ID not found.\n";
        return;
    }

    // Remove the node from the doubly linked list.
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    else {
        head = current->next;
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }
    else {
        tail = current->prev;
    }

    delete current;

    // Remove the same reservation from the file.
    std::ifstream file("data/reservations.txt");
    std::ofstream tempFile("data/reservations_temp.txt");

    if (!file.is_open() || !tempFile.is_open()) {
        std::cout << "Error updating reservation file.\n";
        return;
    }

    std::string line;

    while (std::getline(file, line)) {

        std::stringstream ss(line);
        std::string fileReservationID;

        std::getline(ss, fileReservationID, '|');

        if (fileReservationID != ReservationID) {
            tempFile << line << '\n';
        }
    }

    file.close();
    tempFile.close();

    std::remove("data/reservations.txt");
    std::rename(
        "data/reservations_temp.txt",
        "data/reservations.txt"
    );

    std::cout << "Reservation "
              << ReservationID
              << " canceled successfully.\n";
}

void reservationList::newReservation() {

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
    std::cin.ignore();
    std::getline(std::cin, StudentName);

    std::cout << "Enter Resource ID: ";
    std::cin >> ResourceID;

    std::cout << "Enter Date (MM/DD/YYYY): ";
    std::cin >> Date;

    addReserv(
        ReservationID,
        StudentID,
        StudentName,
        ResourceID,
        Date
    );

    std::ofstream file(
        "data/reservations.txt",
        std::ios::app
    );

    if (!file.is_open()) {
        std::cout << "Error: Could not update reservation file.\n";
        return;
    }

    file << ReservationID << "|"
         << StudentID << "|"
         << StudentName << "|"
         << ResourceID << "|"
         << Date << '\n';

    file.close();

    std::cout << "Reservation created successfully.\n";
}

reservationList::~reservationList() {

    reservation* current = head;

    while (current != nullptr) {

        reservation* next = current->next;

        delete current;

        current = next;
    }

    head = nullptr;
    tail = nullptr;
}