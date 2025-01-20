#ifndef QUEUE_H
#define QUEUE_H

#include "event_structs.h"

// Queue class to manage the list of participants for each event
class Queue {
public:
    Queue(int queueSize);  // Constructor
    ~Queue();  // Destructor
    void Insert(Participant newParticipant);
    Participant Remove();
    bool isEmpty();
    void Display();

private:
    Participant* array;
    int front;
    int rear;
    int count;
    int arraySize;
};

#endif // QUEUE_H
