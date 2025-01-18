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
    EventManager() : eventCount(0), capacity(5) {
        events = new Event[capacity];
        waitingListSizes = new int[capacity]{};
        waitingLists = new Participant*[capacity]{};
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

int main() {
    EventManager manager;
    int choice;
    do {
        cout << "\nEvent Management System:\n"<< "1. Add Event\n"<< "2. Register Participant\n"
             << "3. Display All Events\n"<< "4. Search Event\n"<< "5. Sort Events\n"
             << "6. Undo Last Action\n"<< "7. Exit\n"<< "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addEvent();
                break;
            case 2:
                manager.registerParticipant();
                break;
            case 3:
                manager.displayAllEvents();
                break;
            case 4:
                manager.searchEvent();
                break;
            case 5:
                manager.sortEvents();
                break;
            case 6:
                manager.undoLastAction();
                break;
            case 7:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
