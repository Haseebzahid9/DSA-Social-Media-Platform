
#define _CRT_SECURE_NO_WARNINGS
#include "Post.h"
#include "User.h"
#include <iostream>
using namespace std;

Post::Post(string id, string text, string user) {
    postID  = id;
    content = text;
    owner   = user;
    likes   = 0;
    next    = nullptr;
    prev    = nullptr;
}

PostManager::PostManager() {
    feedHead  = nullptr;
    feedTail  = nullptr;
    postCount = 0;
}

// Create a new post (added to front of feed)
void PostManager::createPost(string user, string content) {
    postCount++;
    string id = "P";
    // Build ID string manually (compatible with old VS)
    int n = postCount;
    string num = "";
    if (n == 0) {
        num = "0";
    } else {
        while (n > 0) {
            char c = '0' + (n % 10);
            num = c + num;
            n /= 10;
        }
    }
    id += num;

    Post* newPost = new Post(id, content, user);

    if (feedHead == nullptr) {
        feedHead = feedTail = newPost;
    } else {
        newPost->next   = feedHead;
        feedHead->prev  = newPost;
        feedHead        = newPost;
    }

    cout << "Post created with ID: " << id << "\n";
}

// Delete post by ID
void PostManager::deletePost(string postID) {
    Post* temp = feedHead;

    while (temp != nullptr) {
        if (temp->postID == postID) {
            if (temp->prev != nullptr) temp->prev->next = temp->next;
            else                       feedHead         = temp->next;

            if (temp->next != nullptr) temp->next->prev = temp->prev;
            else                       feedTail         = temp->prev;

            delete temp;
            cout << "Post deleted!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Post not found!\n";
}

// Display posts of a specific user
void PostManager::displayPosts(string user) {
    cout << "\nPosts by " << user << ":\n";
    Post* temp  = feedHead;
    bool  found = false;

    while (temp != nullptr) {
        if (temp->owner == user) {
            cout << "  ID      : " << temp->postID  << "\n";
            cout << "  Content : " << temp->content << "\n";
            cout << "  Likes   : " << temp->likes   << "\n";
            cout << "  ---\n";
            found = true;
        }
        temp = temp->next;
    }

    if (!found) cout << "  No posts found!\n";
}

// Show first 5 posts in feed
void PostManager::navigateFeed() {
    if (feedHead == nullptr) {
        cout << "Feed is empty!\n";
        return;
    }

    cout << "\n=== Feed (latest 5 posts) ===\n";
    Post* temp  = feedHead;
    int   count = 0;

    while (temp != nullptr && count < 5) {
        cout << "\n  ID      : " << temp->postID  << "\n";
        cout <<   "  By      : " << temp->owner   << "\n";
        cout <<   "  Content : " << temp->content << "\n";
        cout <<   "  Likes   : " << temp->likes   << "\n";
        temp = temp->next;
        count++;
    }
}

// Like a post
void PostManager::likePost(string postID) {
    Post* temp = feedHead;

    while (temp != nullptr) {
        if (temp->postID == postID) {
            temp->likes++;
            cout << "Post liked! Total likes: " << temp->likes << "\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Post not found!\n";
}

// Delete all posts belonging to a user
void PostManager::deleteUserPosts(string user) {
    Post* temp = feedHead;

    while (temp != nullptr) {
        Post* next = temp->next;
        if (temp->owner == user) {
            deletePost(temp->postID);
        }
        temp = next;
    }
}
