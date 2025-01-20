#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "event_structs.h"
#include "stack2.h"
#include "queue2.h"
#include "quicksort2.h"

class EventManager {
public:
    EventManager();
    ~EventManager();

    void addEvent();
    void registerParticipant();
    void displayAllEvents();
    void searchEvent();
    void sortEvents();
    void undoLastAction();

private:
    Event* events;  // Array of events
    Queue** eventQueues;  // Array of queues (one for each event)
    int* waitingListSizes;  // Array to store number of participants for each event
    int eventCount;  // Total number of events
    int capacity;  // Maximum number of events the system can hold
    Stack actionStack;  // Stack for undo functionality

    void resizeArray();
};

void clearInputBuffer();
bool adminLogin();
void adminMode(EventManager &manager);
void userMode(EventManager &manager);

#endif // EVENT_MANAGER_H
