/*
Student Name : Rey Baltar
Student ID : hrb217
Compiler used : Eclipse using MinGW
Program description:
	This program allows the user to interact with a command line interface so that the user
	can add and make modifications to containers in a list
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "BST.h"
using namespace std;

string breakString(string word, string cmd){
//"breaks" the second string by the length of the first string and returns new broken string

	//initialize variables
	string hanger;
	int value1 = word.length()+1; //incremented by 1 to include the space in the second word
	int value2 = cmd.length();

	//begins adding characters after the space after the first word.
	for(int i = value1; i < value2; i++){
		hanger += cmd[i];
	}

	return hanger;
}


string buildString(string word, string cmd){
//simply adds the second string to the first string and returns the new string

	// adds a space between words and increments
	word += " ";
	word += cmd;

	return word;
}

void parse(string& New, string Old, string& LS, string FS){
	//rebuilds the string to a stored variable and breaks the full state_ment so that 'new'
	//gets the remaining text starting with the desired word
	LS = buildString(LS, Old);
	New = breakString(LS, FS);
}

bool traverse_boxes(string name, vector<BST> lists){
	//traverses the list of containers to see if the desired
	//one exist
	vector<BST>::iterator it;
	for(it = lists.begin(); it != lists.end(); ++it){
		if(name ==	(*it).get_name()){

			return true;
		}
	}

	return false;
}



//		MAIN		//
int main() {

	//initialize variables
	vector<BST> boxes;
	BST* box; //pointer for specified container
	bool container; //signal a valid container
	string command, object1, word1, word2, word3, leftSide, full_statement; //user input variables
	int stock;
	ifstream itext;
	bool run = true;

	//introduce program
	cout <<"This program allows the user to interact with a command line " << endl;
	cout <<"interface so that the user can create and modify containers" <<endl;
	cout<< "without typing any code." << endl;
	cout <<"NOTE: for the 'load' command, include the '.txt' after the file name" << endl<< endl;

	//enters parse loop
	while(run){

		/*
		 * checks whether or not a file is open so that the program knows
		 * whether to prompt the user for a command line or automatically
		 * parse the next line of the file
		 */
		if(!itext.is_open()){
			cout << "Command Line: ";
			getline(cin, command);

		}else{
			getline(itext, command);
		}

		//stores the full command statement
		full_statement = command;
		stringstream ss(command);

		// redefines command as the first word in full statement
		getline(ss, command, ' ');

		// stores words that are "broken" from strings
		leftSide = command;

		// assigns object1 to a modified full_statement with 'command' removed
		object1 = breakString(command, full_statement);

		//and define 'object1' as the second word of the full statement and
		getline(ss, object1, ' ');

		//for the following operations the remaining statement from the user will be parsed
		parse(word1, object1, leftSide, full_statement);
		getline(ss, word1, ' ');

		parse(word2, word1, leftSide, full_statement);
		getline(ss, word2, ' ');

		parse(word3, word2, leftSide, full_statement);
		getline(ss, word3, ' ');


		//*** NOW WE ENTER THE IF STATEMENTS *** //

		if(command == "exit"){
			//exits the program
			break;


		}else if(command == "create"){
			//creates a container and adds it into the vector
			container = traverse_boxes(object1, boxes);
			if(!container){
				BST select(object1);
				boxes.push_back(select);
			}else{
				//inform if it already exist
				cout << "container already exists" << endl;
			}

		}else if(command == "destroy"){
			//destroys continer
			container = traverse_boxes(object1, boxes);
			if(!container){
				cout << "destroy fail - non-existent"<< endl;
			}else{
				//searches the vector of containers in order to destroy it
				vector<BST>::iterator it;
				for(it = boxes.begin(); it != boxes.end(); ++it){
					if((*it).get_name() == object1){
						boxes.erase(it);
						break;
					}
				}
			}
		}else if(command == "display"){
			//displays whether pre order, post order, or in order
			//verifies if the contianer is valid
			container = traverse_boxes(object1, boxes);
			for(BST& b: boxes){
				if(b.get_name() == object1){
					box = &b;
					break;
				}
			}
			//notifies failure or displays the tree of the container
			if(!container){
				cout << "container does not exist" << endl;

			}else if(word1 == "pre"){
				box->pre_order(cout);
			}
			else if(word1 == "post"){
				box->post_order(cout);
			}else if(word1 == "in"){
				box->in_order(cout);
			}else{
				cout << "missing display type" << endl;
			}

		}else if(command== "load"){
			//opens a .txt file and obtains its text
			itext.open( object1 );


		}else if(command == "remove"){
			//removes items from a container(s)

			bool check; //signal whether an item has been removed

			//check if the user specifies a container
			if (word1 == "in"){
				container = traverse_boxes(word2, boxes);

				//check if container is valid
				if(container){
					for(BST& b: boxes){
						//finds the container and assings the main pointer
						if(b.get_name()== word2){
							box = &b;
							break;
						}
					}
					check = box->remove(object1);

					//notify whether an item has been removed
					if(check){
						cout<< object1 + " removed from " + box->get_name() << endl;
					}else{
						cout << "remove fail - " + object1 + " not found" <<endl;
					}

				}else{
					cout << "container does not exist" << endl;
				}
			}else{
				bool success = false; //signal if an item is removed from at least one container

				//removes an item from each container in the vector
				vector<BST>::iterator it;
				for(it = boxes.begin(); it != boxes.end(); ++it){
					check = (*it).remove(object1);
					if(check){
						cout<< object1 + " removed from " + (*it).get_name() << endl;
						success = true;
					}
				}

				//notify the user whether any items were removed
				if(success){
					cout << object1 + " successfully removed" << endl;
				}else{
					cout << object1 + " was not found anywhere" << endl;
				}
			}

		}else if(command == "find"){
			//finds the specified item
			//check if a container is specified
			if(word1 == "in"){
				//verifies container
				container = traverse_boxes(word2, boxes);
				if(container){
					for(BST& b: boxes){
						if(b.get_name() == word2){
							box = &b;
							break;
						}
					}
					//searches the item
					int count = box->search(object1);

					//inform if the time is found
					if(count != 0){
						cout << object1 + ": " << count << endl;
					}else{
						cout << object1 + " not in container" << endl;
					}
				}else{
					cout << "container does not exist" << endl;
				}
			}else{
				//initialize counter
				int count = 0;
				//traverses in the vector to add each stock of the item specified
				vector<BST>::iterator it;
				for(it = boxes.begin(); it != boxes.end(); ++it){
					count += (*it).search(object1);
				}

				//notify total amount of the item found
				if(count == 0){
					cout<<object1 + " not found in any containers"<<endl;
				}else{
					cout << object1 + ": " << count << endl;
				}
			}

		}else if(command == "insert"){
			//inserts an item into a BST
			bool check = true;

			//attempts to transfrom the ammount into an integer
			try{

				stock = stoi(word1);
			}catch(...){
				cout << "invalid amount. make sure it is a number" << endl;
				check = false;
			}

			//check if the container is valid and notifies if insertion fails or not
			container = traverse_boxes(word3, boxes);
			if(!container){
				cout << "insert fail - non existent container" << endl;

			}else if(check){
				//obtains specified container
				for(BST& b: boxes){
					if(b.get_name() == word3){
						box = &b;
						break;
					}
				}
				//signal the insert method and inform the result
				check = box->insert(object1, stock);
				if(!check){cout << "insert fail - complex error" << endl;}
				else{cout << object1 + " inserted into container " + word3 << endl;}
			}
		}else{
			//inform user that the command is not within the program (or awkward space in command line)
			cout << "No command of that nature found (or awkward spaces)" << endl;
		}

		// *** EXIT IF STATEMENTS *** //

		//checks if the test file is being processed and if it has reached its end
		if(itext.is_open() and itext.eof()){
			//closes text file and returns to the user interface command line
			itext.close();
		}

		// ** END OF WHILE lOOP ** //
	}
	cout << "TERMINATED" << endl;

	return 0;
}
