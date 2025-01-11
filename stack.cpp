#include <iostream>
#include <string>
using namespace std;

// Define a structure for Actions (used in stack for undo functionality)
struct Action {
    string actionType; // Type of action (e.g., "Add Event", "Register Participant")
    string details;    // Details about the action (e.g., event or participant name)
    Action* next;      // Pointer to the next action in the stack
};

class Stack {
public:
    Stack();                // Default Constructor
    Stack(int stackSize);   // Parameterized Constructor (not utilized in this implementation)
    ~Stack();               // Destructor to clean up dynamically allocated memory
    void Push(const string& actionType, const string& details); // Push an action onto the stack
    Action* Pop();          // Remove and return the top action from the stack
    Action* Top();          // View the top action without removing it
    void Clear();           // Remove all actions from the stack
    void Display();         // Display all actions in the stack

private:
    Action* top;            // Pointer to the top of the stack
};

// Default Constructor
Stack::Stack() {
    top = nullptr; // Initialize the stack as empty
    cout << "Default constructor created\n";
}

// Parameterized Constructor (not utilized in this implementation)
Stack::Stack(int stackSize) {
    top = nullptr; // Initialize the stack as empty
    cout << "Second constructor created\n";
}

// Destructor
Stack::~Stack() {
    Clear(); // Ensure all dynamically allocated memory is freed
    cout << "Stack destroyed!\n";
}

// Method to Push an action onto the stack
void Stack::Push(const string& actionType, const string& details) {
    Action* newAction = new Action{actionType, details, top}; // Create a new action
    top = newAction; // Set the new action as the top of the stack
    cout << "Action pushed: " << actionType << " (" << details << ")\n";
}

// Method to Pop the top action from the stack
Action* Stack::Pop() {
    if (!top) { // Check if the stack is empty
        cout << "Stack Underflow\n";
        return nullptr;
    }

    Action* result = top; // Store the top action
    top = top->next; // Move the top pointer to the next action
    return result; // Return the removed action
}

// Method to View the top action without removing it
Action* Stack::Top() {
    if (!top) { // Check if the stack is empty
        cout << "Stack is empty\n";
        return nullptr;
    }

    return top; // Return the top action
}

// Method to Clear all actions from the stack
void Stack::Clear() {
    while (top) { // Iterate through all actions
        Action* temp = top; // Store the current top action
        top = top->next; // Move the top pointer to the next action
        delete temp; // Delete the current action
    }
    cout << "Stack cleared\n";
}

// Method to Display all actions in the stack
void Stack::Display() {
    if (!top) { // Check if the stack is empty
        cout << "Stack is empty\n";
        return;
    }

    cout << "Display of Stack:\n";
    Action* temp = top; // Start from the top of the stack
    while (temp) { // Traverse through all actions
        cout << "- " << temp->actionType << " (" << temp->details << ")\n";
        temp = temp->next; // Move to the next action
    }
}

// Main function to demonstrate stack functionality
void main() {
    Stack actionStack; // Create a stack instance

    // Push actions onto the stack
    actionStack.Push("Add Event", "Tech Talk 2024");
    actionStack.Push("Register Participant", "John Doe");
    actionStack.Push("Register Participant", "Jane Smith");

    // Display the stack
    actionStack.Display();

    // Pop an action from the stack
    Action* undoneAction = actionStack.Pop();
    if (undoneAction) { // Check if an action was successfully popped
        cout << "Undone action: " << undoneAction->actionType << " (" << undoneAction->details << ")\n";
        delete undoneAction; // Free the memory for the popped action
    }

    // Display the stack again
    actionStack.Display();

    // Clear the stack
    actionStack.Clear();
    actionStack.Display(); // Verify the stack is empty
}
