#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

// User node structure
struct User {
    string userName;
    string password;
    string email;
    string bio;
    string lastActive;
    User* next;
    void* posts;  // Post list head
    int activity;

    User();
};

class UserTable {
private:
    static const int SIZE = 100;
    User* table[SIZE];
    int hash(string key);

public:
    UserTable();
    void registerUser(string user, string pass, string mail);
    User* login(string user, string pass);
    User* searchUser(string user);
    void deleteUser(string user);
    void displayAll();
    User** getTable();
    int getSize();
};

extern User* currentUser;  // Global current user

#endif
