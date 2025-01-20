#ifndef ADMIN_USER_MODE_H
#define ADMIN_USER_MODE_H

#include "event_manager.h"

// Function to handle Admin Mode
void adminMode(EventManager &manager) {
    int choice;
    do {
        cout << "\nAdmin Menu:\n" << "1. Add Event\n" << "2. Display All Events\n" << "3. Search Event\n"
             << "4. Sort Events\n" << "5. Undo Last Action\n" << "6. Back to Main Menu\n";
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
        cout << "\nUser Menu:\n" << "1. Register Participant\n" << "2. Display All Events\n" << "3. Back to Main Menu\n";
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

#endif // ADMIN_USER_MODE_H
