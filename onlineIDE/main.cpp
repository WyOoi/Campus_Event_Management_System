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
private:
    Action* top;
public:
    Stack() : top(nullptr) {}
    ~Stack() { Clear(); }

    void Push(const string& actionType, const string& details) {
        Action* newAction = new Action{actionType, details, top};
        top = newAction;
    }

    Action* Pop() {
        if (!top) return nullptr;
        Action* result = top;
        top = top->next;
        return result;
    }

    void Clear() {
        while (top) {
            Action* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void Display() {
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
};

class EventManager {
private:
    Event* events;
    int* waitingListSizes;
    Participant** waitingLists;
    int eventCount;
    int capacity;
    Stack actionStack;

    void resizeArray() {
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

    int partition(int ids[], int low, int high) {
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

    void quickSort(int ids[], int low, int high) {
        if (low < high) {
            int pi = partition(ids, low, high);
            quickSort(ids, low, pi - 1);
            quickSort(ids, pi + 1, high);
        }
    }

public:
    EventManager() : eventCount(0), capacity(10) { // Set initial capacity to 10
    events = new Event[capacity];
    waitingListSizes = new int[capacity](); // Initialize all sizes to 0
    waitingLists = new Participant*[capacity](); // Initialize all pointers to nullptr

    // Preload 10 events
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


    ~EventManager() {
        delete[] events;
        delete[] waitingListSizes;
        for (int i = 0; i < capacity; i++) {
            delete[] waitingLists[i];
        }
        delete[] waitingLists;
    }

    void addEvent() {
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
        waitingLists[eventCount] = nullptr;
        waitingListSizes[eventCount] = 0;
        eventCount++;

        actionStack.Push("Add Event", newEvent.name);
        cout << "Event added successfully!\n";
    }

    void registerParticipant() {
        int eventId;
        cout << "Enter Event ID: ";
        cin >> eventId;
        int index = -1;
        for (int i = 0; i < eventCount; i++) {
            if (events[i].id == eventId) {
                index = i;
                break;
            }
        }

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

        Participant* updatedList = new Participant[waitingListSizes[index] + 1];
        for (int i = 0; i < waitingListSizes[index]; i++) {
            updatedList[i] = waitingLists[index][i];
        }
        updatedList[waitingListSizes[index]] = newParticipant;

        delete[] waitingLists[index];
        waitingLists[index] = updatedList;
        waitingListSizes[index]++;

        actionStack.Push("Register Participant", newParticipant.name);
        cout << "Participant registered successfully!\n";
    }

    void displayAllEvents() {
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

    void searchEvent() {
        int searchId;
        cout << "Enter Event ID to search: ";
        cin >> searchId;

        for (int i = 0; i < eventCount; i++) {
            if (events[i].id == searchId) {
                cout << "Event Found: " << events[i].name << endl;
                return;
            }
        }
        cout << "Event not found.\n";
    }

    void sortEvents() {
        int* ids = new int[eventCount];
        for (int i = 0; i < eventCount; i++) {
            ids[i] = events[i].id;
        }

        quickSort(ids, 0, eventCount - 1);

        cout << "Sorted Events:\n";
        for (int i = 0; i < eventCount; i++) {
            cout << "Event ID: " << ids[i] << endl;
        }
        delete[] ids;
    }

    void undoLastAction() {
        Action* undoneAction = actionStack.Pop();
        if (undoneAction) {
            cout << "Undone Action: " << undoneAction->actionType << " - " << undoneAction->details << endl;
            delete undoneAction;
        } else {
            cout << "No actions to undo.\n";
        }
    }
};

// Function for admin login
bool adminLogin() {
    string username, password;
    cout << "\nAdmin Login:\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Replace these with your actual admin credentials
    const string adminUsername = "admin";
    const string adminPassword = "1234";

    if (username == adminUsername && password == adminPassword) {
        cout << "Login successful. Welcome, Admin!\n";
        return true;
    } else {
        cout << "Invalid credentials. Access denied.\n";
        return false;
    }
}

// Function to handle Admin Mode
void adminMode(EventManager &manager) {
    int choice;
    do {
        cout << "\nAdmin Menu:\n"
             << "1. Add Event\n"
             << "2. Display All Events\n"
             << "3. Search Event\n"
             << "4. Sort Events\n"
             << "5. Undo Last Action\n"
             << "6. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate input
        if (cin.fail()) {
            cin.clear(); // Clear error flags
            cin.ignore(1000, '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

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
                return; // Exit admin mode and return to the main menu
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
        cin >> choice;

        // Validate input
        if (cin.fail()) {
            cin.clear(); // Clear error flags
            cin.ignore(1000, '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                manager.registerParticipant();
                break;
            case 2:
                manager.displayAllEvents();
                break;
            case 3:
                cout << "Returning to the main menu...\n";
                return; // Exit user mode and return to the main menu
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}

// Main function
int main() {
    EventManager manager;
    int modeChoice;

    while (true) {
        // Main menu: selection of mode
        cout << "\nWelcome to the Event Management System\n";
        cout << "Select Mode:\n1. Admin Mode\n2. User Mode\n3. Exit\nEnter your choice: ";
        cin >> modeChoice;

        // Validate input
        if (cin.fail()) {
            cin.clear(); // Clear error flags
            cin.ignore(1000, '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (modeChoice == 3) { // Exit the system
            cout << "Exiting the system. Goodbye!\n";
            break;
        }

        if (modeChoice == 1) { // Admin mode
            if (!adminLogin()) {
                cout << "Returning to the main menu due to failed login.\n";
                continue;
            }
            adminMode(manager); // Enter Admin Mode
        } else if (modeChoice == 2) { // User mode
            userMode(manager); // Enter User Mode
        } else { // Invalid mode selection
            cout << "Invalid mode selected. Please try again.\n";
        }
    }

    return 0;
}
