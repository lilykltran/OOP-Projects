//Lily Tran. 989558404. HW2. This planet contains implementation of the planet the node class that contains the planet.
//and the derived classes inner and outer planets.

#include "HW2.h"

Planet::Planet() {}

Planet::Planet(const Planet & to_copy) : distance(to_copy.distance), moons(to_copy.moons), mass(to_copy.mass)  //Copys the distance and number of moons
{
	strcpy(name, to_copy.name);
}



Planet::~Planet() {} //destructor. no body bc no dynamic memory.



void Planet::display() //called in node's display function.
{
	cout << endl;
	cout << "That planet's info: " << endl;
	cout << "Distance from the sun: " << distance << endl;
	cout << "Number of moons: " << moons << endl;
	cout << "Name of the planet: " << name << endl;
	cout << "Mass of the planet: " << mass << endl;	
	cout << endl;
}


void Planet::display_name() //called in display_planets to display just the name of all the planets.
{
	cout << "Name: " << name << endl;
}


int Planet::compare(char *planet_name) //called in display_one_planet in SS class. Compares name passed in vs name stored..
{
	return !strcmp(name, planet_name);
}

void Planet::add_data(float tempDistance, int tempMoons, char *tempName, float tempMass)
{
	distance = tempDistance;
	moons = tempMoons;
	strcpy(name, tempName);
	mass = tempMass;
}



//////////////INNER IMPLEMENTATION//////////////////



Inner::Inner() //default constructor that calls rocky or gas function.
{
	rocky_or_gas();
} 



bool Inner::rocky_or_gas() //Randomly determines rocky or gassy, but takes into account that an inner planet is more liekly to be rocky.
{
	int random = (rand() % 3); //random number between 0 and 2.

	if (random < 2) 
		flag = true; //more likely to be rocky!
	else
		flag = false; 

	return 0;
}


void Inner::display()
{
	cout << endl;
	cout << "That INNER planet's info: " << endl;
	cout << "Distance from the sun: " << distance << endl;
	cout << "Number of moons: " << moons << endl;
	cout << "Name of the planet: " << name << endl;
	cout << "Mass of the planet: " << mass << endl;	
	cout << endl;
}


void Inner::inner_or_outer()
{
	cout << "This planet is an inner planet." << endl;
}


//////////////OUTER IMPLEMENTATION///////////



Outer::Outer() // default constructor that calls rocky or gas function.
{
	rocky_or_gas();
}



bool Outer::rocky_or_gas() //Randomly determines rocky or gassy, but takes into account that an outer planet is more likely to be gassy.
{
	int random = (rand() % 3); //random number between 0 and 2.

	if (random < 2)
		flag = false; //more likely to be gassy! 
	else
		flag = true; 

	return 0;
}



void Outer::display()
{
	cout << endl;
	cout << "This OUTER planet's info: " << endl;
	cout << "Distance from the sun: " << distance << endl;
	cout << "Number of moons: " << moons << endl;
	cout << "Name of the planet: " << name << endl;
	cout << "Mass of the planet: " << mass << endl;	
	cout << endl;
}


void Outer::inner_or_outer()
{
	cout << "This planet is an outer planet." << endl;
}



////NODE IMPLEMENTATION////



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
}



node::node() : next(NULL) {} //Default constructor, sets next and previous pointers to NULL



node::~node() //destructor
{
	next = NULL;
}



node::node(Planet *& in) //constructor that stores planet's information into node's data.
{
	data = in;
	next = NULL;
}



node *& node::go_forward() //returns the next pointer.
{
	return next;
}



void node::set_forward(node *in) //sets the next pointer to be the node variable.
{
	next = in;	
}
