# Campus Resource Reservation System
## Final Project — User Documentation

### 1. Introduction

The Campus Resource Reservation System is a C++ command-line application that allows users to view campus resources, create and cancel reservations, manage waiting lists, undo cancellations, search reservations, sort resources, and generate reports.

The application demonstrates the use of vectors, doubly linked lists, FIFO queues, LIFO stacks, searching algorithms, and sorting algorithms.

### 2. System Requirements

- A computer with a C++17-compatible compiler, such as `g++`
- A terminal or command-line interface
- The complete project source code and `data` folder

### 3. Compiling the Program

Open a terminal in the main project directory.

Run:

```bash
g++ -std=c++17 Main.cpp Reservation.cpp WaitingList.cpp CancellationHistory.cpp src/Resource.cpp src/ResourceManager.cpp -Iinclude -o campus_system
```

### 4. Running the Program

After compilation, run:

```bash
./campus_system
```

Run the program from the main project directory so it can locate the files in the `data` folder.

### 5. Main Menu

The program displays nine menu options:

1. View Resources
2. Create Reservation
3. Cancel Reservation
4. View Waiting Lists
5. Undo Cancellation
6. Search Reservations
7. Sort Resources
8. Generate Report
9. Exit

Enter the number corresponding to the desired operation.

### 6. Using the Program

**Option 1 — View Resources**

Displays the campus resources loaded into the system, including their identifiers, names, types, and recorded availability.

**Option 2 — Create Reservation**

Follow the program prompts to enter the required reservation information.

The system validates reservation and resource identifiers. If a resource is unavailable, the request can be placed in the waiting queue.

**Option 3 — Cancel Reservation**

Enter the reservation ID requested by the program.

The system searches for the active reservation and processes its cancellation. When applicable, a waiting request can be assigned to the newly available resource.

**Option 4 — View Waiting Lists**

Displays waiting-list information for pending resource requests.

Waiting requests are processed using first-in, first-out (FIFO) behavior.

**Option 5 — Undo Cancellation**

Restores the most recent cancellation when an eligible cancellation record exists.

Cancellation history follows last-in, first-out (LIFO) behavior.

**Option 6 — Search Reservations**

Enter a reservation ID when prompted.

The system performs a manually implemented linear search through the active reservation doubly linked list.

If a matching reservation exists, its information is displayed. Otherwise, the program reports that no matching reservation was found.

**Option 7 — Sort Resources**

Sorts the resource inventory alphabetically by resource name using a manually implemented merge sort algorithm.

The sorted resource information is then displayed.

**Option 8 — Generate Report**

Generates reports based on the system's current data, including:

- Total active reservations
- Active reservations associated with each resource
- Most requested resources, considering active reservations and waiting requests
- Waiting-list statistics

**Option 9 — Exit**

Ends the program.

### 7. Input Data Files

The application loads initial information from two files:

**`data/resources.txt`**

Resource records follow this format:

`ResourceID|Name|Type|Availability`

Example:

`R101|Study Room 101|Study Room|Available`

**`data/reservations.txt`**

Reservation records follow this format:

`ReservationID|StudentID|StudentName|ResourceID|ReservationDate`

Example:

`301|1001|Alice Smith|R101|09/15/2026`

Do not change the field separators or file locations unless the program is also updated accordingly.

### 8. Error Handling

The application includes checks for invalid menu selections, duplicate reservation IDs, invalid resource IDs, missing reservations, and empty waiting or cancellation histories.

Users should follow the prompts and enter valid information.

### 9. Important Notes

- Waiting-list requests are maintained in memory and are not saved for the next program session.
- Report values reflect the data currently loaded and modified during the program session.
- Resource availability information is displayed according to the system's recorded resource state.
- The application should be started from the project root directory.

### 10. GitHub Repository

https://github.com/aachhami/Campus-Resource-Reservation-System
