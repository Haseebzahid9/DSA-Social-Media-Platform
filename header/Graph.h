#ifndef GRAPH_H
#define GRAPH_H

#include <string>
using namespace std;

// Edge node for adjacency list
struct Edge {
    string friendName;
    Edge*  next;

    Edge(string name);
};

// Graph vertex
struct Vertex {
    string userName;
    Edge*  edges;
    Vertex* next;

    Vertex(string name);
};

class Graph {
private:
    Vertex* head;

public:
    Graph();
    Vertex* findVertex(string user);   // public so DFS helper can use it
    void addFriend(string user1, string user2);
    void removeFriend(string user1, string user2);
    void displayFriends(string user);
    void BFS(string start);
    void DFS(string start);
    void removeUser(string user);
};

#endif
