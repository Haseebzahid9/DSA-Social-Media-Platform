
#define _CRT_SECURE_NO_WARNINGS
#include "Message.h"
#include <iostream>
using namespace std;

Message::Message(string from, string to, string txt, string time) {
    fromUser  = from;
    toUser    = to;
    text      = txt;
    timestamp = time;
    next      = nullptr;
}

Conversation::Conversation(string u1, string u2) {
    user1    = u1;
    user2    = u2;
    msgStack = nullptr;
    next     = nullptr;
}

MessageManager::MessageManager() {
    head = nullptr;
}

// Find conversation between two users (order-independent) -- BUG FIX
Conversation* MessageManager::findConvo(string u1, string u2) {
    Conversation* temp = head;
    while (temp != nullptr) {
        if ((temp->user1 == u1 && temp->user2 == u2) ||
            (temp->user1 == u2 && temp->user2 == u1)) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Send message
void MessageManager::sendMessage(string from, string to, string text) {
    Conversation* convo = findConvo(from, to);

    if (convo == nullptr) {
        convo        = new Conversation(from, to);
        convo->next  = head;
        head         = convo;
    }

    Message* newMsg  = new Message(from, to, text, "Now");
    newMsg->next     = convo->msgStack;
    convo->msgStack  = newMsg;

    cout << "Message sent to " << to << "!\n";
}

// View latest message in any conversation involving 'user'
void MessageManager::viewLatest(string user) {
    Conversation* temp = head;

    while (temp != nullptr) {
        if (temp->user1 == user || temp->user2 == user) {
            if (temp->msgStack != nullptr) {
                Message* latest = temp->msgStack;
                cout << "\nLatest message:\n";
                cout << "  From : " << latest->fromUser  << "\n";
                cout << "  To   : " << latest->toUser    << "\n";
                cout << "  Text : " << latest->text      << "\n";
                cout << "  Time : " << latest->timestamp << "\n";
                return;
            }
        }
        temp = temp->next;
    }

    cout << "No messages found!\n";
}

// Pop (remove) top message from first conversation of user
void MessageManager::popMessage(string user) {
    Conversation* temp = head;

    while (temp != nullptr) {
        if ((temp->user1 == user || temp->user2 == user) &&
             temp->msgStack != nullptr) {
            Message* top   = temp->msgStack;
            temp->msgStack = top->next;
            cout << "Message removed: " << top->text << "\n";
            delete top;
            return;
        }
        temp = temp->next;
    }

    cout << "No messages to remove!\n";
}

// Display full conversation between currentUser and another user
void MessageManager::displayConvo(string user) {
    cout << "\nEnter the other user's name to view conversation with: ";
    string other;
    cin >> other;

    Conversation* convo = findConvo(user, other);

    if (convo == nullptr || convo->msgStack == nullptr) {
        cout << "No conversation found with " << other << "!\n";
        return;
    }

    cout << "\n=== Conversation with " << other << " ===\n";
    Message* temp = convo->msgStack;

    while (temp != nullptr) {
        cout << "\n  From : " << temp->fromUser  << "\n";
        cout <<   "  Text : " << temp->text      << "\n";
        cout <<   "  Time : " << temp->timestamp << "\n";
        temp = temp->next;
    }
}
