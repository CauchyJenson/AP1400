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

BST::BST(std::initializer_list<int> list):root(nullptr){
    for(auto &i: list){
        add_node(i);
    }
}

 bool BST::add_node(int value){
    auto r = this->get_root();
    auto pre = r;
    if(!r){
        this->root = new Node(value, nullptr, nullptr);
        return true;
    }
    while(r){
        pre = r;
        if(r->value > value){
            r = r->left;
        }else if(r->value < value){
            r = r->right;
        }else return false;
    }
    if(pre->value > value){
        pre->left = new Node(value, nullptr, nullptr);
        return true;
    }else{
        pre->right = new Node(value, nullptr, nullptr);
        return true;
    }
    return false;

 }

 BST::Node*& BST::get_root(){
    return this->root;
}

void BST::bfs(std::function<void(Node*& node)> func){
    if(!this->get_root())return;
    std::queue<Node*> que;
    auto r = this->get_root();
    que.push(r);
    while(!que.empty()){
        auto cur = que.front();
        que.pop();
        func(cur);
        if(cur->left)que.push(cur->left);
        if(cur->right)que.push(cur->right);
    }
    return;
}

size_t BST::length(){
    size_t len = 0;
    this->bfs(
        [&len](BST::Node* &node){
            ++len;
    });
    return len;
}

std::ostream& operator<<(std::ostream& os, const BST& bst){
    os << std::string(80, '*') << std::endl;
    auto r = bst.root;
    std::queue<BST::Node*> que;
    if(r)que.push(r);
    while(!que.empty()){
        auto cur = que.front();
        que.pop();
        os << cur;
        if(cur->left)que.push(cur->left);
        if(cur->right)que.push(cur->right);
    }
    os << std::string(80, '*') << std::endl;
    return os;
}