/*
Student Name : Rey Baltar
Student ID : hrb217
Compiler used : Eclipse using MinGW
Program description:
	This program allows the user to interact with a command line interface so that the user
	can add and make modifications to containers in a list
*/
#ifndef BST_H_
#define BST_H_
#include <vector>
#include <iostream>
using std::string;
using std::vector;
using std::ostream;
using std::endl;
using std::cout;

class Node {
//The items of a tree
public:
	string data;
	int count;
	Node* right;
	Node* left;
	Node(): data(0), count(1), right(nullptr), left(nullptr){}
	Node(string data): data(data), count(1), right(nullptr), left(nullptr){}
	Node(string data, int count): data(data), count(count), right(nullptr), left(nullptr){}

};


class BST {
//Binary Search Tree of items
private:
	Node* root;
	string name;

	//built in methods
	int Search(Node*node, string val);
	bool Insert(Node*&node, Node*temp);
	bool Delete(Node*&node, string val); //debug
	void InOrder(Node*node, ostream& os);
	void PreOrder(Node*node, ostream& os);
	void PostOrder(Node*node, ostream& os);

public:
	//call to methods
	BST(): root(nullptr), name(""){};
	BST(string name):root(nullptr), name(name){}
	int search(string val){return Search(root, val);}

	bool insert(string val, int count){
		Node* item = new Node(val,count);
		return Insert(root, item);
	}

	bool remove(string val){return Delete(root, val);}
	void in_order(ostream & os){
		os << "In order:" << endl;
		InOrder(root, os);}
	void pre_order(ostream & os){
		os << "Pre order:" << endl;
		PreOrder(root, os);}
	void post_order(ostream & os){
		os << "Post order:" << endl;
		PostOrder(root, os);}

	//additional methods
	string get_root();
	string get_name();
};

///*

//*/
#endif /* BST_H_ */
