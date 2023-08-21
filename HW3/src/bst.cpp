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




// BST part
BST::Node*& BST::get_root(){
    return this->root;
}

void BST::bfs(std::function<void(Node*& node)> func){
    if(!root)return;
    std::queue<BST::Node*> que;
    que.push(root);
    while(!que.empty()){
        int n = que.size();
        for(int i = 0; i < n; ++i){
            auto t = que.front();
            if(t->left)que.push(t->left);
            if(t->right)que.push(t->right);
            func(t);
            que.pop();
        }
    }
}

size_t BST::length(){
    if(!root)return 0;
    size_t sum = 0;
    std::queue<BST::Node*> que;
    que.push(root);
    while(!que.empty()){
        int n = que.size();
        for(int i = 0; i < n; ++i){
            auto t = que.front();
            if(t->left)que.push(t->left);
            if(t->right)que.push(t->right);
            ++sum;
            que.pop();
        }
    }
    return sum;
}


bool BST::add_node(int value){
    if(root == nullptr){
        root = new BST::Node(value, nullptr, nullptr);
        return true;
    }
    Node* cur = root, *pre = nullptr;
    while(cur != nullptr){
        if(cur->value == value){   // find same node, 
            return false;       // add fail, return false
        }
        pre = cur;
        if(cur->value > value){
            cur = cur->left;
        }else{
            cur = cur->right;
        }
    }
    Node* node = new BST::Node(value, nullptr, nullptr);
    if(pre->value > value){
        pre->left = node;
    }else{
        pre->right = node;
    }
    return true;
}