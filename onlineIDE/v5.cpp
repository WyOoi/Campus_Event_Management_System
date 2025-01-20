#include <iostream>
#include <string>
using namespace std;

struct Event {
    int id;
    string name;
    string date;
    string time;
    string location;
};

struct Participant {
    string name;
    string contact;
};

struct Action {
    string actionType;
    string details;
    Action* next;
};

class Stack {
    public:
        Stack();
        ~Stack();

        void Push(const string& actionType, const string& details);
        void Clear();
        void Display();
        
        Action* Pop();
        
    private:
        Action* top;
};

Stack::Stack() : top(NULL) {}

Stack::~Stack() {
    Clear();
}

void Stack::Push(const string& actionType, const string& details) {
    Action* newAction = new Action{actionType, details, top};
    top = newAction;
}

void Stack::Clear() {
    while (top) {
        Action* temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::Display() {
    if (!top) {
        cout << "No actions in stack." << endl;
        return;
    }
    Action* current = top;
    while (current) {
        cout << "Action: " << current->actionType << ", Details: " << current->details << endl;
        current = current->next;
    }
}

Action* Stack::Pop() {
    if (!top) return NULL;
    Action* result = top;
    top = top->next;
    return result;
}

class QuickSortHelper {
    public:
        static void sort(int ids[], int low, int high) {
            if (low < high) {
                int pi = partition(ids, low, high);
                sort(ids, low, pi - 1);
                sort(ids, pi + 1, high);
            }
        }

    private:
        static int partition(int ids[], int low, int high) {
            int pivot = ids[high];
            int i = low - 1;
            for (int j = low; j < high; j++) {
                if (ids[j] < pivot) {
                    i++;
                    swap(ids[i], ids[j]);
                }
            }
            swap(ids[i + 1], ids[high]);
            return i + 1;
        }
};

class QueueHelper {
    public:
        static void registerParticipant(Participant** waitingLists, int* waitingListSizes, int eventId, Participant newParticipant) {
            Participant* updatedList = new Participant[waitingListSizes[eventId] + 1];
            for (int i = 0; i < waitingListSizes[eventId]; i++) {
                updatedList[i] = waitingLists[eventId][i];
            }
            updatedList[waitingListSizes[eventId]] = newParticipant;

            delete[] waitingLists[eventId];
            waitingLists[eventId] = updatedList;
            waitingListSizes[eventId]++;
        }
};

class SearchHelper {
    public:
        static int searchEvent(Event* events, int eventCount, int searchId) {
            for (int i = 0; i < eventCount; i++) {
                if (events[i].id == searchId) {
                    return i; // Return the index of the event
                }
            }
            return -1; // Event not found
        }
};

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
        Event* events;
        int* waitingListSizes;
        Participant** waitingLists;
        int eventCount;
        int capacity;
        Stack actionStack;

        void resizeArray();
};

EventManager::EventManager() : eventCount(0), capacity(10) {
    events = new Event[capacity];
    waitingListSizes = new int[capacity]();
    waitingLists = new Participant*[capacity]();
    
    events[eventCount++] = {1, "Tech Conference", "2025-01-20", "09:00 AM", "Hall A"};
    events[eventCount++] = {2, "Art Workshop", "2025-01-21", "11:00 AM", "Room 102"};
    events[eventCount++] = {3, "Music Concert", "2025-01-22", "07:00 PM", "Open Grounds"};
    events[eventCount++] = {4, "Coding Hackathon", "2025-01-23", "10:00 AM", "Lab 304"};
    events[eventCount++] = {5, "Startup Pitch", "2025-01-24", "02:00 PM", "Hall B"};
    events[eventCount++] = {6, "Photography Contest", "2025-01-25", "03:00 PM", "Room 210"};
    events[eventCount++] = {7, "Literary Meet", "2025-01-26", "04:00 PM", "Room 301"};
    events[eventCount++] = {8, "Robotics Expo", "2025-01-27", "01:00 PM", "Hall C"};
    events[eventCount++] = {9, "Science Fair", "2025-01-28", "10:00 AM", "Main Hall"};
    events[eventCount++] = {10, "Fitness Workshop", "2025-01-29", "08:00 AM", "Gym"};
}

EventManager::~EventManager() {
    delete[] events;
    delete[] waitingListSizes;
    for (int i = 0; i < capacity; i++) {
        delete[] waitingLists[i];
    }
    delete[] waitingLists;
}

void EventManager::addEvent() {
    if (eventCount == capacity) {
        resizeArray();
    }
    Event newEvent;
    cout << "Enter event ID: ";
    cin >> newEvent.id;
    cin.ignore();
    cout << "Enter event name: ";
    getline(cin, newEvent.name);
    cout << "Enter event date: ";
    getline(cin, newEvent.date);
    cout << "Enter event time: ";
    getline(cin, newEvent.time);
    cout << "Enter event location: ";
    getline(cin, newEvent.location);

    events[eventCount] = newEvent;
    waitingLists[eventCount] = NULL;
    waitingListSizes[eventCount] = 0;
    eventCount++;

    actionStack.Push("Add Event", newEvent.name);
    cout << "Event added successfully!\n";
}

void EventManager::registerParticipant() {
    int eventId;
    cout << "Enter Event ID: ";
    cin >> eventId;
    int index = SearchHelper::searchEvent(events, eventCount, eventId);

    if (index == -1) {
        cout << "Event not found.\n";
        return;
    }

    Participant newParticipant;
    cout << "Enter participant name: ";
    cin.ignore();
    getline(cin, newParticipant.name);
    cout << "Enter participant contact: ";
    getline(cin, newParticipant.contact);

    QueueHelper::registerParticipant(waitingLists, waitingListSizes, index, newParticipant);

    actionStack.Push("Register Participant", newParticipant.name);
    cout << "Participant registered successfully!\n";
}

void EventManager::displayAllEvents() {
    if (eventCount == 0) {
        cout << "No events available.\n";
        return;
    }

    for (int i = 0; i < eventCount; i++) {
        cout << "Event ID: " << events[i].id
             << " | Name: " << events[i].name
             << " | Date: " << events[i].date
             << " | Time: " << events[i].time
             << " | Location: " << events[i].location << endl;
    }
}

void EventManager::searchEvent() {
    int searchId;
    cout << "Enter Event ID to search: ";
    cin >> searchId;

    int index = SearchHelper::searchEvent(events, eventCount, searchId);

    if (index != -1) {
        cout << "Event Found: " << events[index].name << endl;
    } else {
        cout << "Event not found.\n";
    }
}

void EventManager::sortEvents() {
    int* ids = new int[eventCount];
    for (int i = 0; i < eventCount; i++) {
        ids[i] = events[i].id;
    }

    QuickSortHelper::sort(ids, 0, eventCount - 1);

    // Now sort the events based on the sorted ids
    Event* sortedEvents = new Event[eventCount];
    for (int i = 0; i < eventCount; i++) {
        for (int j = 0; j < eventCount; j++) {
            if (events[j].id == ids[i]) {
                sortedEvents[i] = events[j];
                break;
            }
        }
    }

    // Copy the sorted events back into the original events array
    for (int i = 0; i < eventCount; i++) {
        events[i] = sortedEvents[i];
    }

    delete[] ids;
    delete[] sortedEvents;

    cout << "Sorted Events:\n";
    for (int i = 0; i < eventCount; i++) {
        cout << "Event ID: " << events[i].id
             << " | Name: " << events[i].name
             << " | Date: " << events[i].date
             << " | Time: " << events[i].time
             << " | Location: " << events[i].location << endl;
    }
}


void EventManager::undoLastAction() {
    Action* undoneAction = actionStack.Pop();
    if (undoneAction) {
        cout << "Undone Action: " << undoneAction->actionType << " - " << undoneAction->details << endl;
        delete undoneAction;
    } else {
        cout << "No actions to undo.\n";
    }
}

void EventManager::resizeArray() {
    capacity *= 2;
    Event* newEvents = new Event[capacity];
    int* newSizes = new int[capacity];
    Participant** newLists = new Participant*[capacity];
    for (int i = 0; i < eventCount; i++) {
        newEvents[i] = events[i];
        newSizes[i] = waitingListSizes[i];
        newLists[i] = waitingLists[i];
    }
    delete[] events;
    delete[] waitingListSizes;
    delete[] waitingLists;
    events = newEvents;
    waitingListSizes = newSizes;
    waitingLists = newLists;
}

// Function to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// Function for admin login
bool adminLogin(){
    string username, password;
    cout << "\nAdmin Login:\n"<<"Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    const string adminUsername = "admin";
    const string adminPassword = "1234";

    if (username == adminUsername && password == adminPassword){
        cout << "Login successful. Welcome, Admin!\n";
        clearInputBuffer();
        return true;
    } else{
        cout << "Invalid credentials. Access denied.\n";
        clearInputBuffer();
        return false;
    }
}

// Function to handle Admin Mode
void adminMode(EventManager &manager){
    int choice;
    do {
        cout << "\nAdmin Menu:\n"<< "1. Add Event\n"<< "2. Display All Events\n"<< "3. Search Event\n"
             << "4. Sort Events\n"<< "5. Undo Last Action\n"<< "6. Back to Main Menu\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                manager.addEvent();
                break;
            case 2:
                manager.displayAllEvents();
                break;
            case 3:
                manager.searchEvent();
                break;
            case 4:
                manager.sortEvents();
                break;
            case 5:
                manager.undoLastAction();
                break;
            case 6:
                cout << "Returning to the main menu...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}

// Function to handle User Mode
void userMode(EventManager &manager) {
    int choice;
    do {
        cout << "\nUser Menu:\n"
             << "1. Register Participant\n"
             << "2. Display All Events\n"
             << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                manager.registerParticipant();
                break;
            case 2:
                manager.displayAllEvents();
                break;
            case 3:
                cout << "Returning to the main menu...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}

int main() {
    EventManager manager;
    int modeChoice;

    while (true) {
        cout << "\nWelcome to the Event Management System\n"<< "Select Mode:\n"<< "1. Admin Mode\n"
             << "2. User Mode\n"<< "3. Exit\n"<< "Enter your choice: ";

        if (!(cin >> modeChoice)) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        clearInputBuffer();

        switch (modeChoice) {
            case 1:
                if (adminLogin()) {
                    adminMode(manager);
                } else {
                    cout << "Returning to the main menu due to failed login.\n";
                }
                break;
                
            case 2:
                userMode(manager);
                break;
                
            case 3:
                cout << "Exiting the system. Goodbye!\n";
                return 0;
                
            default:
                cout << "Invalid mode selected. Please try again.\n";
        }
    }

    return 0;
}
