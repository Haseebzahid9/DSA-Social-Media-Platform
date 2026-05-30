
#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <iostream>
using namespace std;

User* currentUser = nullptr;

User::User() {
    next     = nullptr;
    posts    = nullptr;
    activity = 0;
}

UserTable::UserTable() {
    for (int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
}

// Simple hash function
int UserTable::hash(string key) {
    int sum = 0;
    for (int i = 0; i < (int)key.size(); i++) {
        sum += (int)key[i];
    }
    return sum % SIZE;
}

// Register new user
void UserTable::registerUser(string user, string pass, string mail) {
    int idx = hash(user);

    // Check if already exists
    User* temp = table[idx];
    while (temp != nullptr) {
        if (temp->userName == user) {
            cout << "User already exists!\n";
            return;
        }
        temp = temp->next;
    }

    // Create new user
    User* newUser  = new User();
    newUser->userName = user;
    newUser->password = pass;
    newUser->email    = mail;
    newUser->next     = table[idx];
    table[idx]        = newUser;

    cout << "User registered successfully!\n";
}

// Login user
User* UserTable::login(string user, string pass) {
    int idx  = hash(user);
    User* temp = table[idx];

    while (temp != nullptr) {
        if (temp->userName == user && temp->password == pass) {
            currentUser = temp;
            cout << "Login successful! Welcome, " << user << "!\n";
            return temp;
        }
        temp = temp->next;
    }

    cout << "Invalid username or password!\n";
    return nullptr;
}

// Search user
User* UserTable::searchUser(string user) {
    int idx  = hash(user);
    User* temp = table[idx];

    while (temp != nullptr) {
        if (temp->userName == user) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Delete user
void UserTable::deleteUser(string user) {
    int idx  = hash(user);
    User* temp = table[idx];
    User* prev = nullptr;

    while (temp != nullptr) {
        if (temp->userName == user) {
            if (prev == nullptr) {
                table[idx] = temp->next;
            } else {
                prev->next = temp->next;
            }

            if (currentUser == temp) {
                currentUser = nullptr;
            }

            delete temp;
            cout << "User deleted!\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "User not found!\n";
}

// Display all users
void UserTable::displayAll() {
    cout << "\n=== All Users ===\n";
    bool found = false;
    for (int i = 0; i < SIZE; i++) {
        User* temp = table[i];
        while (temp != nullptr) {
            cout << "Username : " << temp->userName << "\n";
            cout << "Email    : " << temp->email    << "\n";
            cout << "---\n";
            temp  = temp->next;
            found = true;
        }
    }
    if (!found) {
        cout << "No users registered yet.\n";
    }
}

User** UserTable::getTable() {
    return table;
}

int UserTable::getSize() {
    return SIZE;
}
