
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include "User.h"
#include "Graph.h"
#include "Post.h"
#include "Story.h"
#include "Notification.h"
#include "AVL.h"
#include "Message.h"

using namespace std;

// Global objects
UserTable         users;
Graph             socialGraph;
PostManager       posts;
StoryManager      stories;
NotificationQueue notifications;
AVLTree           userActivity;
AVLTree           postLikes;
MessageManager    msgManager;

// Simple timestamp using a counter (no unsafe ctime)
string getCurrentTime() {
    static int counter = 0;
    counter++;
    string s = "Event-";
    int n = counter;
    string num = "";
    if (n == 0) { num = "0"; }
    else { while (n > 0) { char c = '0' + (n % 10); num = c + num; n /= 10; } }
    return s + num;
}

// Check if a user is logged in
bool checkLogin() {
    if (currentUser == nullptr) {
        cout << "\nPlease login first!\n";
        return false;
    }
    return true;
}

// -------------------------------------------------------
// User Management Menu
// -------------------------------------------------------
void userMenu() {
    int choice;
    do {
        cout << "\n=== User Management ===\n";
        cout << "1. Register User\n";
        cout << "2. Login\n";
        cout << "3. Logout\n";
        cout << "4. Delete User\n";
        cout << "5. Search User\n";
        cout << "6. Display All Users\n";
        cout << "7. Back\n";
        cout << "Choice: ";
        cin  >> choice;

        string user, pass, email;

        switch (choice) {
            case 1:
                cout << "Username : ";
                cin  >> user;
                cout << "Password : ";
                cin  >> pass;
                cout << "Email    : ";
                cin  >> email;
                users.registerUser(user, pass, email);
                userActivity.insert(user, 0);
                break;

            case 2:
                cout << "Username : ";
                cin  >> user;
                cout << "Password : ";
                cin  >> pass;
                users.login(user, pass);
                break;

            case 3:
                if (currentUser != nullptr) {
                    cout << "Logged out: " << currentUser->userName << "\n";
                    currentUser = nullptr;
                } else {
                    cout << "No user is logged in.\n";
                }
                break;

            case 4:
                cout << "Username : ";
                cin  >> user;
                users.deleteUser(user);
                socialGraph.removeUser(user);
                posts.deleteUserPosts(user);
                userActivity.remove(user);
                break;

            case 5:
                cout << "Username : ";
                cin  >> user;
                if (users.searchUser(user) != nullptr)
                    cout << "User found!\n";
                else
                    cout << "User not found!\n";
                break;

            case 6:
                users.displayAll();
                break;

            default:
                if (choice != 7)
                    cout << "Invalid choice!\n";
        }
    } while (choice != 7);
}

// -------------------------------------------------------
// Social Network Menu
// -------------------------------------------------------
void socialMenu() {
    if (!checkLogin()) return;

    int choice;
    do {
        cout << "\n=== Social Network ===\n";
        cout << "1. Add Friend\n";
        cout << "2. Remove Friend\n";
        cout << "3. View My Friends\n";
        cout << "4. BFS Traversal\n";
        cout << "5. DFS Traversal\n";
        cout << "6. Back\n";
        cout << "Choice: ";
        cin  >> choice;

        string user;

        switch (choice) {
            case 1:
                cout << "Friend username: ";
                cin  >> user;
                if (users.searchUser(user) != nullptr)
                    socialGraph.addFriend(currentUser->userName, user);
                else
                    cout << "User not found!\n";
                break;

            case 2:
                cout << "Friend username: ";
                cin  >> user;
                socialGraph.removeFriend(currentUser->userName, user);
                break;

            case 3:
                socialGraph.displayFriends(currentUser->userName);
                break;

            case 4:
                socialGraph.BFS(currentUser->userName);
                break;

            case 5:
                socialGraph.DFS(currentUser->userName);
                break;

            default:
                if (choice != 6)
                    cout << "Invalid choice!\n";
        }
    } while (choice != 6);
}

// -------------------------------------------------------
// Posts & Feed Menu
// -------------------------------------------------------
void postsMenu() {
    if (!checkLogin()) return;

    int choice;
    do {
        cout << "\n=== Posts & Feed ===\n";
        cout << "1. Create Post\n";
        cout << "2. Delete Post\n";
        cout << "3. View My Posts\n";
        cout << "4. View Feed\n";
        cout << "5. Like Post\n";
        cout << "6. Back\n";
        cout << "Choice: ";
        cin  >> choice;

        string content, postID;

        switch (choice) {
            case 1:
                cout << "Content: ";
                cin.ignore();
                getline(cin, content);
                posts.createPost(currentUser->userName, content);
                userActivity.update(currentUser->userName,
                    userActivity.getValue(currentUser->userName) + 1);
                break;

            case 2:
                cout << "Post ID: ";
                cin  >> postID;
                posts.deletePost(postID);
                postLikes.remove(postID);
                break;

            case 3:
                posts.displayPosts(currentUser->userName);
                break;

            case 4:
                posts.navigateFeed();
                break;

            case 5:
                cout << "Post ID: ";
                cin  >> postID;
                posts.likePost(postID);
                postLikes.update(postID,
                    postLikes.getValue(postID) + 1);
                notifications.enqueue(
                    "Your post " + postID + " was liked!",
                    currentUser->userName,
                    getCurrentTime());
                break;

            default:
                if (choice != 6)
                    cout << "Invalid choice!\n";
        }
    } while (choice != 6);
}

