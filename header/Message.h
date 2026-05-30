#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
using namespace std;

// Message node (stack per conversation)
struct Message {
    string fromUser;
    string toUser;
    string text;
    string timestamp;
    Message* next;

    Message(string from, string to, string txt, string time);
};

// Conversation entry
struct Conversation {
    string user1;      // one end of chat
    string user2;      // other end of chat
    Message* msgStack; // top of stack = latest message
    Conversation* next;

    Conversation(string u1, string u2);
};

class MessageManager {
private:
    Conversation* head;

    // Returns conversation between u1 and u2 (order-independent)
    Conversation* findConvo(string u1, string u2);

public:
    MessageManager();
    void sendMessage(string from, string to, string text);
    void viewLatest(string user);
    void popMessage(string user);
    void displayConvo(string user);
};

#endif
