#ifndef STORY_H
#define STORY_H

#include <string>
using namespace std;

// Story node (circular linked list)
struct Story {
    string userName;
    string content;
    Story* next;

    Story(string user, string text);
};

class StoryManager {
private:
    Story* tail;   // tail->next = head (circular)
    int    count;

public:
    StoryManager();
    void addStory(string user, string content);
    void viewStories();
};

#endif
