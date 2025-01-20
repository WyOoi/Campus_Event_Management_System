#ifndef UTILS_H
#define UTILS_H

#include <iostream>
using namespace std;

// Function to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// Admin login function
bool adminLogin() {
    string username, password;
    cout << "\nAdmin Login:\n" << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    const string adminUsername = "admin";
    const string adminPassword = "1234";

    if (username == adminUsername && password == adminPassword) {
        cout << "Login successful. Welcome, Admin!\n";
        clearInputBuffer();
        return true;
    } else {
        cout << "Invalid credentials. Access denied.\n";
        clearInputBuffer();
        return false;
    }
}

#endif // UTILS_H
