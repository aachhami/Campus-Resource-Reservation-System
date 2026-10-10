# Campus Resource Reservation System

## Project 1 - Final Submission

The Campus Resource Reservation System is a C++ command-line application
for managing campus resources and student reservations.

The project demonstrates object-oriented programming and the use of
fundamental data structures including vectors, linked lists, queues,
and stacks.

## Implemented Features

The current Milestone 1 implementation supports:

- Loading campus resources from an input file
- Storing resources using a vector
- Displaying resource information and availability
- Creating new reservations
- Preventing duplicate reservation IDs
- Validating resource IDs
- Storing active reservations using a doubly linked list
- Cancelling active reservations
- Adding requests for unavailable resources to a FIFO waiting list
- Automatically assigning a resource to the next eligible waiting user
  when the resource becomes available
- Storing cancelled reservations using a stack
- Displaying cancellation history
- Undoing the most recent cancellation using LIFO behavior
- Handling empty waiting lists and cancellation histories
- Validating menu selections

### Final Project Features

**Option 6 — Search Reservations**
- Implements manual linear search using the doubly linked list.
- Searches for a reservation using its reservation ID.
- Displays reservation details or a not-found message.

**Option 7 — Sort Resources**
- Implements merge sort manually without using std::sort().
- Sorts resources alphabetically by resource name.
- Uses O(n log n) time and O(n) additional space.

**Option 8 — Generate Report**
- Displays the total number of active reservations.
- Shows active reservation counts for each resource.
- Identifies the most requested resources.
- Displays waiting-list statistics for each resource.
- Generates reports using the system's current data.

## Data Structures

### Vector

The resource inventory is stored using a `vector<Resource>`.

### Doubly Linked List

Active reservations are stored using a doubly linked list. Each
reservation node contains pointers to the previous and next reservation.

### Queue

Waiting-list requests are stored using a FIFO queue. When a resource is
unavailable, the request is placed in the waiting list. When the resource
becomes available, the first matching waiting request is processed.

### Stack

Cancelled reservations are stored using a stack. This allows the system
to restore only the most recently cancelled reservation using LIFO
behavior.

## Input Files

The program loads its initial data from the `data` directory.

### Resource File

`data/resources.txt`

Resource records use the following format:

```text
ResourceID|Name|Type|Availability
```

Example:

```text
R101|Study Room 101|Study Room|Available
```

### Reservation File

`data/reservations.txt`

Reservation records use the following format:

```text
ReservationID|StudentID|StudentName|ResourceID|ReservationDate
```

Example:

```text
301|1001|Alice Smith|R101|09/15/2026
```

## Program Menu

The command-line interface contains the following menu:

```text
1. View Resources
2. Create Reservation
3. Cancel Reservation
4. View Waiting Lists
5. Undo Cancellation
6. Search Reservations
7. Sort Resources
8. Generate Report
9. Exit
```

All nine menu options are integrated into the final project.

- Option 1: Display all campus resources and their availability.
- Option 2: Create a reservation or join the waiting list.
- Option 3: Cancel an active reservation.
- Option 4: Display waiting-list requests.
- Option 5: Undo the most recent cancellation.
- Option 6: Search for a reservation by ID using linear search.
- Option 7: Sort resources alphabetically using merge sort.
- Option 8: Generate reservation, utilization, popularity, and waiting-list reports.
- Option 9: Exit the program.

## Project Files

```text
Campus-Resource-Reservation-System/
├── data/
│   ├── reservations.txt
│   └── resources.txt
├── include/
│   ├── Resource.h
│   └── ResourceManager.h
├── src/
│   ├── Resource.cpp
│   └── ResourceManager.cpp
├── CancellationHistory.cpp
├── CancellationHistory.h
├── Main.cpp
├── Reservation.cpp
├── Reservation.h
├── WaitingList.cpp
├── WaitingList.h
├── ComplexityAnalysis.md
└── README.md
```

## Compilation

The project uses C++17.

From the project root directory, compile with:

```bash
g++ -std=c++17 Main.cpp Reservation.cpp WaitingList.cpp CancellationHistory.cpp src/Resource.cpp src/ResourceManager.cpp -Iinclude -o campus_system
```

## Running the Program

After compilation, run:

```bash
./campus_system
```

The program should be executed from the project root directory so that
the files inside the `data` directory can be located correctly.

## Testing

### Milestone 1 Test Cases

The following test cases were included during Milestone 1:

- Loading the provided resource file
- Loading the provided reservation file
- Displaying resources
- Creating a valid reservation
- Rejecting duplicate reservation IDs
- Rejecting invalid resource IDs
- Adding requests for unavailable resources to the waiting list
- Processing waiting requests in FIFO order
- Cancelling reservations
- Automatically assigning a newly available resource to a waiting user
- Undoing the most recent cancellation
- Verifying LIFO cancellation-history behavior
- Handling an empty waiting queue
- Handling an empty cancellation stack
- Handling invalid menu input

### Final Project Test Results

The following tests were performed on the final project:

| Test | Result |
|------|--------|
| Compile the merged project using C++17 | Passed |
| Search for existing reservation ID 301 | Passed |
| Search for nonexistent reservation ID 999 | Passed |
| Sort 20 resources alphabetically using merge sort | Passed |
| Generate report with 20 active reservations | Passed |
| Display utilization statistics for all 20 resources | Passed |
| Identify most requested resources | Passed |
| Add reservation 999 to the waiting list for R103 | Passed |
| Verify R103 has 1 waiting request | Passed |
| Verify R103 has 3 total requests | Passed |
| Return to the main menu after generating reports | Passed |
| Exit the program normally | Passed |

All final-project tests listed above were performed locally using WSL.

Final-project compilation and execution on UNT CELL are still pending verification.


## Complexity Analysis

Time-complexity analysis for reservation insertion, reservation removal,
waiting-list processing, and undo cancellation is provided in
`ComplexityAnalysis.md`.

## GitHub Repository

https://github.com/aachhami/Campus-Resource-Reservation-System