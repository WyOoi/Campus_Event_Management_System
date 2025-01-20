#ifndef EVENT_STRUCTS_H
#define EVENT_STRUCTS_H

#include <string>
using namespace std;

// Structure for storing event details
struct Event {
    int id;
    string name;
    string date;
    string time;
    string location;
};

// Structure for storing participant details
struct Participant {
    string name;
    string contact;
};

// Structure to represent an action performed (for undo functionality)
struct Action {
    string actionType;
    string details;
    Action* next;
};

#endif // EVENT_STRUCTS_H
