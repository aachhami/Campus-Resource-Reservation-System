#include <iostream>
#include <limits>

#include "Reservation.h"
#include "WaitingList.h"
#include "include/ResourceManager.h"

int main() {

    // Reservation and waiting-list objects
    reservationList list;
    WaitingList wList;

    // Load existing reservations into the linked list
    list.getReserv();

    // Resource management object
    ResourceManager resourceManager;

    // Load resources from file
    if (!resourceManager.loadResources("data/resources.txt")) {
        std::cout << "Warning: Resource file could not be loaded.\n";
    }

    int choice = 0;

    do {
        std::cout << "\n";
        std::cout << "===== Campus Resource Reservation System =====\n\n";

        std::cout << "1. View Resources\n";
        std::cout << "2. Create Reservation\n";
        std::cout << "3. Cancel Reservation\n";
        std::cout << "4. View Waiting Lists\n";
        std::cout << "5. Undo Cancellation\n";
        std::cout << "6. Search Reservations\n";
        std::cout << "7. Sort Resources\n";
        std::cout << "8. Generate Report\n";
        std::cout << "9. Exit\n\n";

        std::cout << "Enter Choice: ";

        // Validate menu input
        while (!(std::cin >> choice) || choice < 1 || choice > 9) {

            std::cout
                << "Invalid choice. Please enter a number from 1 to 9: ";

            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
        }


        // Option 1 - View Resources
        if (choice == 1) {

            std::cout << "\nViewing Resources...\n";

            resourceManager.displayResources();
        }


        // Option 2 - Create Reservation
        else if (choice == 2) {

            std::cout << "\nCreating Reservation...\n";

            list.newReservation(
                resourceManager,
                wList
            );

            list.displayReserv();
        }


        // Option 3 - Cancel Reservation
        else if (choice == 3) {

            std::cout << "\nCanceling Reservation...\n";

            list.cancelReserv(resourceManager, wList);

            list.displayReserv();
        }


        // Option 4 - View Waiting Lists
        else if (choice == 4) {

            std::cout << "\nViewing Waiting Lists...\n";

            wList.displayList();
        }


        // Option 5 - Undo Cancellation
        else if (choice == 5) {

            std::cout << "\nUndoing Cancellation...\n";

            // Cancellation-history stack
            // will be connected here.
        }


        // Option 6 - Search Reservations
        else if (choice == 6) {

            std::cout << "\nSearching Reservations...\n";

            // Search functionality
            // will be connected here.
        }


        // Option 7 - Sort Resources
        else if (choice == 7) {

            std::cout << "\nSorting Resources...\n";

            // Sorting functionality
            // will be connected here.
        }


        // Option 8 - Generate Report
        else if (choice == 8) {

            std::cout << "\nGenerating Report...\n";

            // Report functionality
            // will be connected here.
        }


        // Option 9 - Exit
        else if (choice == 9) {

            std::cout
                << "\nExiting Campus Resource Reservation System...\n";
        }

    } while (choice != 9);

    return 0;
}