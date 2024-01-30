#include "bst.h"

BST::Node::Node(int value, Node* left, Node* right):
    value{value}, left{left}, right{right}{}

BST::Node::Node():
    value{0}, left{nullptr}, right{nullptr}{}

BST::Node::Node(const Node& node):
    Node(node.value, node.left, node.right){}

std::ostream& operator<<(std::ostream& os, const BST::Node& node){
    os << "Value:" << node.value << '\t'
         << "Left:" << node.left << '\t'
         << "Right:" << node.right << '\n';
    return os;
}

bool operator>(BST::Node& node, int v){
    return node.value > v;
}

bool operator>(int v, BST::Node& node){
    return v > node.value;
}

bool operator>=(BST::Node& node, int v){
    return node.value >= v;
}

bool operator>=(int v, BST::Node& node){
    return v >= node.value;
}

bool operator<(BST::Node& node, int v){
    return !(node >= v);
}

bool operator<(int v, BST::Node& node){
    return !(v >= node);
}

bool operator<=(BST::Node& node, int v){
    return !(node > v);
}

bool operator<=(int v, BST::Node& node){
    return !(v > node);
}

bool operator==(BST::Node& node, int v){
    return node.value == v;
}

bool operator==(int v, BST::Node& node){
    return  v == node.value;
}