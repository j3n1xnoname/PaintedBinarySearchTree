#ifndef TREE_H
#define TREE_H

#include "Node.h"

#include <iostream>
#include <queue>

template <typename T>
class Tree {
    static void postOrderHelper(Node<T>* cur);
    static void inOrderHelper(Node<T>* cur);
    static void preOrderHelper(Node<T>* cur);
    static int getHeightHelper(Node<T>* cur, int curHeight = 0);
    static Node<T>* findElemHelper(Node<T>* cur, T elem);
    static void clearHelper(Node<T>* &cur);

    Node<T>* root;
public:
    Tree() : root(nullptr) {}

    void addEl(T elem);
    void delEl(T elem);

    void printPostOrder() const;
    void printInOrder() const;
    void printPreOrder() const;
    void printBfs() const;

    Node<T>* getRoot() const { return root; }


    void clear();

    [[nodiscard]] Node<T>* findElem(T elem) const;

    ~Tree();

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] T minEl() const;
    [[nodiscard]] T maxEl() const;
};

template <typename T>
void Tree<T>::printBfs() const {
    if (root == nullptr) {
        return;
    }
    Node<T>* cur = root;
    std::queue<Node<T>*> q;
    q.push(cur);
    // Node count on current line
    int curNodeCount = 1;
    // Node count on next line
    int tempNodeCount;
    while (!q.empty()) {
        tempNodeCount = 0;
        while (curNodeCount) {
            cur = q.front();
            q.pop();
            std::cout << cur->data << " ";
            if (cur->left != nullptr) {
                tempNodeCount++;
                q.push(cur->left);
            }
            if (cur->right != nullptr) {
                tempNodeCount++;
                q.push(cur->right);
            }
            curNodeCount--;
        }

        curNodeCount = tempNodeCount;
        std::cout << '\n';
    }
}

template <typename T>
void Tree<T>::clearHelper(Node<T>*& cur) {
    if (cur->left == nullptr && cur->right == nullptr) {
        delete cur;
        cur = nullptr;
        return;
    }

    if (cur->left != nullptr) {
        clearHelper(cur->left);
    }
    if (cur->right != nullptr) {
        clearHelper(cur->right);
    }
    delete cur;
    cur = nullptr;
}

template <typename T>
void Tree<T>::clear() {
    if (root == nullptr) {
        return;
    }
    clearHelper(root);
}

template <typename T>
Tree<T>::~Tree() {
    clear();
}

template <typename T>
Node<T>* Tree<T>::findElemHelper(Node<T>* cur, T elem) {
    if (cur->left == nullptr && cur->right == nullptr) {
        if (cur->data == elem) {
            return cur;
        }
        return nullptr;
    }

    if (cur->data == elem) {
        return cur;
    }

    if (cur->left != nullptr && elem < cur->data) {
        return findElemHelper(cur->left, elem);
    }
    if (cur->right != nullptr && elem > cur->data) {
        return findElemHelper(cur->right, elem);
    }

    return nullptr;
}

template <typename T>
Node<T>* Tree<T>::findElem(T elem) const {
    if (root == nullptr) {
        return nullptr;
    }
    return findElemHelper(root, elem);
}

template <typename T>
int Tree<T>::getHeightHelper(Node<T>* cur, int curHeight) {
    if (cur->left == nullptr && cur->right == nullptr) {
        return curHeight;
    }
    int leftHeight = curHeight;
    int rightHeight = curHeight;
    if (cur->left != nullptr) {
        leftHeight = getHeightHelper(cur->left, curHeight + 1);
    }
    if (cur->right != nullptr) {
        rightHeight = getHeightHelper(cur->right, curHeight + 1);
    }

    return std::max(leftHeight, rightHeight);
}

template <typename T>
int Tree<T>::getHeight() const {
    if (root == nullptr) {
        return -1;
    }
    return getHeightHelper(root);
}

template <typename T>
void Tree<T>::preOrderHelper(Node<T>* cur) {
    if (cur->left == nullptr && cur->right == nullptr) {
        std::cout << cur->data << " ";
        return;
    }

    std::cout << cur->data << " ";
    if (cur->left != nullptr) {
        preOrderHelper(cur->left);
    }
    if (cur->right != nullptr) {
        preOrderHelper(cur->right);
    }
}

