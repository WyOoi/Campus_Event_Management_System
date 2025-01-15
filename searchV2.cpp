#include <iostream>
#include <string>
using namespace std;

// Function to sort the event IDs using bubble sort
void bubbleSort(int ids[], string events[], int size) {
    for (int j = 0; j < size - 1; j++) {
        for (int i = 0; i < size - j - 1; i++) {
            // Compare adjacent event IDs
            if (ids[i] > ids[i + 1]) {
                // Swap event IDs
                int tempId = ids[i];
                ids[i] = ids[i + 1];
                ids[i + 1] = tempId;

                // Swap corresponding event names
                string tempEvent = events[i];
                events[i] = events[i + 1];
                events[i + 1] = tempEvent;
            }
        }
    }
}

// Function to display the events
void displayEvents(int ids[], string events[], int size) {
    cout << "Event List:\n";
    for (int i = 0; i < size; i++) {
        cout << "Event ID: " << ids[i] << " | Event Name: " << events[i] << endl;
    }
}

// Function to perform binary search on sorted event IDs
int binarySearch(int ids[], string events[], int size, int key) {
    int left = 0; // Initialize left boundary
    int right = size - 1; // Initialize right boundary

    while (left <= right) {
        int mid = (left + right) / 2; // Calculate middle index

        if (ids[mid] == key) {
            // If the key matches, return the index
            return mid;
        } else if (ids[mid] < key) {
            // If the key is greater, move the left boundary
            left = mid + 1;
        } else {
            // If the key is smaller, move the right boundary
            right = mid - 1;
        }
    }

    // If the key is not found, return -1
    return -1;
}

int main() {
    // Array of event IDs
    int eventIDs[] = {105, 101, 109, 103, 102};
    // Array of event names corresponding to the IDs
    string eventNames[] = {"Sports Day", "Tech Fest", "Music Night", "Art Exhibition", "Seminar"};
    int size = sizeof(eventIDs) / sizeof(eventIDs[0]); // Determine the size of the array

    // Sort events by ID for binary search
    bubbleSort(eventIDs, eventNames, size);

    // Display the sorted list of events
    displayEvents(eventIDs, eventNames, size);

    // Prompt the user to search for an event by ID
    int searchID;
    cout << "\nEnter the Event ID to search: ";
    cin >> searchID;

    // Perform binary search
    int result = binarySearch(eventIDs, eventNames, size, searchID);

    if (result != -1) {
        // If the event is found, display its details
        cout << "Event found!\n";
        cout << "Event ID: " << eventIDs[result] << " | Event Name: " << eventNames[result] << endl;
    } else {
        // If the event is not found, notify the user
        cout << "Event not found.\n";
    }

    return 0;
}
