#include <iostream>
#include <string>
using namespace std;

// Define a structure for Actions (used in stack for undo functionality)
struct Action {
    string actionType; // Type of action (e.g., "Add Event", "Register Participant")
    string details;    // Details about the action (e.g., event or participant name)
    Action* next;      // Pointer to the next action in the stack
};

// Top of the stack for undo functionality
Action* actionStack = nullptr;

// Function to record an action on the stack
void recordAction(const string& actionType, const string& details) {
    Action* newAction = new Action{actionType, details, actionStack};
    actionStack = newAction;
}

// Function to undo the last action
void undoLastAction() {
    if (!actionStack) { // Check if the stack is empty
        cout << "No actions to undo.\n";
        return;
    }

    // Retrieve and remove the top action from the stack
    Action* temp = actionStack;
    actionStack = actionStack->next;

    // Display the undone action
    cout << "Undid action: " << temp->actionType << " (" << temp->details << ")\n";

    // Free the memory for the removed action
    delete temp;
}
