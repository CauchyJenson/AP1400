#include "bst.h"


// Class Node part
BST::Node::Node(int value, Node* left, Node* right):
        value(value), left(left), right(right){}

BST::Node::Node():value(0), left(nullptr), right(nullptr){}

BST::Node::Node(const Node& node):value(node.value),
                            left(node.left), right(node.right){}
                    
std::ostream& operator<<(std::ostream& os, const BST::Node& node){
    os << std::hex << std::setw(16) << &node << "=> value:" 
    << std::setw(10) << node.value << "left:"
    << std::hex << std::setw(16) << node.left << "right:"
    << std::hex << std::setw(16) << node.right <<std::endl;
    return os;
}
// ==
bool operator==(const BST::Node& node, int num){return node.value == num;}
bool operator==(int num, const BST::Node& node){return num == node.value;}
// >
bool operator<(const BST::Node& node, int num){return node.value < num;}
bool operator<(int num, const BST::Node& node){return num < node.value;}
// >
bool operator>(const BST::Node& node, int num){return node.value > num;}
bool operator>(int num, const BST::Node& node){return num > node.value;}
// <=
bool operator<=(const BST::Node& node, int num){return node.value <= num;}
bool operator<=(int num, const BST::Node& node){return num <= node.value;}
// >=
bool operator>=(const BST::Node& node, int num){return node.value >= num;}
bool operator>=(int num, const BST::Node& node){return num >= node.value;}




//
