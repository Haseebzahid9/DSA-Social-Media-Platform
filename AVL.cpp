
#define _CRT_SECURE_NO_WARNINGS
#include "AVL.h"
#include <iostream>
using namespace std;

// Helper: max of two ints
static int myMax(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode::AVLNode(string k, int v) {
    key    = k;
    value  = v;
    left   = nullptr;
    right  = nullptr;
    height = 1;
}

AVLTree::AVLTree() {
    root = nullptr;
}

int AVLTree::getHeight(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int AVLTree::getBalance(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x  = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left  = T2;

    y->height = myMax(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = myMax(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y  = x->right;
    AVLNode* T2 = y->left;

    y->left  = x;
    x->right = T2;

    x->height = myMax(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = myMax(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLNode* AVLTree::insertNode(AVLNode* node, string key, int val) {
    if (node == nullptr) {
        return new AVLNode(key, val);
    }

    if (key < node->key) {
        node->left = insertNode(node->left, key, val);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key, val);
    } else {
        // Duplicate key: update value
        node->value = val;
        return node;
    }

    node->height = myMax(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::insert(string key, int val) {
    root = insertNode(root, key, val);
}

AVLNode* AVLTree::minNode(AVLNode* node) {
    AVLNode* curr = node;
    while (curr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

AVLNode* AVLTree::deleteNode(AVLNode* node, string key) {
    if (node == nullptr) return node;

    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                delete node;
                node = nullptr;
            } else {
                *node = *temp;
                delete temp;
            }
        } else {
            AVLNode* temp = minNode(node->right);
            node->key   = temp->key;
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->key);
        }
    }

    if (node == nullptr) return node;

    node->height = myMax(getHeight(node->left), getHeight(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::remove(string key) {
    root = deleteNode(root, key);
}

AVLNode* AVLTree::searchNode(AVLNode* node, string key) {
    if (node == nullptr || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return searchNode(node->left, key);
    }
    return searchNode(node->right, key);
}

void AVLTree::update(string key, int val) {
    AVLNode* node = searchNode(root, key);
    if (node != nullptr) {
        node->value = val;
    } else {
        insert(key, val);
    }
}

void AVLTree::inorder(AVLNode* node) {
    if (node != nullptr) {
        inorder(node->left);
        cout << "  " << node->key << " : " << node->value << "\n";
        inorder(node->right);
    }
}

void AVLTree::display() {
    cout << "\n=== Analytics Data ===\n";
    if (root == nullptr) {
        cout << "  (empty)\n";
        return;
    }
    inorder(root);
}

// Reverse inorder gives descending order (highest value first by key)
void AVLTree::getTopK(AVLNode* node, int k, int& count) {
    if (node == nullptr || count >= k) return;

    getTopK(node->right, k, count);

    if (count < k) {
        cout << "  " << node->key << " : " << node->value << "\n";
        count++;
    }

    getTopK(node->left, k, count);
}

void AVLTree::showTopK(int k) {
    cout << "\n=== Top " << k << " ===\n";
    if (root == nullptr) {
        cout << "  (no data)\n";
        return;
    }
    int count = 0;
    getTopK(root, k, count);
}

int AVLTree::getValue(string key) {
    AVLNode* node = searchNode(root, key);
    if (node != nullptr) {
        return node->value;
    }
    return 0;
}
