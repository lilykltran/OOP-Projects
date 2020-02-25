/*Lily Tran. 989558404. HW2. This file contains implementation
 * of the solar system class.
*/

#include "HW2.h"


Solar_System::Solar_System(char *sun_name, char *ss_name) //constructor that copies solar system info
{
	strcpy(suns, sun_name);	 //copies what is passed in into the class member.
	strcpy(SS_name, ss_name);
	rear = NULL;

	read_in();
}



Solar_System::~Solar_System() //destructor that calls delete nodes function
{
	node *temp = rear -> go_forward();
	rear -> set_forward(NULL); //break the CLL into a LLL
	delete_nodes(temp); //calls delete nodes function.
}



void Solar_System::delete_nodes(node *&rear) //function that deletes all the nodes.
{
	if (!rear)
		return;
	
	node *temp = rear;
	rear = rear -> go_forward();
	delete temp;

	delete_nodes(rear);
}



void Solar_System::read_in() //read in function that reads in planet's info.
{
	int random = rand() % 20; //randomly stores planet info. mod by number of planets available in the file.
	int counter = 0;
	ifstream read;
	read.open("planets.txt"); //connect to file. 
	
	if (!read) //makes sure connected fo file. 
		return;


	while(read && !read.eof() && counter < random) //previous read is successful
	{
		
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

		Planet *temp;// = new Planet();

		if (distance < 400) //dynamic binding
		{
			temp = new Inner(); //create an inner planet
		}
		else
			temp = new Outer(); //create an outer planet


		temp -> add_data(distance, moons, name, mass); //call the add data function that simply copies data from file into members.


		if (!rear)
		{
			rear = new node(temp); //create a new node
			rear -> set_forward(rear); //point it to itself
		}
			
		else if (rear)
		{

			node *current = new node(temp); //call node constructor and pass in the Planet pointer
			current -> set_forward(rear -> go_forward()); 
			rear -> set_forward(current); //connect the CLL
	}

		++counter; //increment counter to read in all 20 planets.
	}

	read.ignore(100, '|');
	read.close();
}




Solar_System::Solar_System(const Solar_System & SS_Obj) //copy constructor that copies name of solar system passed in into the array.
{		
	strcpy(suns, SS_Obj.suns); //copies solar system info.
	strcpy(SS_name, SS_Obj.SS_name);

	if(SS_Obj.rear) 
	{
		rear = new node(*SS_Obj.rear); //create a new node
		rear -> set_forward(rear);
	}

	node *temp = SS_Obj.rear -> go_forward();
	SS_Obj.rear -> set_forward(NULL); //break the CLL to be a LLL
	
	copy_CLL(rear, temp);
	SS_Obj.rear -> set_forward(temp); //connect original list again.


	//connecting copied list
	node *temp2 = rear;

	while (rear -> go_forward())
	{
		rear = rear -> go_forward();
	}
	
	rear -> set_forward(temp2);
}



void Solar_System::copy_CLL(node *& dest, node * source) //copying it as a LLL after breaking the CLL
{
	if (!source)
	{
		return;
	}

	dest = new node(*source);
	
	copy_CLL(dest -> go_forward(), source -> go_forward());
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



int Solar_System::display_planets() //wrapper function to display planets.
{
	if (!rear)
	{
		cout << "This solar system has no planets!" << endl;
		return 0;
	}

	return display_planets(rear -> go_forward());
}



int Solar_System::display_planets(node *rear) //displays all of the planet names in that solar system.
{
	node* temp = rear -> go_forward();
	
	if (!rear)
		return 0;

	if (temp == this -> rear) //if we are at the beginning of the list again, stop traversing
		return 0;

	temp -> get_data() -> display_name(); //call node function that gets data and function that displays planet info from planet class
	return display_planets(rear -> go_forward());
}



void Solar_System::display_one_planet(char *name) //displays the planet that the user wants to travel to and its information.
{
	node *current = rear -> go_forward();

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


