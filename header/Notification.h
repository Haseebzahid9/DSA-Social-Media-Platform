#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
using namespace std;

// Notification queue node
struct Notification {
    string message;
    string userName;
    string timestamp;
    Notification* next;

    Notification(string msg, string user, string time);
};

class NotificationQueue {
private:
    Notification* front;
    Notification* rear;
    int count;

public:
    NotificationQueue();
    void enqueue(string msg, string user, string time);
    void dequeue();
    void peek();
    void display();
};

#endif