template <typename T>
void Tree<T>::printPreOrder() const {
    if (root == nullptr) {
        return;
    }
    preOrderHelper(root);
}

template <typename T>
void Tree<T>::inOrderHelper(Node<T>* cur) {
    if (cur->left == nullptr && cur->right == nullptr) {
        std::cout << cur->data << " ";
        return;
    }

    if (cur->left != nullptr) {
        inOrderHelper(cur->left);
    }
    std::cout << cur->data << " ";
    if (cur->right != nullptr) {
        inOrderHelper(cur->right);
    }
}

template <typename T>
void Tree<T>::printInOrder() const {
    if (root == nullptr) {
        return;
    }
    inOrderHelper(root);
}

template <typename T>
void Tree<T>::postOrderHelper(Node<T>* cur) {
    if (cur->left == nullptr && cur->right == nullptr) {
        std::cout << cur->data << " ";
        return;
    }

    if (cur->left != nullptr) {
        postOrderHelper(cur->left);
    }
    if (cur->right != nullptr) {
        postOrderHelper(cur->right);
    }

    std::cout << cur->data << " ";
}

template <typename T>
void Tree<T>::printPostOrder() const {
    if (root == nullptr) {
        return;
    }
    postOrderHelper(root);
}

template <typename T>
void Tree<T>::delEl(T elem) {
    Node<T>* cur = root;
    Node<T>* parent = root;
    while (cur != nullptr && cur->data != elem) {
        parent = cur;
        if (elem < cur->data) {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
    // If the element doesn't exist
    if (cur == nullptr) {
        return;
    }

    // Deleting the sheet (+)
    if (cur->left == nullptr && cur->right == nullptr) {
        if (parent->left == cur) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }

        delete cur;
    }
    // Two children
    else if (cur->left != nullptr && cur->right != nullptr) {
        Node<T>* temp = cur->right;
        // Case when temp is the sheet
        if (temp->left == nullptr && temp->right == nullptr) {
            std::swap(cur->data, temp->data);
            delete temp;
            cur->right = nullptr;
        }
        // Case when temp has two children or temp has only left child
        else if ((temp->left != nullptr && temp->right != nullptr) || (temp->left != nullptr && temp->right == nullptr)) {
            Node<T>* parentTemp = temp;
            while (temp->left != nullptr) {
                parentTemp = temp;
                temp = temp->left;
            }
            std::swap(cur->data, temp->data);
            delete temp;
            parentTemp->left = nullptr;
        }
        // Case when temp has only right child
        else {
            std::swap(cur->data, temp->data);
            cur->right = temp->right;
            delete temp;
        }
    }
    // Only one child
    else {
        if (cur->right != nullptr) {
            if (parent->left == cur) {
                parent->left = cur->right;
            }
            else {
                parent->right = cur->right;
            }
        }
        else {
            if (parent->left == cur) {
                parent->left = cur->left;
            }
            else {
                parent->right = cur->left;
            }
        }
        delete cur;
    }
}

template <typename T>
T Tree<T>::minEl() const {
    if (root == nullptr) {
        return {};
    }
    Node<T>* cur = root;
    while (cur->left != nullptr) {
        cur = cur->left;
    }

    return cur->data;
}

template <typename T>
T Tree<T>::maxEl() const {
    if (root == nullptr) {
        return {};
    }
    Node<T>* cur = root;
    while  (cur->right != nullptr) {
        cur = cur->right;
    }

    return cur->data;
}

template <typename T>
void Tree<T>::addEl(T elem) {
    if (root == nullptr) {
        root = new Node<T>(elem);
        return;
    }

    Node<T>* cur = root;
    while (cur != nullptr) {
        if (elem < cur->data) {
            if (cur->left == nullptr) {
                cur->left = new Node<T>(elem);
                break;
            }
            cur = cur->left;
        }
        else {
            if (cur->right == nullptr) {
                cur->right = new Node<T>(elem);
                break;
            }
            cur = cur->right;
        }
    }
}

#endif //TREE_H

// Rewrite check that tree is empty with exceptions