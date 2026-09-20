#pragma once
#include<iostream>
#include<string>


struct reservation {
	std::string ReservationID;
	std::string StudentID;
	std::string StudentName;
	std::string ResourceID;
	std::string Date;
	reservation* next;
	reservation* prev;
	reservation(const std::string ReservationID, const std::string StudentID, const std::string StudentName, const std::string ResourceID, const std::string Date) : ReservationID(ReservationID), StudentID(StudentID), StudentName(StudentName), ResourceID(ResourceID), Date(Date), next(nullptr), prev(nullptr) {}
};

class reservationList {
private:
	reservation* head;
	reservation* tail;
public:
	reservationList() : head(nullptr), tail(nullptr) {}
	void addReserv(const std::string& ReservationID, const std::string& StudentID, const std::string& StudentName, const std::string& ResourceID, const std::string& Date);
	void displayReserv();
	void getReserv();
	void cancelReserv();
	void newReservation();
	~reservationList();
}; 