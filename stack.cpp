#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Define a structure to represent administrative actions
struct Action {
    string actionType;  // e.g., "Add Participant", "Remove Event"
    string details;     // Details about the action, e.g., participant name, event name

    // Constructor for easy initialization
    Action(string type, string det) : actionType(type), details(det) {}
};

class AdminActions {
private:
    stack<Action> actionStack;  // Stack to store actions

public:
    // Function to add an action to the stack
    void performAction(const string& actionType, const string& details) {
        // Create a new action with the provided type and details
        Action newAction(actionType, details);
        // Push the action onto the stack
        actionStack.push(newAction);
        // Notify the user that the action has been performed
        cout << "Action performed: " << actionType << " - " << details << endl;
    }

    // Function to undo the last action
    void undoLastAction() {
        // Check if the stack is empty
        if (actionStack.empty()) {
            cout << "No actions to undo." << endl;
            return; // Exit if there are no actions to undo
        }
        // Retrieve the last action from the stack
        Action lastAction = actionStack.top();
        // Remove the last action from the stack
        actionStack.pop();
        // Notify the user of the undone action
        cout << "Undone action: " << lastAction.actionType << " - " << lastAction.details << endl;
    }

    // Function to display the current stack of actions
    void displayActions() {
        // Check if the stack is empty
        if (actionStack.empty()) {
            cout << "No actions in the stack." << endl;
            return; // Exit if there are no actions to display
        }

        // Create a temporary stack to iterate through the current actions
        stack<Action> tempStack = actionStack;
        cout << "Current actions in the stack:" << endl;
        while (!tempStack.empty()) {
            // Get the top action from the temporary stack
            Action action = tempStack.top();
            // Remove the action from the temporary stack
            tempStack.pop();
            // Display the action details
            cout << "- " << action.actionType << ": " << action.details << endl;
        }
    }
};

// Main function to demonstrate functionality
int main() {
    AdminActions admin;

    // Perform some actions
    admin.performAction("Add Participant", "John Doe"); // Add a participant named John Doe
    admin.performAction("Remove Event", "Tech Talk 2024"); // Remove an event named Tech Talk 2024
    admin.performAction("Add Participant", "Jane Smith"); // Add a participant named Jane Smith

    // Display current actions
    admin.displayActions();

    // Undo the last action
    admin.undoLastAction(); // Undo the action of adding Jane Smith

    // Display actions after undo
    admin.displayActions();

    return 0;
}
