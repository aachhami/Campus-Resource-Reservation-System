#include <iostream>
#include <limits>

#include "Reservation.h"
#include "WaitingList.h"
#include "CancellationHistory.h"
#include "include/ResourceManager.h"

int main() {

    reservationList list;

    WaitingList waitingList;

    CancellationHistory cancellationHistory;

    ResourceManager resourceManager;

    list.getReserv();

    if (!resourceManager.loadResources(
            "data/resources.txt"
        )) {

        std::cout
            << "Warning: Resource file could not be loaded.\n";
    }

    int choice = 0;

    do {

        std::cout
            << "\n===== Campus Resource Reservation System =====\n\n"

            << "1. View Resources\n"
            << "2. Create Reservation\n"
            << "3. Cancel Reservation\n"
            << "4. View Waiting Lists\n"
            << "5. Undo Cancellation\n"
            << "6. Search Reservations\n"
            << "7. Sort Resources\n"
            << "8. Generate Report\n"
            << "9. Exit\n\n"

            << "Enter Choice: ";

        while (!(std::cin >> choice) ||
               choice < 1 ||
               choice > 9) {

            std::cout
                << "Invalid choice. Please enter a number from 1 to 9: ";

            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<
                    std::streamsize>::max(),
                '\n'
            );
        }

        switch (choice) {

        case 1:

            std::cout
                << "\nViewing Resources...\n";

            resourceManager
                .displayResources();

            break;

        case 2:

            std::cout
                << "\nCreating Reservation...\n";

            list.newReservation(
                resourceManager,
                waitingList
            );

            list.displayReserv();

            break;

        case 3:

            std::cout
                << "\nCanceling Reservation...\n";

            list.cancelReserv(
                resourceManager,
                waitingList,
                cancellationHistory
            );

            list.displayReserv();

            break;

        case 4:

            std::cout
                << "\nViewing Waiting Lists...\n";

            waitingList.displayList();

            break;

        case 5:

            std::cout
                << "\nUndoing Cancellation...\n";

            cancellationHistory
                .displayHistory();

            list.undoCancellation(
                resourceManager,
                waitingList,
                cancellationHistory
            );

            break;

        case 6:

            std::cout
                << "\nSearch Reservations will be implemented "
                << "for the final project.\n";

            break;

        case 7:

            std::cout
                << "\nSort Resources will be implemented "
                << "for the final project.\n";

            break;

        case 8:

            std::cout
                << "\nGenerate Report will be implemented "
                << "for the final project.\n";

            break;

        case 9:

            std::cout
                << "\nExiting Campus Resource Reservation System...\n";

            break;
        }

    } while (choice != 9);

    return 0;
}