#include<iostream>
#include<fstream>
#include<string>
#include"Reservation.h"
using namespace std;

int main() {

	int choice;
	cout << "===== Campus Resource Reservation System =====" << '\n' << '\n';
	cout << "1. View Resources" << '\n';
	cout << "2. Create Reservation" << '\n';
	cout << "3. Cancel Reservation" << '\n';
	cout << "4. View Waiting Lists" << '\n';
	cout << "5. Undo Cancellation" << '\n';
	cout << "6. Search Reservations" << '\n';
	cout << "7. Sort Resources" << '\n';
	cout << "8. Generate Report" << '\n';
	cout << "9. Exit" << '\n';

	do {
		cout << "Enter Choice: ";
		cin >> choice;
		cin.clear();
		cin.ignore();
	} while (!choice || choice < 1 || choice > 9);

	if (choice == 1) {
		cout << "Viewing Resources..." << '\n';
	}
	else if (choice == 2) {
		cout << "Creating Reservation..." << '\n';
	}
	else if (choice == 3) {
		cout << "Canceling Reservation..." << '\n';
	}
	else if (choice == 4) {
		cout << "Viewing Waiting lists..." << '\n';
	}
	else if (choice == 5) {
		cout << "Undoing Reservation..." << '\n';
	}
	else if (choice == 6) {
		cout << "Searching Reservations..." << '\n';
	}
	else if (choice == 7) {
		cout << "Sorting Resources..." << '\n';
	}
	else if (choice == 8) {
		cout << "Generating report..." << '\n';
	}
	else
		cout << "Exiting" << '\n';
	return 0;
}
