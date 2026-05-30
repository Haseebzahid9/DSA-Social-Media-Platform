# 📱 Social Media Platform — DSA Project

A **console-based social media application** built in **C++** that demonstrates core Data Structures and Algorithms concepts through a fully functional social network simulation.

---

## 📌 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Data Structures Used](#data-structures-used)
- [Project Structure](#project-structure)
- [How to Compile & Run](#how-to-compile--run)
- [Modules](#modules)
- [Sample Menu Flow](#sample-menu-flow)

---

## Overview

This project simulates a social media platform with real-world features like user registration, friend connections, posts, stories, notifications, messaging, and activity analytics — all implemented using fundamental data structures such as **Hash Tables**, **Graphs**, **AVL Trees**, **Queues**, and **Stacks**.

---

## Features

| Module | Functionality |
|---|---|
| 👤 User Management | Register, Login, Logout, Delete, Search, Display All |
| 🤝 Social Network | Add/Remove Friends, View Friends, BFS & DFS Traversal |
| 📝 Posts & Feed | Create/Delete Posts, View Feed, Like Posts |
| 📖 Stories | Add & View Stories |
| 🔔 Notifications | Enqueue, Dequeue, Peek Notifications |
| 📊 Analytics | Top 5 Active Users, Most Liked Posts, Activity Data |
| 💬 Messaging | Send Messages, View Latest, Pop Message, View Conversation |

---

## Data Structures Used

| Data Structure | Used For |
|---|---|
| **Hash Table** | Storing and searching users efficiently (`UserTable`) |
| **Graph (Adjacency List)** | Friend connections between users (`Graph`) |
| **AVL Tree** | Ranking users by activity and posts by likes (`AVLTree`) |
| **Queue** | Notification system — FIFO order (`NotificationQueue`) |
| **Stack** | Messaging — view latest / pop message (`MessageManager`) |
| **Linked List** | Internal chaining in hash table, adjacency list edges |

---

## Project Structure

```
Dsa social media/
│
├── main.cpp               # Entry point — all menus and program flow
│
├── User.cpp / User.h      # User struct, hash table (register, login, search, delete)
├── Graph.cpp / Graph.h    # Friend graph with BFS and DFS traversal
├── AVL.cpp / AVL.h        # AVL tree for activity ranking and post likes
├── Post.cpp / Post.h      # Post creation, deletion, feed navigation, likes
├── Story.cpp / Story.h    # Story add and view
├── Notification.cpp / Notification.h  # Queue-based notification system
├── Message.cpp / Message.h            # Stack-based messaging system
│
└── header/                # All header files (.h)
    ├── AVL.h
    ├── Graph.h
    ├── Message.h
    ├── Notification.h
    ├── Post.h
    ├── Story.h
    └── User.h
```

---

## How to Compile & Run

### Using g++ (Recommended)

```bash
g++ main.cpp User.cpp Graph.cpp AVL.cpp Post.cpp Story.cpp Notification.cpp Message.cpp -o social_media
./social_media
```

### Using Visual Studio / Dev-C++

1. Create a new **C++ project**
2. Add all `.cpp` files to the project
3. Make sure the `header/` folder is in the include path
4. Build and Run

> ⚠️ The project uses `system("pause")` — works on Windows. On Linux/Mac, remove or replace that line in `main.cpp`.

---

## Modules

### 👤 User Management
- Uses a **Hash Table** (array of size 100) with chaining via linked list
- Supports: `registerUser`, `login`, `searchUser`, `deleteUser`, `displayAll`
- A global `currentUser` pointer tracks the logged-in session

### 🤝 Social Network (Graph)
- **Undirected Graph** using adjacency list
- `addFriend` / `removeFriend` — updates both users' edge lists
- `BFS` (Breadth-First Search) and `DFS` (Depth-First Search) traversals from the current user

### 📝 Posts & Feed
- Posts are linked per user
- `likePost` increments the like count in the AVL Tree and pushes a notification
- `navigateFeed` lets users browse posts

### 🔔 Notifications
- **Queue** structure — new notifications are enqueued, processed in FIFO order
- Notifications are triggered on post likes and new messages

### 📊 Analytics (AVL Tree)
- Two AVL Trees: one for **user activity scores**, one for **post like counts**
- `showTopK(5)` traverses the tree in-order and returns top K entries

### 💬 Messaging (Stack)
- Messages per conversation stored in a stack
- `viewLatest` peeks at the top; `popMessage` removes it
- Sending a message also triggers a notification to the recipient

---

## Sample Menu Flow

```
=============================================
      SOCIAL MEDIA PLATFORM  (DSA Project)
=============================================

================ MAIN MENU =================
  Status       : Not logged in
1. User Management
2. Social Network
3. Posts & Feed
4. Stories
5. Notifications
6. Analytics & Ranking
7. Messaging
8. Exit
============================================
```

---

## 👨‍💻 Built With

- **Language:** C++
- **Paradigm:** Object-Oriented Programming + Data Structures
- **IDE:** Visual Studio / Dev-C++ / g++

---

## 📚 Concepts Demonstrated

- Hash Table with chaining
- Graph traversal (BFS & DFS)
- AVL Tree (self-balancing BST) with insert, delete, update, and top-K query
- Queue for event-driven notifications
- Stack-based messaging
- Modular OOP design with header/source separation
