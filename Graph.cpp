
#define _CRT_SECURE_NO_WARNINGS
#include "Graph.h"
#include <iostream>
#include <queue>
using namespace std;

// ---- Simple string-based visited list ----
static const int MAX_VISITED = 200;

static bool isVisited(string visited[], int vCount, string name) {
    for (int i = 0; i < vCount; i++) {
        if (visited[i] == name) return true;
    }
    return false;
}

// ------------------------------------------

Edge::Edge(string name) {
    friendName = name;
    next       = nullptr;
}

Vertex::Vertex(string name) {
    userName = name;
    edges    = nullptr;
    next     = nullptr;
}

Graph::Graph() {
    head = nullptr;
}

Vertex* Graph::findVertex(string user) {
    Vertex* temp = head;
    while (temp != nullptr) {
        if (temp->userName == user) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Add friend (undirected edge)
void Graph::addFriend(string user1, string user2) {
    Vertex* v1 = findVertex(user1);
    Vertex* v2 = findVertex(user2);

    if (v1 == nullptr) {
        v1        = new Vertex(user1);
        v1->next  = head;
        head      = v1;
    }

    if (v2 == nullptr) {
        v2        = new Vertex(user2);
        v2->next  = head;
        head      = v2;
    }

    // Check if already friends
    Edge* e = v1->edges;
    while (e != nullptr) {
        if (e->friendName == user2) {
            cout << "Already friends!\n";
            return;
        }
        e = e->next;
    }

    // user1 -> user2
    Edge* e1  = new Edge(user2);
    e1->next  = v1->edges;
    v1->edges = e1;

    // user2 -> user1
    Edge* e2  = new Edge(user1);
    e2->next  = v2->edges;
    v2->edges = e2;

    cout << "Friend added!\n";
}

// Remove friend (undirected)
void Graph::removeFriend(string user1, string user2) {
    Vertex* v1 = findVertex(user1);
    Vertex* v2 = findVertex(user2);

    if (v1 == nullptr || v2 == nullptr) {
        cout << "User not found!\n";
        return;
    }

    // Remove from v1's list
    Edge* temp = v1->edges;
    Edge* prev = nullptr;
    while (temp != nullptr) {
        if (temp->friendName == user2) {
            if (prev == nullptr) v1->edges  = temp->next;
            else                 prev->next = temp->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    // Remove from v2's list
    temp = v2->edges;
    prev = nullptr;
    while (temp != nullptr) {
        if (temp->friendName == user1) {
            if (prev == nullptr) v2->edges  = temp->next;
            else                 prev->next = temp->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "Friend removed!\n";
}

// Display friends list
void Graph::displayFriends(string user) {
    Vertex* v = findVertex(user);
    if (v == nullptr) {
        cout << "User has no connections yet.\n";
        return;
    }

    cout << "\nFriends of " << user << ":\n";
    Edge* temp  = v->edges;
    bool  found = false;
    while (temp != nullptr) {
        cout << "  - " << temp->friendName << "\n";
        temp  = temp->next;
        found = true;
    }
    if (!found) cout << "  (none)\n";
}

// BFS traversal — properly marks visited nodes
void Graph::BFS(string start) {
    Vertex* v = findVertex(start);
    if (v == nullptr) {
        cout << "User not found in graph!\n";
        return;
    }

    cout << "\nBFS from " << start << ":\n";

    string visited[MAX_VISITED];
    int    vCount = 0;

    queue<string> q;
    q.push(start);
    visited[vCount++] = start;

    while (!q.empty()) {
        string curr = q.front();
        q.pop();

        cout << "  " << curr << "\n";

        Vertex* currV = findVertex(curr);
        if (currV == nullptr) continue;

        Edge* e = currV->edges;
        while (e != nullptr) {
            if (!isVisited(visited, vCount, e->friendName)) {
                visited[vCount++] = e->friendName;
                q.push(e->friendName);
            }
            e = e->next;
        }
    }
}

// DFS recursive helper — uses visited array correctly
static void dfsHelper(string user, string visited[], int& vCount, Graph* g) {
    cout << "  " << user << "\n";

    Vertex* v = g->findVertex(user);
    if (v == nullptr) return;

    Edge* e = v->edges;
    while (e != nullptr) {
        if (!isVisited(visited, vCount, e->friendName)) {
            visited[vCount++] = e->friendName;
            dfsHelper(e->friendName, visited, vCount, g);
        }
        e = e->next;
    }
}

// DFS traversal
void Graph::DFS(string start) {
    Vertex* v = findVertex(start);
    if (v == nullptr) {
        cout << "User not found in graph!\n";
        return;
    }

    cout << "\nDFS from " << start << ":\n";

    string visited[MAX_VISITED];
    int    vCount         = 0;
    visited[vCount++]     = start;

    dfsHelper(start, visited, vCount, this);
}

// Remove a user vertex and all its edges
void Graph::removeUser(string user) {
    // Remove edges pointing to 'user' from other vertices
    Vertex* temp = head;
    while (temp != nullptr) {
        if (temp->userName != user) {
            Edge* e    = temp->edges;
            Edge* prev = nullptr;
            while (e != nullptr) {
                if (e->friendName == user) {
                    if (prev == nullptr) temp->edges = e->next;
                    else                 prev->next  = e->next;
                    Edge* del = e;
                    e = e->next;
                    delete del;
                } else {
                    prev = e;
                    e    = e->next;
                }
            }
        }
        temp = temp->next;
    }

    // Remove the vertex itself
    temp       = head;
    Vertex* prev = nullptr;
    while (temp != nullptr) {
        if (temp->userName == user) {
            if (prev == nullptr) head       = temp->next;
            else                 prev->next = temp->next;

            Edge* e = temp->edges;
            while (e != nullptr) {
                Edge* next = e->next;
                delete e;
                e = next;
            }
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}
