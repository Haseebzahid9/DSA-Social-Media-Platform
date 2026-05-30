
#define _CRT_SECURE_NO_WARNINGS
#include "Notification.h"
#include <iostream>
using namespace std;

Notification::Notification(string msg, string user, string time) {
    message   = msg;
    userName  = user;
    timestamp = time;
    next      = nullptr;
}

NotificationQueue::NotificationQueue() {
    front = nullptr;
    rear  = nullptr;
    count = 0;
}

// Enqueue notification
void NotificationQueue::enqueue(string msg, string user, string time) {
    Notification* newNotif = new Notification(msg, user, time);

    if (rear == nullptr) {
        front = rear = newNotif;
    } else {
        rear->next = newNotif;
        rear       = newNotif;
    }

    count++;
    cout << "Notification queued!\n";
}

// Dequeue (process) first notification
void NotificationQueue::dequeue() {
    if (front == nullptr) {
        cout << "No notifications!\n";
        return;
    }

    Notification* temp = front;
    front              = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    cout << "Processed notification: " << temp->message << "\n";
    delete temp;
    count--;
}

// Peek at front notification
void NotificationQueue::peek() {
    if (front == nullptr) {
        cout << "No notifications!\n";
        return;
    }

    cout << "\nNext notification:\n";
    cout << "  To      : " << front->userName  << "\n";
    cout << "  Message : " << front->message   << "\n";
    cout << "  Time    : " << front->timestamp << "\n";
}

// Display all notifications
void NotificationQueue::display() {
    if (front == nullptr) {
        cout << "No notifications!\n";
        return;
    }

    cout << "\n=== Notifications (" << count << ") ===\n";
    Notification* temp = front;

    while (temp != nullptr) {
        cout << "\n  To      : " << temp->userName  << "\n";
        cout <<   "  Message : " << temp->message   << "\n";
        cout <<   "  Time    : " << temp->timestamp << "\n";
        temp = temp->next;
    }
}
