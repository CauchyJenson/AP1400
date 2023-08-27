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

// default constructor
BST::BST(){this->root = nullptr;}

// copy constructor
static void copy(BST::Node* a, BST::Node* &b){
    if(a){// a -> b
        b = new BST::Node(a->value, nullptr, nullptr);
        copy(a->left, b->left);
        copy(a->right, b->right);
    }
    return;
}
BST::BST(const BST& bst){
    copy(bst.root, this->root);
}

// move constructor
BST::BST(BST && bst){
    if(bst.get_root() != nullptr){
        this->root = bst.get_root();
        bst.get_root() = nullptr;
    }
}

// destructor
 BST::~BST()
 {
 	std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes)
 		delete node;
 }

 // List initialization
 BST::BST(std::initializer_list<int> list){
    this->root = nullptr;
    if(list.size() != 0){
        for(auto i: list){
            this->add_node(i);
        }
    }
 }

// overload ==
BST& BST::operator=(const BST& bst){
    auto newBST = new BST(bst);
    this->~BST();
    root = newBST->get_root();
    return *this;
}
// member function
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
            que.pop();
            if(t->left)que.push(t->left);
            if(t->right)que.push(t->right);
            func(t);
            
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
    // Node* node = new BST::Node(value, nullptr, nullptr);
    if(pre->value > value){
        pre->left = new BST::Node(value, nullptr, nullptr);
    }else{
        pre->right = new BST::Node(value, nullptr, nullptr);
    }
    return true;
}

BST::Node** BST::find_node(int value){
    BST::Node* node = root;
    while(node){
        if(node->value == value){
            return new Node*(node);
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
            return new Node*(pre);
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

static void in_order(BST::Node* root, std::vector<BST::Node*>& vec){
    if(root){
        in_order(root->right, vec);
        vec.push_back(root);
        in_order(root->left, vec);
    }
}

BST::Node** BST::find_successor(int value){
    BST::Node* node = root;
    if(!root)return nullptr;
    std::vector<BST::Node*> vec;
    in_order(node, vec);
    int i = 0;
    for(; i < vec.size(); ++i){
        if(vec[i]->value == value) break;
    }
    return i+1 <vec.size()? find_node(vec[i+1]->value): nullptr;
}

int MostLeftOnRight(BST::Node* n) {
    BST::Node* p = n;
    while (p->left != nullptr) p = p->left;
    return p->value;
}

bool BST::delete_node(int value) {
    auto node = find_node(value);
    auto parent = find_parrent(value);

    // 404 not found
    if (node == nullptr) {
        return false;
    }

    if ((*node)->left == nullptr && (*node)->right == nullptr) {
        if (get_root() == *node)
            root = nullptr;
        else {
            if (value > (*parent)->value)
                (*parent)->right = nullptr;
            else
                (*parent)->left = nullptr;
        }

    } else if ((*node)->left != nullptr && (*node)->right != nullptr) {
        auto next = find_successor(value);
        auto new_one = new Node{(*next)->value, (*node)->left, (*node)->right};
        delete_node((*next)->value);
        delete next;
        if (get_root() == *node) {
            new_one->left = root->left;
            new_one->right = root->right;
            root = new_one;
        } else {
            if ((*parent)->left == *node)
                (*parent)->left = new_one;
            else
                (*parent)->right = new_one;
        }
    } else {
        Node* new_one = nullptr;
        if ((*node)->left)
            new_one = (*node)->left;
        else
            new_one = (*node)->right;

        if (root == *node) {
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

std::ostream& operator<<(std::ostream& os, const BST& bst){
    os << "********************************************************************************" << std::endl;
    std::queue<BST::Node*> que;
    que.push(bst.root);
    while(!que.empty()){
        auto tNode = que.front();
        que.pop();
        os << *tNode << std::endl;
        if(tNode->left){
            que.push(tNode->left);
        }
        if(tNode->right){
            que.push(tNode->right);
        }
    }
    os << "********************************************************************************" << std::endl;
    return os;
}

BST& BST::operator++(){
    this->bfs([](BST::Node* &node){++node->value;});//lamda function
    return *this;
}

BST BST::operator++(int){
    BST tmp = BST(*this);
    ++(*this);
    return tmp;
}