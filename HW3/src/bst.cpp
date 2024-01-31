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

BST::BST(BST &b): root(nullptr){
    std::vector<int> v;
    b.bfs(
        [&v](BST::Node* &node){
            v.emplace_back(node->value);
        }
    );
    for(auto &i: v){
        add_node(i);
    }
}

BST BST::operator=(BST& b){
    if(this->root == b.get_root())return *this;
    this->root = nullptr;
    std::vector<int> v;
    b.bfs(
        [&v](BST::Node* &node){
            v.emplace_back(node->value);
        }
    );
    for(auto &i: v){
        add_node(i);
    }
    return *this;
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
    os << std::endl;
    os << std::string(80, '*') << std::endl;
    return os;
}

BST::Node** BST::find_node(int value){
    auto r = this->get_root();
    while(r){
        if(r->value > value){
            r = r->left;
        }else if(r->value < value){
            r = r->right;
        }else break;
    }
    if(!r)return nullptr;
    //return &r;
    return new Node*(r);
}

BST::Node** BST::find_parrent(int value){
    auto cur = this->get_root();
    decltype(cur) pre = nullptr;
    while(cur){
        if(cur->value > value){
            pre = cur;
            cur = cur->left;
        }else if(cur->value < value){
            pre = cur;
            cur = cur->right;
        }else break;
    }
    if(!pre)return nullptr;
    return new Node*(pre);
}

BST::Node** BST::find_successor(int value){
    auto cur = this->find_node(value);
    if(!cur)return nullptr;
    if((*cur)->left){
        auto tmp = (*cur)->left;
        while(tmp->right){
            tmp = tmp->right;
        }
        return new Node*(tmp);
    }
    if((*cur)->right){
        auto tmp = (*cur)->right;
        while(tmp->left){
            tmp = tmp->left;
        }
        return new Node*(tmp);
    }
    return nullptr;
}
//copy from Franz.
bool BST::delete_node(int value) {
    auto node = find_node(value);
    auto parent = find_parrent(value);

    //not found
    if (node == nullptr) {
        return false;
    }
    // is leaf
    if ((*node)->left == nullptr && (*node)->right == nullptr) {
        if (get_root() == *node) // is root
            root = nullptr;
        else {
            if (value > (*parent)->value)
                (*parent)->right = nullptr;
            else
                (*parent)->left = nullptr;
        }
    // has two children
    } else if ((*node)->left != nullptr && (*node)->right != nullptr) {
        auto next = find_successor(value);
        auto new_one = new Node{(*next)->value, (*node)->left, (*node)->right};//copy successor, to make it current node.
        delete_node((*next)->value);// next is a leaf, so just delete it.
        delete next;
        if (get_root() == *node) {// is root
            new_one->left = root->left;
            new_one->right = root->right;
            root = new_one;
        } else {// not root
            if ((*parent)->left == *node)
                (*parent)->left = new_one;
            else
                (*parent)->right = new_one;
        }
    } else {// has one child
        Node* new_one = nullptr;
        if ((*node)->left)
            new_one = (*node)->left;
        else
            new_one = (*node)->right;

        if (root == *node) {// is root
            new_one->left = root->left;
            new_one->right = root->right;
            root = new_one;
        } else {
            if ((*parent)->left == *node)
                (*parent)->left = new_one;
            else
                (*parent)->right = new_one;
        }
    }
    delete *node;
    delete node;
    delete parent;

    return true;
}