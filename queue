#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    int maxCapacity;
    cout << "Enter event capacity: ";
    cin >> maxCapacity;

    queue<string> registered, waitingList;
    int choice;
    string name;

    while (true) {
        cout << "\n1. Register Participant\n2. Cancel Registration\n3. View Registered\n4. View Waiting List\n5. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter name: ";
            getline(cin, name);
            if (registered.size() < maxCapacity) {
                registered.push(name);
                cout << name << " registered successfully!\n";
            } else {
                waitingList.push(name);
                cout << "Event full. " << name << " added to waiting list.\n";
            }
        } else if (choice == 2) {
            if (registered.empty()) {
                cout << "No registered participants to cancel.\n";
            } else {
                cout << "Cancelling registration for " << registered.front() << ".\n";
                registered.pop();
                if (!waitingList.empty()) {
                    registered.push(waitingList.front());
                    cout << waitingList.front() << " moved to registered list.\n";
                    waitingList.pop();
                }
            }
        } else if (choice == 3) {
            if (registered.empty()) {
                cout << "No registered participants.\n";
            } else {
                cout << "Registered Participants:\n";
                queue<string> temp = registered;
                while (!temp.empty()) {
                    cout << temp.front() << endl;
                    temp.pop();
                }
            }
        } else if (choice == 4) {
            if (waitingList.empty()) {
                cout << "No participants in waiting list.\n";
            } else {
                cout << "Waiting List:\n";
                queue<string> temp = waitingList;
                while (!temp.empty()) {
                    cout << temp.front() << endl;
                    temp.pop();
                }
            }
        } else if (choice == 5) {
            cout << "Exiting.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
