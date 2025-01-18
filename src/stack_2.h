class Stack {
private:
    Action* top;
public:
    Stack() : top(nullptr) {}
    ~Stack() { Clear(); }

    void Push(const string& actionType, const string& details) {
        Action* newAction = new Action{actionType, details, top};
        top = newAction;
    }

    Action* Pop() {
        if (!top) return nullptr;
        Action* result = top;
        top = top->next;
        return result;
    }

    void Clear() {
        while (top) {
            Action* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void Display() {
        if (!top) {
            cout << "No actions in stack." << endl;
            return;
        }
        Action* current = top;
        while (current) {
            cout << "Action: " << current->actionType << ", Details: " << current->details << endl;
            current = current->next;
        }
    }
};
