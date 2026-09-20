#include<iostream>
#include"Reservation.h"



int main() {
	reservationList list;
	int choice;
	std::cout << "===== Campus Resource Reservation System =====" << '\n' << '\n';
	std::cout << "1. View Resources" << '\n';
	std::cout << "2. Create Reservation" << '\n';
	std::cout << "3. Cancel Reservation" << '\n';
	std::cout << "4. View Waiting Lists" << '\n';
	std::cout << "5. Undo Cancellation" << '\n';
	std::cout << "6. Search Reservations" << '\n';
	std::cout << "7. Sort Resources" << '\n';
	std::cout << "8. Generate Report" << '\n';
	std::cout << "9. Exit" << '\n';

	do {
		std::cout << "Enter Choice: ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore();
	} while (!choice || choice < 1 || choice > 9);

	if (choice == 1) {
		std::cout << "Viewing Resources..." << '\n';
	}
	else if (choice == 2) {
		std::cout << "Creating Reservation..." << '\n';
		list.getReserv();
		list.newReservation();
		list.displayReserv();
	}
	else if (choice == 3) {
		std::cout << "Canceling Reservation..." << '\n';
		list.cancelReserv();
		list.getReserv();
		list.displayReserv();
	}
	else if (choice == 4) {
		std::cout << "Viewing Waiting lists..." << '\n';
	}
	else if (choice == 5) {
		std::cout << "Undoing Reservation..." << '\n';
	}
	else if (choice == 6) {
		std::cout << "Searching Reservations..." << '\n';
	}
	else if (choice == 7) {
		std::cout << "Sorting Resources..." << '\n';
	}
	else if (choice == 8) {
		std::cout << "Generating report..." << '\n';
	}else
		std::cout << "Exiting" << '\n';
	return 0;

}
