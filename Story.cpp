
#define _CRT_SECURE_NO_WARNINGS
#include "Story.h"
#include <iostream>
using namespace std;

Story::Story(string user, string text) {
    userName = user;
    content  = text;
    next     = nullptr;
}

StoryManager::StoryManager() {
    tail  = nullptr;
    count = 0;
}

// Add story to circular linked list
void StoryManager::addStory(string user, string content) {
    Story* newStory = new Story(user, content);

    if (tail == nullptr) {
        // First node points to itself
        newStory->next = newStory;
        tail           = newStory;
    } else {
        // Insert after tail (i.e., at front of circle)
        newStory->next = tail->next;
        tail->next     = newStory;
        tail           = newStory;   // new node becomes tail
    }

    count++;
    cout << "Story added!\n";
}

// View all stories in circular list
void StoryManager::viewStories() {
    if (tail == nullptr) {
        cout << "No stories!\n";
        return;
    }

    cout << "\n=== Stories ===\n";
    Story* head   = tail->next;   // head of circular list
    Story* temp   = head;
    int    viewed = 0;

    do {
        cout << "\n  By    : " << temp->userName << "\n";
        cout <<   "  Story : " << temp->content  << "\n";
        temp = temp->next;
        viewed++;
    } while (temp != head && viewed < count);
}
