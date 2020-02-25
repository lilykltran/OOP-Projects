//Lily Tran 989558404 CS202 HW3. This file contains implementation of classes RBT_Node and Tree
#include "HW3.h"

//default constructor
RBT_Node::RBT_Node(LLL a_meeting): meetings(a_meeting), title(NULL), left(NULL), right(NULL), parent(NULL), internal(true){}


//copy constructor
RBT_Node::RBT_Node(const RBT_Node & to_copy): meetings(to_copy.meetings), left(NULL), right(NULL), parent(NULL), internal(to_copy.internal)
{
	title = new char[strlen(to_copy.title) +1];
	strcpy(title, to_copy.title);
}


//Adds meeting constructor
RBT_Node::RBT_Node(Meeting to_add) : left(NULL), right(NULL), parent(NULL)
{
	meetings.add_meeting(&to_add); //call the add meeting function from LLL 
	internal = true;
	title = new char[strlen(to_add.get_keyword()) +1];
	strcpy(title, to_add.get_keyword());
}


//returns title
char *RBT_Node::get_title()
{
	return title;
}


//destructor
RBT_Node::~RBT_Node()
{
	left = parent = right = NULL;
}


//returns right pointer
RBT_Node *& RBT_Node::get_right()
{
	return right;
}


//returns left pointer
RBT_Node *& RBT_Node::get_left()
{
	return left;
}


//returns parents pointer
RBT_Node *& RBT_Node::get_parent()
{
	return parent;
}


//returns internal
bool RBT_Node ::get_internal()
{
	return internal;
}


//sets internal to value passed in
void RBT_Node::set_internal(bool value)
{
	internal = value;
}


//add a LLL to the node
int RBT_Node::add_meeting(Meeting a_meeting)
{
	return meetings.add_meeting(&a_meeting); //call the add meeting function from LLL 
}


//constructor
Tree::Tree() { root = NULL;}


//destructor
Tree::~Tree()
{
	remove_all(); //call remove all function
}


//Wrapper for remove all
int Tree::remove_all()
{
	if (!root)
		return 0;

	return remove_all(root);
}


//removes and deallocates all nodes in tree
int Tree::remove_all(RBT_Node* & root)
{
	if (!root)
		return 0;

	remove_all(root->get_left()); //Removes the left tree
	remove_all(root->get_right()); //Removes the right tree

	delete root;
	return 1;
}


//wrapper for copying tree
int Tree::copy(const Tree & source)
{
	return copy(root, source.root);
}


//Recursive function to copy a tree
int Tree::copy(RBT_Node* & dest, RBT_Node* source)
{
	if (!source) //If the source root is NULL, make the dest root NULL
	{
		dest = NULL;
		return 0;
	}

	dest = new RBT_Node(*source); //Otherwise create a new node and assign it the same data as the source node
	if (copy(dest->get_left(), source->get_left())) //Copy the left tree
		dest->get_left()->get_parent() = dest;
	if (copy(dest->get_right(), source->get_right())) //Copy the right tree
		dest->get_right()->get_parent() = dest;

	return 1;
}


//returns 0 if match, some other if non match
int Tree::compare(char *title, char *keyword)
{
	return strcmp(title, keyword);
}


//wrapper for insert function
int Tree::insert(Meeting a_meeting)
{
	return insert(this -> root, a_meeting);
}


//inserts meetings into the tree recursively
int Tree::insert(RBT_Node *& root, Meeting a_meeting)
{
	if (!root)
	{
		root = new RBT_Node(a_meeting);
		return 1;
	}

	else
	{
		if (compare(root -> get_title(), a_meeting.get_keyword()) > 0) //if the matching keyword is to the right subtree,
		{
			insert(root -> get_right(), a_meeting); //traverse right till we find the match
			root->get_right()->get_parent() = root;
			balance(root->get_right(), a_meeting); //call balance function
		}

		else if (compare(root -> get_title(), a_meeting.get_keyword()) < 0) //if matching keyword is in the left subtree
		{
			insert(root -> get_left(), a_meeting);  //traverse left till we find the match
			root->get_left()->get_parent() = root;
			balance(root->get_left(), a_meeting); //call balance function
		}

		else //there is a match
		{ 
			root -> add_meeting(a_meeting); //add the meeting right there
			return 1;
		}
	}
	return 1;
}


//Recursively displays all nodes in tree
void Tree::display(RBT_Node *root)
{
	if (!root)
		return;

	root -> display(); //call the LLL's display function.
	display(root -> get_left());
	display(root -> get_right());
}


//wrapper for display
void Tree::display()
{
	if (!root)
		return;

	display(this -> root);
}


//finds matching keyword wrapper
RBT_Node* Tree::find(char *keyword)
{
	if (!root) return NULL;
	return find(this -> root, keyword);
}


//recurisvely searches for the mat hing keyword
RBT_Node* Tree::find(RBT_Node *root, char *keyword)
{
	if (!root)
		return NULL;

	if (compare(root -> get_title(), keyword) == 0) //call the compare function that compares title and keyword
		return root;

	else if (compare(root -> get_title(), keyword) < 0)
		return find(root -> get_left(), keyword);
	
	else
		return find(root -> get_right(), keyword);
}


