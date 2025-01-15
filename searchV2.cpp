#include <iostream>
#include <string>
using namespace std;

// Function to partition the array for quick sort
int partition(int ids[], string events[], int low, int high) {
    int pivot = ids[high]; // Choose the last element as the pivot
    int i = low - 1;       // Index of smaller element

    for (int j = low; j < high; j++) {
        if (ids[j] < pivot) { // If the current element is smaller than the pivot
            i++; // Increment the index of the smaller element
            
            // Swap ids
            swap(ids[i], ids[j]);
            // Swap corresponding events
            swap(events[i], events[j]);
        }
    }

    // Swap the pivot element with the element at i+1
    swap(ids[i + 1], ids[high]);
    swap(events[i + 1], events[high]);

    return i + 1; // Return the partitioning index
}

// Function to perform quick sort on the array
void quickSort(int ids[], string events[], int low, int high) {
    if (low < high) {
        int pi = partition(ids, events, low, high); // Partition index

        // Recursively sort elements before and after partition
        quickSort(ids, events, low, pi - 1);
        quickSort(ids, events, pi + 1, high);
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

    // Sort events by ID for binary search using quick sort
    quickSort(eventIDs, eventNames, 0, size - 1);

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
