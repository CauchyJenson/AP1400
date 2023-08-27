#ifndef BST_H
#define BST_H
#include<iostream>
#include<functional>
#include<iomanip>
#include<queue>

class BST
{
public:
    class Node;
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    // constructors
    BST();
    BST(const BST& bst);
    BST(BST && bst);
    BST(std::initializer_list<int> list);
    // overload =
    BST& operator=(const BST& bst);
    ~BST();

    friend std::ostream& operator<<(std::ostream& os, const BST& bst);
    BST& operator++(); // ++pre
    BST operator++(int); // post++
private:
    Node* root;
};



class BST::Node
{
public:
	Node(int value, Node* left, Node* right);
	Node();
	Node(const Node& node);

	int value;
	Node* left;
	Node* right;
};

std::ostream& operator<<(std::ostream& os, const BST::Node& node);
// == overload
bool operator==(const BST::Node& node, int num);
bool operator==(int num, const BST::Node& node);
// < overload
bool operator<(const BST::Node& node, int num);
bool operator<(int num, const BST::Node& node);
// > overload
bool operator>(const BST::Node& node, int num);
bool operator>(int num, const BST::Node& node);
// <= overload
bool operator<=(const BST::Node& node, int num);
bool operator<=(int num, const BST::Node& node);
// >= overload
bool operator>=(const BST::Node& node, int num);
bool operator>=(int num, const BST::Node& node);

#endif //BST_H