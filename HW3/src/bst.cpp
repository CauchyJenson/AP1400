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

BST::Node** BST::find_node(int value){
    BST::Node* node = root;
    while(node){
        if(node->value == value){
            return &node;
        }else if(node->value > value){
            node = node->left;
        }else if(node->value < value){
            node = node->right;
        }
    }
    return nullptr;
}

BST::Node** BST::find_parrent(int value){
    BST::Node* cur = root, *pre = nullptr;
    while(cur){
        if(cur->value == value){
            return &pre;
        }else if(cur->value > value){
            pre = cur;
            cur = cur->left;
        }else if(cur->value < value){
            pre = cur;
            cur = cur->right;
        }
    }
    return nullptr;
}

BST::Node** BST::find_successor(int value){
    BST::Node* node = root;
    while(node){
        if(node->value == value){
            break;
        }else if(node->value > value){
            node = node->left;
        }else if(node->value < value){
            node = node->right;
        }
    }
    if(node){
        if(node->left){
            return &(node->left);
        }else if(node->right){
            return &(node->right);
        }
    }
    return nullptr;
}

bool BST::delete_node(int value){
    BST::Node* cur = root, *pre = nullptr;
    while(cur){
        if(cur->value == value)break;
        if(cur->value > value){
            pre = cur;
            cur = cur->left;
        }else if(cur->value < value){
            pre = cur;
            cur = cur->right;
        }
    }
    if(cur == nullptr)return false;
    if(cur->left == nullptr || cur->right == nullptr){
        auto child = cur->left != nullptr? cur->left: cur->right;
        if(cur != root){
            if(cur == pre->left){
                pre->left = child;
            }else if(cur == pre->right){
                pre->right = child;
            }
        }else{
            root = child;
        }
        delete cur;
    }else{
        auto tmp = root->right;
        while(tmp->left){
            tmp = tmp->left;
        }
        int tmpVal = tmp->value;
        BST::delete_node(tmpVal);
        cur->value = tmpVal;
        return true;
    }
    return false;
}