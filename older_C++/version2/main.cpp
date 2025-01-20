#include "event_manager.h"
#include "admin_user_mode.h"
#include "utils.h"

int main() {
    EventManager manager;
    int modeChoice;

    while (true) {
        cout << "\nWelcome to the Event Management System\n" << "Select Mode:\n" << "1. Admin Mode\n"
             << "2. User Mode\n" << "3. Exit\n" << "Enter your choice: ";

        if (!(cin >> modeChoice)) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        clearInputBuffer();

        switch (modeChoice) {
            case 1:
                if (adminLogin()) {
                    adminMode(manager);  // Handle admin actions
                } else {
                    cout << "Returning to the main menu due to failed login.\n";
                }
                break;
                
            case 2:
                userMode(manager);  // Handle user actions
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