//Balances the tree
int Tree::balance(RBT_Node* added, Meeting a_meeting)
{
	RBT_Node* current = root;

	while (current && current != added) //Finds the node added
	{
		int diff = compare(added->get_title(), a_meeting.get_keyword()); //set the compare value to diff

		if (diff > 0) //if it's in right subtree
			current = current->get_right(); //traverse right
		else if (diff < 0)
			current = current->get_left(); //else travers left
	}

	if (!current)
		return 0;

	RBT_Node* parent, *grandparent; //The parent and grandparent of the node added

	while (current && current != root && current->get_parent()->get_internal()) //While there is two red nodes in a row
	{
		parent = current->get_parent();
		grandparent = parent->get_parent();
		RBT_Node* uncle;
		if (parent == grandparent->get_left()) //If parent is the left child of its parent
		{
			uncle = grandparent->get_right();
			if (uncle && uncle->get_internal()) //If the uncle is red, push the color up to the grandparent
			{
				parent->set_internal(false);
				uncle->set_internal(false);
				grandparent->set_internal(true);
				current = grandparent;
			}
			else //If the uncle isn't red
			{
				if (current == parent->get_right()) //If the current node is its parent's right child
				{
					current = parent;
					rotate_left(current); //Rotate the parent left
				}
				current->get_parent()->set_internal(false);
				current->get_parent()->get_parent()->set_internal(true);
				rotate_right(current->get_parent()->get_parent()); //Rotate the grandparent right
			}
		}
		else //If the parent is the right child of its parent
		{
			uncle = grandparent->get_left();
			if (uncle && uncle->get_internal()) //If the uncle is red, push the color up to the grandparent
			{
				parent->set_internal(false); 
				uncle->set_internal(false);
				grandparent->set_internal(true);
				current = grandparent;
			}
			else
			{
				if (current == parent->get_left()) //If current is its parent's left child
				{
					current = parent;
					rotate_right(current); //Rotate the parent right
				}
				current->get_parent()->set_internal(false);
				current->get_parent()->get_parent()->set_internal(true);
				rotate_left(current->get_parent()->get_parent()); //Rotate the grandparent left
			}
		}
	}

	Tree::root->set_internal(false);

	return 1;
}


//Rotates a group of nodes left
void Tree::rotate_left(RBT_Node* root)
{
	RBT_Node* temp = root->get_right(); //Stores the right child in a temp
	root->get_right() = temp->get_left(); //Sets the right child to its left child
	if (temp->get_left()) //If there is a left child
		temp->get_left()->get_parent() = root; //Reconnect up the parent
	temp->get_parent() = root->get_parent(); //Reconnects parent
	if (!root->get_parent()) //If we are at the top of the tree
		Tree::root = temp; //Change the main root
	else
	{
		if (root == root->get_parent()->get_left()) //If root is the left child
			root->get_parent()->get_left() = temp; //The left child becomes root's old right child
		else
			root->get_parent()->get_right() = temp; //Otherwise the right child becomes the old right child
	}
	temp->get_left() = root; //Reconnects root to the tree
	root->get_parent() = temp; //Reconnects parent
}


//Rotates a group of nodes right
void Tree::rotate_right(RBT_Node* root)
{
	RBT_Node* temp = root->get_left(); //Stores the left child in a temp
	root->get_left() = temp->get_right(); //Sets the left child to its right child
	if (temp->get_right()) //If there is a right child
		temp->get_left()->get_parent() = root; //Reconnect up the parent
	temp->get_parent() = root->get_parent(); //Reconnects parent
	if (!root->get_parent()) //If we are at the top of the tree
		Tree::root = temp; //Change the main root
	else
	{
		if (root == root->get_parent()->get_left()) //If root is a left child
			root->get_parent()->get_left() = temp; //The left child becomes the root's old left child
		else
			root->get_parent()->get_right() = temp; //Otherwise the right child beomces the old left child
	}
	temp->get_right() = root; //Reconnects root the the tree
	root->get_parent() = temp; //Reconnects parent
}

/////////////////OPERATOR OVERLOADING. UNFINISHED...///////////////
/*
Tree & Tree::operator=(const Meeting & a_meeting)
{

	add_meeting(a_meeting); //Set the new song

	return *this;
}

Tree & Tree::operator=(const Tree & a_list)
{
	if (this == &a_list)
		return *this;

	copy(head, a_list.head); //Copy Tree

	return *this;
}

Tree & Tree::operator+=(const Meeting & a_meeting)
{
	add_meeting(a_meeting);

	return *this;
}


Tree Tree::operator+(const Meeting & a_meeting, const Tree & a_list)
{
	Tree temp(a_list);

	temp.add_song(a_meeting);

	return temp;
}

Tree Tree::operator+(const Tree & a_list, const Meeting & a_meeting)
{
	Tree temp(a_list);

	temp.add_meeting(a_meeting);

	return temp;
}
*/
