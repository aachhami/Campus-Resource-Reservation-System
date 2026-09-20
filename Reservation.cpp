#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"Reservation.h"

reservation* head;
reservation* tail;
void reservationList::addReserv(const std::string& ReservationID, const std::string& StudentID, const std::string& StudentName, const std::string& ResourceID, const std::string& Date) {
	reservation* newReserv = new reservation(ReservationID, StudentID, StudentName, ResourceID, Date);
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
	reservation* current = head;
	std::cout << '\n';
	while (current != nullptr) {
		std::cout << current->ReservationID << "|" << current->StudentID << "|" << current->StudentName << "|" << current->ResourceID << "|" << current->Date << '\n';
		current = current->next;
	}
}
void reservationList::getReserv() {
	reservationList list;
	std::ifstream file("reservations.txt", std::ios::in | std::ios::out);
	std::string line;
	while (getline(file, line)) {
		if (line.empty()) {
			continue;
		}
		std::stringstream ss(line);
		std::string ReservationID, StudentID, StudentName, ResourceID, Date;
		std::getline(ss, ReservationID, '|');
		std::getline(ss, StudentID, '|');
		std::getline(ss, StudentName, '|');
		std::getline(ss, ResourceID, '|');
		std::getline(ss, Date, '|');

		addReserv(ReservationID, StudentID, StudentName, ResourceID, Date);
	}
	file.close();
}
void reservationList::cancelReserv() {
	reservationList list;
	std::cout << "Enter Reservation ID to cancel: ";
	std::string ReservationID;
	std::cin >> ReservationID;
	std::ifstream file("reservations.txt", std::ios::in);
	std::ofstream tempFile("temp.txt", std::ios::out);
	std::string line;
	while (getline(file, line)) {
		if (line.find(ReservationID) == std::string::npos) {
			tempFile << line << '\n';
		}
	}
	file.close();
	tempFile.close();
	remove("reservations.txt");
	rename("temp.txt", "reservations.txt");
}
void reservationList::newReservation() {
	reservationList list;
	std::string ReservationID, StudentID, StudentName, ResourceID, Date;
	std::cout << "Enter Reservation ID: ";
	std::cin >> ReservationID;
	std::cout << "Enter Student ID: ";
	std::cin >> StudentID;
	std::cout << "Enter Student Name: ";
	std::cin.ignore();
	getline(std::cin, StudentName);
	std::cout << "Enter Resource ID: ";
	std::cin >> ResourceID;
	std::cout << "Enter Date (MM/DD/YYYY): ";
	std::cin >> Date;
	addReserv(ReservationID, StudentID, StudentName, ResourceID, Date);
	std::ofstream file("reservations.txt", std::ios::app);
	file << ReservationID << "|" << StudentID << "|" << StudentName << "|" << ResourceID << "|" << Date << '\n';
	file.close();
}
reservationList::~reservationList() {
	reservation* current = head;
	while (current != nullptr) {
		reservation* next = current->next;
		delete current;
		current = next;
	}
}