// -------------------------------------------------------
// Stories Menu
// -------------------------------------------------------
void storiesMenu() {
    if (!checkLogin()) return;

    int choice;
    do {
        cout << "\n=== Stories ===\n";
        cout << "1. Add Story\n";
        cout << "2. View Stories\n";
        cout << "3. Back\n";
        cout << "Choice: ";
        cin  >> choice;

        string content;

        switch (choice) {
            case 1:
                cout << "Story content: ";
                cin.ignore();
                getline(cin, content);
                stories.addStory(currentUser->userName, content);
                break;

            case 2:
                stories.viewStories();
                break;

            default:
                if (choice != 3)
                    cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}

// -------------------------------------------------------
// Notifications Menu
// -------------------------------------------------------
void notificationsMenu() {
    if (!checkLogin()) return;

    int choice;
    do {
        cout << "\n=== Notifications ===\n";
        cout << "1. View Notifications\n";
        cout << "2. Process (Dequeue) Notification\n";
        cout << "3. Peek at Next\n";
        cout << "4. Back\n";
        cout << "Choice: ";
        cin  >> choice;

        switch (choice) {
            case 1:
                notifications.display();
                break;

            case 2:
                notifications.dequeue();
                break;

            case 3:
                notifications.peek();
                break;

            default:
                if (choice != 4)
                    cout << "Invalid choice!\n";
        }
    } while (choice != 4);
}

// -------------------------------------------------------
// Analytics & Ranking Menu
// -------------------------------------------------------
void analyticsMenu() {
    if (!checkLogin()) return;

    int choice;
    do {
        cout << "\n=== Analytics & Ranking ===\n";
        cout << "1. Top 5 Active Users\n";
        cout << "2. Most Liked Posts\n";
        cout << "3. Display All Activity Data\n";
        cout << "4. Back\n";
        cout << "Choice: ";
        cin  >> choice;

        switch (choice) {
            case 1:
                userActivity.showTopK(5);
                break;

            case 2:
                postLikes.showTopK(5);
                break;

            case 3:
                cout << "\nUser Activity:\n";
                userActivity.display();
                cout << "\nPost Likes:\n";
                postLikes.display();
                break;

            default:
                if (choice != 4)
                    cout << "Invalid choice!\n";
        }
    } while (choice != 4);
}

// -------------------------------------------------------
// Messaging Menu
// -------------------------------------------------------
void messagingMenu() {
    if (!checkLogin()) return;

    int choice;
    do {
        cout << "\n=== Messaging ===\n";
        cout << "1. Send Message\n";
        cout << "2. View Latest Message\n";
        cout << "3. Pop (Remove) Message\n";
        cout << "4. View Conversation\n";
        cout << "5. Back\n";
        cout << "Choice: ";
        cin  >> choice;

        string to, text;

        switch (choice) {
            case 1:
                cout << "To: ";
                cin  >> to;
                if (users.searchUser(to) != nullptr) {
                    cout << "Message: ";
                    cin.ignore();
                    getline(cin, text);
                    msgManager.sendMessage(currentUser->userName, to, text);
                    notifications.enqueue(
                        "New message from " + currentUser->userName,
                        to,
                        getCurrentTime());
                } else {
                    cout << "User not found!\n";
                }
                break;

            case 2:
                msgManager.viewLatest(currentUser->userName);
                break;

            case 3:
                msgManager.popMessage(currentUser->userName);
                break;

            case 4:
                msgManager.displayConvo(currentUser->userName);
                break;

            default:
                if (choice != 5)
                    cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

// -------------------------------------------------------
// MAIN
// -------------------------------------------------------
int main() {
    int choice;

    cout << "=============================================\n";
    cout << "      SOCIAL MEDIA PLATFORM  (DSA Project)  \n";
    cout << "=============================================\n";

    do {
        cout << "\n================ MAIN MENU =================\n";
        if (currentUser != nullptr)
            cout << "  Logged in as : " << currentUser->userName << "\n";
        else
            cout << "  Status       : Not logged in\n";

        cout << "1. User Management\n";
        cout << "2. Social Network\n";
        cout << "3. Posts & Feed\n";
        cout << "4. Stories\n";
        cout << "5. Notifications\n";
        cout << "6. Analytics & Ranking\n";
        cout << "7. Messaging\n";
        cout << "8. Exit\n";
        cout << "============================================\n";
        cout << "Choice: ";
        cin  >> choice;

        switch (choice) {
            case 1: userMenu();          break;
            case 2: socialMenu();        break;
            case 3: postsMenu();         break;
            case 4: storiesMenu();       break;
            case 5: notificationsMenu(); break;
            case 6: analyticsMenu();     break;
            case 7: messagingMenu();     break;
            case 8: cout << "\nThank you for using Social Media Platform!\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    system("pause");
    return 0;
}
