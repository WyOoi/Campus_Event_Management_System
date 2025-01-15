#include <iostream>
#include <string>
using namespace std;

// Participant class
class Participant {
private:
    string name;       // Name of the participant
    int id;            // Unique ID for the participant
    string contact;    // Contact information for the participant
    Participant* next; // Pointer to the next participant in the linked list

public:
    // Constructor to initialize a participant
    Participant(const string& name, int id, const string& contact)
        : name(name), id(id), contact(contact), next(nullptr) {}

    friend class Event; // Grant Event class access to private members
};

// Event class
class Event {
private:
    int id;                    // Unique ID for the event
    string name;               // Name of the event
    string category;           // Category of the event (e.g., sports, music)
    int maxCapacity;           // Maximum number of participants allowed
    int registeredCount;       // Current count of registered participants
    Participant* participants; // Linked list of registered participants
    Participant* waitlistFront;// Front of the waitlist queue
    Participant* waitlistRear; // Rear of the waitlist queue
    Event* next;               // Pointer to the next event in the linked list

public:
    // Constructor to initialize an event
    Event(int id, const string& name, const string& category, int maxCapacity)
        : id(id), name(name), category(category), maxCapacity(maxCapacity),
          registeredCount(0), participants(nullptr), waitlistFront(nullptr),
          waitlistRear(nullptr), next(nullptr) {}

    // Method to register a participant for the event
    void registerParticipant(const string& name, int id, const string& contact);

    // Method to display event details
    void displayEvent() const;

    friend class EventList; // Grant EventList class access to private members
};

// Action class for undo functionality
class Action {
private:
    string actionType; // Type of the action (e.g., "Add Event", "Register Participant")
    string details;    // Additional details about the action
    Action* next;      // Pointer to the next action in the stack

public:
    // Constructor to initialize an action
    Action(const string& actionType, const string& details, Action* next = nullptr)
        : actionType(actionType), details(details), next(next) {}

    friend class ActionStack; // Grant ActionStack class access to private members
};

// EventList class to manage the events
class EventList {
private:
    Event* head; // Head of the linked list for events

public:
    // Constructor to initialize the event list
    EventList() : head(nullptr) {}

    // Method to add an event to the list
    void addEvent(int id, const string& name, const string& category, int maxCapacity);

    // Method to search for an event by its ID
    Event* searchEvent(int id);

    // Method to display all events in the list
    void displayEvents() const;

    friend class ActionStack; // Grant ActionStack class access to private members
};

// ActionStack class for undo functionality
class ActionStack {
private:
    Action* top; // Top of the stack for undo functionality

public:
    // Constructor to initialize the action stack
    ActionStack() : top(nullptr) {}

    // Method to push an action onto the stack
    void pushAction(const string& actionType, const string& details);

    // Method to undo the last action
    void undoLastAction();
};

// Global variables
EventList eventList;   // List of events
ActionStack actionStack; // Stack for undo functionality

// Implementation of Event methods
void Event::registerParticipant(const string& name, int id, const string& contact) {
    // Check if the participant is already registered
    Participant* temp = participants;
    while (temp) {
        if (temp->id == id) {
            cout << "Participant with ID " << id << " is already registered for the event.\n";
            return;
        }
        temp = temp->next;
    }

    // Create a new participant
    Participant* newParticipant = new Participant(name, id, contact);

    // If there's space, register the participant directly
    if (registeredCount < maxCapacity) {
        if (!participants) {
            participants = newParticipant;
        } else {
            Participant* temp = participants;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newParticipant;
        }
        registeredCount++;
        cout << "Participant '" << name << "' registered successfully for event '" << this->name << "'.\n";
    } else {
        // Otherwise, add the participant to the waitlist
        if (!waitlistFront) {
            waitlistFront = waitlistRear = newParticipant;
        } else {
            waitlistRear->next = newParticipant;
            waitlistRear = newParticipant;
        }
        cout << "Event is fully booked. Participant '" << name << "' added to the waitlist.\n";
    }

    // Record the action for undo
    actionStack.pushAction("Register Participant", name);
}

void Event::displayEvent() const {
    // Display the event details
    cout << "Event ID: " << id << " | Name: " << name << " | Category: " << category
         << " | Capacity: " << registeredCount << "/" << maxCapacity << "\n";
}

// Implementation of EventList methods
void EventList::addEvent(int id, const string& name, const string& category, int maxCapacity) {
    // Create a new event
    Event* newEvent = new Event(id, name, category, maxCapacity);

    // Add the event to the end of the list
    if (!head) {
        head = newEvent;
    } else {
        Event* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newEvent;
    }

    // Record the action for undo
    actionStack.pushAction("Add Event", name);
    cout << "Event '" << name << "' added successfully.\n";
}

Event* EventList::searchEvent(int id) {
    // Search for the event by ID
    Event* temp = head;
    while (temp && temp->id != id) {
        temp = temp->next;
    }
    if (temp) {
        return temp;
    }
    cout << "Event with ID " << id << " not found.\n";
    return nullptr;
}

void EventList::displayEvents() const {
    // Display all events in the list
    Event* temp = head;
    while (temp) {
        temp->displayEvent();
        temp = temp->next;
    }
}

// Implementation of ActionStack methods
void ActionStack::pushAction(const string& actionType, const string& details) {
    // Push a new action onto the stack
    top = new Action(actionType, details, top);
}

void ActionStack::undoLastAction() {
    // Undo the last action
    if (!top) {
        cout << "No actions to undo.\n";
        return;
    }

    Action* temp = top;
    top = top->next;
    cout << "Undid action: " << temp->actionType << " (" << temp->details << ")\n";
    delete temp;
}

// Main function
int main() {
    int choice;

    while (true) {
        cout << "\nCampus Event Management System:\n";
        cout << "1. Add Event\n";
        cout << "2. Register Participant\n";
        cout << "3. Search Event\n";
        cout << "4. Undo Last Action\n";
        cout << "5. Display All Events\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, capacity;
                string name, category;
                cout << "Enter Event ID: ";
                cin >> id;
                cout << "Enter Event Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Event Category: ";
                getline(cin, category);
                cout << "Enter Max Capacity: ";
                cin >> capacity;
                eventList.addEvent(id, name, category, capacity);
                break;
            }
            case 2: {
                int eventId, participantId;
                string name, contact;
                cout << "Enter Event ID: ";
                cin >> eventId;
                cout << "Enter Participant Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Participant ID: ";
                cin >> participantId;
                cout << "Enter Contact Info: ";
                cin.ignore();
                getline(cin, contact);
                Event* event = eventList.searchEvent(eventId);
                if (event) {
                    event->registerParticipant(name, participantId, contact);
                }
                break;
            }
            case 3: {
                int eventId;
                cout << "Enter Event ID: ";
                cin >> eventId;
                Event* event = eventList.searchEvent(eventId);
                if (event) {
                    event->displayEvent();
                }
                break;
            }
            case 4:
                actionStack.undoLastAction();
                break;
            case 5:
                eventList.displayEvents();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
