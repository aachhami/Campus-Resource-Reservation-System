# Campus Resource Reservation System
## Milestone 1 - Complexity Analysis

This document analyzes the time complexity of the main data structure
operations used in the Campus Resource Reservation System.

Let:

- n = number of active reservations
- w = number of requests in the waiting list
- r = number of resources

### 1. Reservation Insertion - O(1)

Active reservations are stored in a doubly linked list. The reservation
list maintains both a head pointer and a tail pointer.

When a new reservation is inserted, the new node is attached directly
to the tail of the linked list. Because the program does not need to
traverse the list to find the insertion position, the linked-list
insertion operation takes O(1) time.

The complete reservation-creation process may also perform validation
and resource lookup before insertion, but the linked-list insertion
itself is O(1).

### 2. Reservation Removal - O(n)

To cancel a reservation, the program searches the active reservation
linked list for the requested reservation ID.

In the worst case, the program may need to examine all n active
reservations before finding the requested reservation or determining
that it does not exist. Therefore, locating a reservation for removal
takes O(n) time.

After the reservation node has been found, unlinking the node from the
doubly linked list takes O(1) time.

The reservation file is also rewritten during cancellation, which
requires processing the reservation records. Therefore, cancellation
remains linear with respect to the number of reservations, excluding
additional waiting-list processing.

### 3. Waiting-List Processing - O(w)

Waiting requests are stored using a FIFO queue.

Adding a new request to the back of the queue is O(1).

When a resource becomes available, the program searches the waiting
queue for the first request associated with that resource. In the worst
case, it may inspect all w waiting-list entries.

Therefore, processing the waiting list to locate the next matching
student is O(w).

The queue preserves FIFO order so that the first matching student who
requested the resource is processed first.

### 4. Undo Cancellation - O(n + w + r)

Cancellation history is stored using a stack. Accessing or removing the
most recently cancelled reservation from the top of the stack is O(1).

The complete undo operation can require additional work. If the
cancelled resource was automatically assigned to a waiting student,
the program may need to remove that automatic reservation from the
active reservation list and file and return the student to the waiting
queue.

Removing an active reservation can require O(n), rebuilding the waiting
queue can require O(w), and locating/updating a resource stored in the
resource vector can require O(r).

Therefore, the complete worst-case undo operation is O(n + w + r),
while the stack push, top, and pop operations themselves are O(1).

## Summary

| Operation | Time Complexity |
|---|---|
| Linked-list reservation insertion | O(1) |
| Reservation removal/search | O(n) |
| Waiting-list enqueue | O(1) |
| Waiting-list processing for a resource | O(w) |
| Cancellation stack push/top/pop | O(1) |
| Complete undo cancellation | O(n + w + r) |