#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;

    explicit Node(T _data, Node* _left = nullptr, Node* _right = nullptr) : data(_data), left(_left), right(_right) {}
};

#endif //NODE_H
