#ifndef BST_H
#define BST_H
#include <iostream>
#include <functional>

class BST
{
public:
    class Node;
    BST(std::initializer_list<int> list);
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

bool operator>(BST::Node& node, int v);

bool operator>(int v, BST::Node& node);

bool operator>=(BST::Node& node, int v);

bool operator>=(int v, BST::Node& node);

bool operator<(BST::Node& node, int v);

bool operator<(int v, BST::Node& node);

bool operator<=(BST::Node& node, int v);

bool operator<=(int v, BST::Node& node);

bool operator==(BST::Node& node, int v);

bool operator==(int v, BST::Node& node);

#endif //BST_H