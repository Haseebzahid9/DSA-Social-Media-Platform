#ifndef AVL_H
#define AVL_H

#include <string>
using namespace std;

// AVL tree node
struct AVLNode {
    string key;
    int    value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(string k, int v);
};

class AVLTree {
private:
    AVLNode* root;

    int      getHeight(AVLNode* node);
    int      getBalance(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insertNode(AVLNode* node, string key, int val);
    AVLNode* deleteNode(AVLNode* node, string key);
    AVLNode* minNode(AVLNode* node);
    AVLNode* searchNode(AVLNode* node, string key);
    void     inorder(AVLNode* node);
    void     getTopK(AVLNode* node, int k, int& count);

public:
    AVLTree();
    void insert(string key, int val);
    void remove(string key);
    void update(string key, int val);
    void display();
    void showTopK(int k);
    int  getValue(string key);
};

#endif
