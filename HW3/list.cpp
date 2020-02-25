//Lily Tran 989558404 CS202 HW3. This file contains implementation of classes LLL_Node and List.
#include "HW3.h"

/////////////////////LLL_Node implementation///////////////////////////

LLL_Node::LLL_Node(Meeting * a_meeting): data(a_meeting), next(NULL) {}


//destructor
LLL_Node::~LLL_Node()
{
	if (data)
	{
		delete data;
	}

	data = NULL;
	next = NULL;
}


//Returns the next pointer
LLL_Node* & LLL_Node::get_next()
{
	return next;
}


//Sets the next pointer to argument passed in
int LLL_Node::set_next(LLL_Node *to_add)
{
	next = to_add;
	return 1;
}


//Sets the data
int LLL_Node::set_data(Meeting* a_meeting)
{
	if (!a_meeting)
		return 0;

	if (data)
		delete data;
	data = a_meeting;

	return 1;
}


//Appends the arguement LLL_Node to the end of the current LLL_Node
int LLL_Node::append(LLL_Node* a_LLL_Node)
{
	if (!a_LLL_Node)
		return 0;

	next = a_LLL_Node;

	return 1;
}


//Returns a pointer to the course stored in the LLL_Node
Meeting* LLL_Node::get_data()
{
	return data;
}


//Displays the data in the LLL_Node
int LLL_Node::display()
{
	if (!data)
		return 0;

	data->display();
	return 1;
}


///////////////////////////List implemntation///////////////////////////////


LLL::LLL(): head(NULL), tail(NULL), num_meetings(0) {}


//Copy constructor, calls copy function
LLL::LLL(const LLL & to_copy)
{
	copy(head, to_copy.head);
}


//Destructor
LLL::~LLL()
{
	LLL_Node* current = head;

	while (current)
	{
		current = current->get_next();
		delete head;
		head = current;
	}

	head = tail = NULL;
}


//Copies another list recursively
int LLL::copy(LLL_Node* & dest, LLL_Node* source)
{
	if (!source)
	{
		dest = NULL;
		return 0;
	}

	dest = new LLL_Node(source->get_data());
	copy(dest->get_next(), source->get_next());

	return 1;
}


//Displays all meetings in the list
int LLL::display()
{
	if (!head)
		return 0;

	LLL_Node* current = head;

	while (current)
	{
		Meeting* data = current->get_data();
		if (data)
			data->display();
		cout << endl;
		current = current->get_next();
	}

	return 1;
}


//adds a meeting to the LLL
int LLL::add_meeting(Meeting* a_meeting)
{
	if (!a_meeting)
		return 0;

	LLL_Node* temp = new LLL_Node(a_meeting); 
	
	if (!head) //Adds at head if list empty
	{
		head = tail = temp;
		tail -> set_next(NULL);
		return 1;
	}

	else //if list is not empty
	{
		tail -> set_next(temp);
		tail = tail->get_next();
		tail -> set_next(NULL);
		return 1;
	}
	return 0;
}


//writes out all meetings to meetings.txt file
void LLL::write()
{

	ofstream write; //create variable of ofstream called write
	write.open("meetings.txt");  //rewrite over the entire file. 

	if (!write) //makes sure it is connected to file jobs.txt
	{
		cout <<"unable to open file.";
		return;
	}
	else
	{
		LLL_Node *current = head;
		while (current)	
		{
			write << current -> get_data() -> get_name() <<"|" //write out each variable of the struct, using a '|' as the deliminator. 
				<< current -> get_data() -> get_time() <<"|"
				<< current -> get_data() -> get_date() <<"|"
				<< current -> get_data() -> get_location() <<"|"
				<< current -> get_data() -> get_keyword() << "|";

				current -> get_data() -> display_contacts(write);
			
			current = current -> get_next();
		}

		write.flush();
		}
		write.close(); //close file 
}


