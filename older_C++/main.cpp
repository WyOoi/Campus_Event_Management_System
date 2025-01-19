#include <iostream>
#include <string>
#include "eventmanager.h"
using namespace std;

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
