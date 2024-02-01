#ifndef BST_H
#define BST_H
#include <iostream>
#include <functional>
#include <queue>
#include <string>
#include <vector>

class BST
{
public:
    class Node;
    BST(std::initializer_list<int> list);
    BST(BST &b);
    BST(BST &&b);
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& os, const BST& bst);
    BST operator=(BST& b);
    BST operator=(BST&& b);
    friend BST& operator++(BST& b);
    friend BST operator++(BST& b, int);

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
