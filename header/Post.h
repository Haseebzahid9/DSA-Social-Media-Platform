#ifndef POST_H
#define POST_H

#include <string>
using namespace std;

// Doubly-linked post node
struct Post {
    string postID;
    string content;
    string owner;
    int    likes;
    Post*  next;
    Post*  prev;

    Post(string id, string text, string user);
};

class PostManager {
private:
    Post* feedHead;
    Post* feedTail;
    int   postCount;

public:
    PostManager();
    void createPost(string user, string content);
    void deletePost(string postID);
    void displayPosts(string user);
    void navigateFeed();
    void likePost(string postID);
    void deleteUserPosts(string user);
};

#endif