///////////////////////OPERATOR OVERLOADING. CRASHES...THESE ARE UNFINISHED/////////////////
/*

Meeting * LLL::find_meeting(const Meeting * to_find) const
{
	if (!head)
		return NULL;

	if (head -> get_data() -> get_name() == to_find) //If rear is the song to find
		return head;

	LLL_Node* current = head;

	while (current -> get_next()) //Traverse while current hasn't looped around
	{
		if (current -> get_data() -> get_name() == to_find)
			return current;
		else
			current = current->get_next();
	}

	return NULL;
}

bool LLL::compare_list(const LLL & comp) const
{

	if (!head) 
	{
		if (!comp.head)
			return true;
		else
			return false;
	}

	LLL_Node* current = head;
	LLL_Node* current2 = comp.head;

	if (!comp.find_meeting(*current) || !find_meeting(*current2)) //Compare the first two songs
		return false;

	while (current -> get_next() && current2 -> get_next()) //Traverse while the end of the list hasn't been reached
	{
		if (!comp.find_meeting(*current) || !find_meeting(*current2)) //Compare the current songs
			return false;
		current = current->get_next();
		current2 = current->get_next();
	}

	return true;
}


LLL & LLL::operator=(const Meeting & a_meeting)
{

	add_meeting(a_meeting); //Set the new song

	return *this;
}

LLL & LLL::operator=(const LLL & a_list)
{
	if (this == &a_list)
		return *this;

	copy(head, a_list.head); //Copy LLL

	return *this;
}

LLL & LLL::operator+=(const Meeting & a_meeting)
{
	add_meeting(a_meeting);

	return *this;
}


LLL LLL::operator+(const Meeting & a_meeting, const LLL & a_list)
{
	LLL temp(a_list);

	temp.add_song(a_meeting);

	return temp;
}

LLL LLL::operator+(const LLL & a_list, const Meeting & a_meeting)
{
	LLL temp(a_list);

	temp.add_meeting(a_meeting);

	return temp;
}


bool LLL::operator==(const Meeting & a_meeting, const LLL & a_list)
{
	if (a_list.find_meeting(a_meeting))
		return true;
	else
		return false;
}

bool LLL::operator==(const LLL & a_list, const Meeting & a_meeting)
{
	if (a_list.find_meeting(a_meeting))
		return true;
	else
		return false;
}

bool LLL::operator==(const LLL & l1, const LLL & l2)
{
	return l1.compare_list(l2);
}


bool LLL::operator!=(const Meeting & a_meeting, const LLL & a_list)
{
	if (!a_list.find_meeting(a_meeting))
		return true;
	else
		return false;
}

bool LLL::operator!=(const LLL & a_list, const Meeting & a_meeting)
{
	if (!a_list.find_meeting(a_meeting))
		return true;
	else
		return false;
}

bool LLL::operator!=(const LLL & l1, const LLL & l2)
{
	return !l1.compare_list(l2);
}

bool LLL::operator>(const LLL & l1, const LLL & l2)
{
	return l1.num_meetings > l2.num_meetings;
}

bool LLL::operator>=(const LLL & l1, const LLL & l2)
{
	return l1.num_meetings >= l2.num_meetings;
}

bool LLL::operator<(const LLL & l1, const LLL & l2)
{
	return l1.num_meetings < l2.num_meetings;
}

bool LLL::operator<=(const LLL & l1, const LLL & l2)
{
	return l1.num_meetings <= l2.num_meetings;
}

std::ostream & LLL::operator<<(std::ostream & out, const LLL & a_list)
{
	if (!a_list.head)
	{
		return out;
	}

	out << *a_list.head;

	LLL_Node* current = a_list.head->get_next();

	while (current != a_list.head)
	{
		out << ", " << *current;
		current = current->get_next();
	}

	return out;
}

Meeting & LLL::operator[](int index) const
{

	LLL_Node* current = head;

	for (int i = 0; (i < index) && (current = current->get_next()); ++i); //Gets the song from the list

	return *current;
}

*/
