#include <iostream>
#include <string>
using namespace std;

struct Event {
    string name;
    string date;
    string time;
    string location;
};

class EventManager {
private:
   
    Event* events;    // Dynamic array for storing events
    int eventCount;   // Number of events currently stored
    int capacity;     // Maximum number of events
    void resizeArray();// Function to resize the dynamic array when full

public:
    // Constructor
    EventManager();

    // Destructor
    ~EventManager();

    // Add an event
    void addEvent();

    // Display all events
    void displayAllEvents();

    // Update an event
    void updateEvent();

    // Delete an event
    void deleteEvent();
};

EventManager::EventManager() {
    capacity = 5;   // Initial capacity of the array
    events = new Event[capacity];
    eventCount = 0;
}

EventManager::~EventManager()
{
    delete[] events;
}

void EventManager::resizeArray() {
    capacity *= 2;
    Event* newEvents = new Event[capacity];
    for (int i = 0; i < eventCount; i++) {
        newEvents[i] = events[i];
    }
    delete[] events;
    events = newEvents;
}

void EventManager::addEvent() {
    if (eventCount == capacity) {
        resizeArray();
    }

    Event newEvent;
    cout << "Enter event name: ";
    cin.ignore();
    getline(cin, newEvent.name);
    cout << "Enter event date: ";
    getline(cin, newEvent.date);
    cout << "Enter event time: ";
    getline(cin, newEvent.time);
    cout << "Enter event location: ";
    getline(cin, newEvent.location);

    events[eventCount++] = newEvent;
    cout << "Event added successfully!" << endl;
}
// Display all events
void EventManager::displayAllEvents() {
    if (eventCount == 0) {
        cout << "No events available." << endl;
        return;
    }
    for (int i = 0; i < eventCount; i++) {
        cout << "\nEvent #" << i + 1 << endl;
        cout << "Name: " << events[i].name << endl;
        cout << "Date: " << events[i].date << endl;
        cout << "Time: " << events[i].time << endl;
        cout << "Location: " << events[i].location << endl;
        cout << "-----------------------------" << endl;
    }
}
void EventManager::updateEvent() {
    if (eventCount == 0) {
        cout << "No events available to update." << endl;
        return;
    }

    int eventNumber;
    cout << "Enter the event number to update: ";
    cin >> eventNumber;

    if (eventNumber < 1 || eventNumber > eventCount) {
        cout << "Invalid event number!" << endl;
        return;
    }

    Event& event = events[eventNumber - 1];
    cout << "Enter new event name (current: " << event.name << "): ";
    cin.ignore();
    getline(cin, event.name);
    cout << "Enter new event date (current: " << event.date << "): ";
    getline(cin, event.date);
    cout << "Enter new event time (current: " << event.time << "): ";
    getline(cin, event.time);
    cout << "Enter new event location (current: " << event.location << "): ";
    getline(cin, event.location);

    cout << "Event updated successfully!" << endl;
}
void EventManager::deleteEvent() {
    if (eventCount == 0) {
        cout << "No events available to delete." << endl;
        return;
    }

    int eventNumber;
    cout << "Enter the event number to delete: ";
    cin >> eventNumber;

    if (eventNumber < 1 || eventNumber > eventCount) {
        cout << "Invalid event number!" << endl;
        return;
    }

    for (int i = eventNumber - 1; i < eventCount - 1; i++) {
        events[i] = events[i + 1];
    }
    eventCount--;
    cout << "Event deleted successfully!" << endl;
}

int main() {
    EventManager manager;
    int choice = 0;

    for (;;) { // Infinite loop until the user decides to exit
        cout << "\nCampus Event Management System" << endl;
        cout << "1. Add Event" << endl;
        cout << "2. View All Events" << endl;
        cout << "3. Update Event" << endl;
        cout << "4. Delete Event" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            manager.addEvent();
        }
        else if (choice == 2) {
            manager.displayAllEvents();
        }
        else if (choice == 3) {
            manager.updateEvent();
        }
        else if (choice == 4) {
            manager.deleteEvent();
        }
        else if (choice == 5) {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
