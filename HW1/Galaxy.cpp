/* Lily Tran. 98958404. CS202 HW1. This file contains the constructors, destructors
 * and implentation of the base class Galaxy, as well as class Solar Systems and the node.
*/

#include "HW1.h"

Galaxy::Galaxy() //constructor
{
	solar_systems = new Solar_System*[3]; //create the solar system

	for (int i = 0; i < 3; ++i)
	{
		solar_systems[i] = NULL; //sets each index to NULL
	}
}



Galaxy::~Galaxy() //destructor that deallocates memory for solar systems array
{
	for (int i = 0; i < 3; ++i)
	{
		delete solar_systems[i];
	}
}



int Galaxy::create(char *sun_name, char *ss_name) //Creates the array.
{
	for (int i = 0; i < 3; ++i)
	{
		if (solar_systems[i] == NULL) //if there is an open slot in the array,
		{
			solar_systems[i] = new Solar_System(sun_name, ss_name); //add a new solar system.
			return 1;
		}
	}
}



void Galaxy::display_all() //displays the name of the solar system.
{
	for (int i = 0; i < 3; ++i)
	{
		solar_systems[i] -> display_name(); //calls the display_name function that couts the solar system name
	}
}


int Galaxy::display_SS(char* in) //displays a specific solar system's information.
{
	Solar_System* mySS = SS_match(in); //pointer to solar_system, setting it equal to SS_match function that finds name match.

	if (mySS) //if we have a match
		mySS -> display_planets(); //call function that displays the planets.
}



Solar_System::Solar_System(char *sun_name, char *ss_name) //constructor that copies solar system info
{
	strcpy(suns, sun_name);	 //copies what is passed in into the class member.
	strcpy(SS_name, ss_name);
	head = NULL;

	read_in();
}



Solar_System::~Solar_System() //destructor
{
	delete_nodes(head); //calls delete nodes function.
}



void Solar_System::delete_nodes(node *&head) //function that deletes all the nodes.
{
	if (!head)
		return;

	node *temp = head -> go_forward();
	delete head;
	head = temp;
}



void Solar_System::read_in() //read in function that reads in planet's info.
{
	int random = rand() % 20; //randomly stores planet info. mod by number of planets available in the file.
	int counter = 0;
	ifstream read;
	read.open("planets.txt"); //connect to file. 
	
	if (!read) //makes sure connected fo file. 
		return;

	node * current = head;

	while(read && !read.eof() && counter < random) //previous read is successful
	{
		Planet *temp = new Planet();
		
		float distance, mass;
		int moons;
		char name[20];

		read >> distance; //read in info up until the delimitter.
		read.ignore(20, '|');

		read >> moons;
		read.ignore(20, '|');

		read.get(name, 20, '|');
		read.ignore(100,'|');

		read >> mass;
		read.ignore(20, '\n');

		temp -> add_data(distance, moons, name, mass); //call the add data function that simply copies data from file into members.

		current = new node(temp); //call node constructor and pass in the Planet pointer.

		if (!head)
			head = current;

		else if (head)
		{
			node *temp1 = head;
			for (int i = 0; i < counter - 1; ++i) //traverse until the max planets.
			{
				temp1 = temp1 -> go_forward(); //traverse temp1 
			}

			temp1 -> set_forward(current); //set it equal to current.
		}

		current = current -> go_forward(); //traverse

		++counter; //increment counter to read in all 20 planets.
	}

	read.ignore(100, '|');
	read.close();
}




Solar_System::Solar_System(const Solar_System & SS_Obj) //copy constructor that copies name of solar system passed in into the array.
{		
	strcpy(suns, SS_Obj.suns); //copies solar system info.
	strcpy(SS_name, SS_Obj.SS_name);

	if(SS_Obj.head) 
	{
		head = new node(*SS_Obj.head); //create a new node
		head -> set_backward(NULL);
	}

	node *temp = SS_Obj.head->go_forward();
	node *temp2 = head->go_forward();
	node* temp3 = head;

	while (temp)
	{
		temp2 = new node(*temp);
		temp2 -> set_backward(temp3);
		temp = temp -> go_forward();
		temp2 = temp2 -> go_forward();
		temp3 = temp3 -> go_forward();
	}
}



void Solar_System::display_name() //displays just the name of the solar system and its sun
{
	cout << "name: " << SS_name << endl;
	cout << "sun: " << suns << endl;
}



int Solar_System::compare(char *name) //checks to see if the name passed in from user matches the stored data.
{
	return !strcmp(name, SS_name); //returns 1 or 0 depending on if there is a match.
}



int Solar_System::display_planets() //displays all of the planet names in that solar system.
{
	node* temp = head;
	
	if (head) //checks to make sure list exists before we continue.
		cout << "List exists" << endl;

	while (temp) //while we are not NULL
	{
		temp -> get_data() -> display_name(); //call the display function in class planets that displays the names of the planets.
		temp = temp -> go_forward(); //traverse.
	}

	return 1;
}



void Solar_System::display_one_planet(char *name) //displays the planet that the user wants to travel to and its information.
{
	node *current = head;

	while (current) //while not NULL
	{
		if (current -> get_data() -> compare(name)) //call function that compares the name passed in vs the data.
		{
			current -> display(); //calls the display function that displays planet variables.
			return;
		}

		current = current -> go_forward(); //traverse the list.
	}
}




Solar_System* Galaxy::SS_match(char *tempSS) //this function checks to see if the solar system passed in matches
{
	for (int i = 0; i < 3; ++i)
	{
		if (solar_systems[i] != NULL) //if the index we are at is not null
		{
			if (solar_systems[i] -> compare(tempSS)) //compare ss  name passed in with ss name in array.
				return solar_systems[i]; //return that solar system index.
		}
	}
	return NULL; //if there is no match, just return NULL.
}


Planet* node::get_data() //returns data of type Planet. Used to access planet's functions.
{
	return data;
}


void node::display() //calls planet's display function that displays all of the planet info.
{
	data -> display();
}



node::node(const node & to_copy) //constructor that copies data.
{
	data = to_copy.data;
	next = NULL;
	previous = NULL;
}

node::node() : next(NULL), previous(NULL) {} //Default constructor, sets next and previous pointers to NULL


node::~node()
{
	delete data; //deletes data.
	next = NULL;
	previous = NULL;
}

node::node(Planet *& in)
{
	data = in;
	next = NULL;
	previous = NULL;
}

node *& node::go_forward() //returns the next pointer.
{
	return next;
}

void node::set_forward(node *in) //sets the next pointer to be the node variable.
{
	next = in;	
}

void node::set_backward(node *in) //sets the backwords pointer to be the node variable.
{
	previous = in;
}

node *& node::go_backward() //returns the previous pointer.
{
	return previous;
}

int node::add_before(node* to_add) //Adds the argument node before the calling node in the DLL. Returns 0 if argument node pointer is NULL
{
	if (!to_add)
		return 0;
	
	to_add->previous = previous;
	to_add->next = this;
	previous = to_add;

	return 1;
}

int node::add_after(node* to_add) //Adds argument node after the calling node in the DLL. Returns 0 if argument node pointer is NULL
{
	if (!to_add)
		return 0;

	to_add->previous = this;
	to_add->next = next;
	next = to_add;

	return 1;
}
