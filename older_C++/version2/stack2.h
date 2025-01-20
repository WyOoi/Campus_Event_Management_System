#ifndef STACK_H
#define STACK_H

#include "event_structs.h"

// Stack class to store actions for undo functionality
class Stack {
public:
    Stack();  // Constructor
    ~Stack();  // Destructor

    void Push(const string& actionType, const string& details);
    void Clear();
    void Display();
    Action* Pop();

private:
    Action* top;  // Top pointer to the stack
};

#endif // STACK_H
