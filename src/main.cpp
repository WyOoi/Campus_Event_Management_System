#include <iostream>
#include <string>
#include <stack_2.h>
#include <eventmanager.h>
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
