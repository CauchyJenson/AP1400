#ifndef BST_H
#define BST_H
#include<iostream>
#include<functional>
#include<iomanip>

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