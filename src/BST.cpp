/*
Student Name : Rey Baltar
Student ID : hrb217
Compiler used : Eclipse using MinGW
Program description:
	This program allows the user to interact with a command line interface so that the user
	can add and make modifications to containers in a list
*/

#include "BST.h"


bool BST::Delete(Node* &node, string val){
	//returns 0 if the node parameter is non-existent
	if(node == nullptr)return 0;

	//if the node exists then begin deletion
	if(node->data == val){
		//initialize variables
		int degree = 0;
		Node* next;

		//checks if left or right node exist
		if(node->left != nullptr){
			degree++;
			next = node->left; //applies if the degree is 1
		}
		if(node->right != nullptr){
			degree++;
			next = node->right;// applies if the degree is 1
		}

		//deletes the node
		if(degree==0){
			delete node;
			node = nullptr;
			return true;

		//parents points to the nodes child and then delete node
		}else if(degree == 1){
			Node *s = node;
			node = next;
			delete s;
			return true;

		//traverse left then all the way right reassingns pointers
		}else if(degree == 2){

			//initialize variables
			Node* S = node->left;
			Node* h = node;

			//check if node's left has a right child
			if(!S->right){
				//reassigns pointers if no right pointers
				node = h->left;
				h->left = node->left;
				node->right = h->right;
				node->left = h;
				return Delete(node->left, val);
			}else{
				//initialize pointer to traverse the right nodes
				Node* s = S;
				while(s->right->right != nullptr){
					s = s->right;
				}

				//reassigns variable based on the end of right nodes
				node = s->right;
				node->right = h->right;
				h->left = node->left;
				node->left = S;
				s->right = h;
				h->right = nullptr;
				return Delete(node->left, val);
			}
		}
	}

	//traverse to the right of the node
	else if(val > node->data)return Delete(node->right, val);

	//traverse to the left of the node
	else if(val < node->data)return Delete(node->left, val);

	//return 0 if all else fails
	return 0;
}

//searches for a node
int BST::Search(Node*node, string val){
	//returns 0 if the node parameter is non-existent
	if(node == nullptr)return 0;

	//if the node exists then return the stock amount
	if(node->data == val)return node->count;

	//traverse to the right of the node
	else if(val > node->data)return Search(node->right, val);

	//traverse to the left of the node
	else if(val < node->data)return Search(node->left, val);

	//return 0 if all else fails
	return 0;
}

//inserts a node into the binary search tree
bool BST::Insert(Node*&node, Node*temp){

	//places node in an empty location
	if(node == nullptr){
		node = temp;
		return true;
	}

	//if the node already exists, then increase the amount
	if(node->data == temp->data){
		node->count += temp->count;
		return true;
	}

	//traverse to the right of the node
	else if(temp->data > node->data){
		//if(node == nullptr->right)node->right = temp;
		//else{Insert(node->right, temp);}
		return Insert(node->right, temp);
	}

	//traverse to the left
	else if(temp->data < node->data){
		//if(node == nullptr->left)node->left = temp;
		//else{Insert(node->left, temp);}
		return Insert(node->left, temp);
	}
	//signal failure
	return false;
}

//displays the BST by in-order traversal
void BST::InOrder(Node*node, ostream& os){
	if(node == nullptr)return;

	//left -> node -> right
	InOrder(node->left,os);
	os << node->data << ": " << node->count << endl;
	InOrder(node->right, os);

}

//displays the BST by pre-order traversal
void BST::PreOrder(Node* node, ostream& os){
	if(node == nullptr)return;

	//node -> left -> right
	os << node->data << ": " << node->count << endl;
	PreOrder(node->left, os);
	PreOrder(node->right, os);


}

//displays the BST by post-order traversal
void BST::PostOrder(Node* node, ostream & os){
	if(node == nullptr){
		return;
	}

	//left -> right -> node
	PostOrder(node->left, os);
	PostOrder(node->right, os);
	os << node->data << ": " << node->count << endl;

}

//returns the private varibles
string BST::get_root(){
	return root->data;
}
string BST::get_name(){
	return name;
}
