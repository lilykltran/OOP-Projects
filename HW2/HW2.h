/*Lily Tran. 989558404. CS202 HW2. This header contains all of the classes and its prototypes.
*/

#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <fstream>

using namespace std;

const int SIZE = 10;
const int SIZE2 = 20;

class Galaxy //The class Galaxy has a Solar_System
{
	public:
		Galaxy(); //constructor
		~Galaxy(); //destructor 
		class Solar_System* SS_match(char *); //returns pointer to that solar system that matches what the user passed in.
		int display_SS(char*); //displays a specific solar system's planets.
		void display_all(); //displays all the solar system.
		int create(char *, char *); //creates the solar system array.

	protected: class Solar_System **solar_systems; //the number of solar systems. This is the array.
};



class Solar_System //The class Solar_System has a list of planets
{

	public:
		Solar_System(); //constructor
		Solar_System(char *, char*); //constructor that creates the array with its data members.
		~Solar_System(); //desctructor calls delete_nodes.
		Solar_System(const Solar_System &); //copy constructor 
		void display_name(); //displays just the name of the planets.
		int compare(char *); //compares name of SS
		int display_planets(); //displays planets of a specific solar system. Uses return value in SS_match
		void display_one_planet(char *); //search function for one planet. Displays its contents.
		void read_in();
		//bool inner_or_outer(); //determines that planet is inner or outer based on its distance.

	protected:
		class node * rear; //Array of CLLS
		char suns[SIZE]; //the name of the sun of each solar system.
		char SS_name[SIZE2]; //the name of each solar system.
		void delete_nodes(node *&rear); //function that deletes the DLL.
		void copy_CLL(node *&dest, node * source);
		int display_planets(node *rear); //recursive function
};



class Planet //The base class.
{

	public:
		Planet(); //default constructor w/ initialization list that sets data members to 0.
		~Planet(); //destructor
		Planet(const Planet &); // copy constructor to copy all data members
		virtual void display(); //displays Planet variables. called by solar system class
		void display_name(); //displays Planet name. called by solar system class.
		int display_distance(); //displays distance to determine innor or outer in solar system
		int compare(char *); //compares planet name passed in vs name stored.
		void add_data(float, int, char *, float); 
		virtual void inner_or_outer() = 0; //pure virtual function that says if it's an inner or outer

	protected:
		float distance; //the distance of that planet from the sun. read in from external file.
		int moons; //number of moons that planet has. read in.
		char name[20]; //name of planet. read in from external file.
		float mass; //mass of planet. read in from external file.
};



class Inner: public Planet //An inner planet is a Planet.
{
	public:
		Inner();
		bool rocky_or_gas(); //determines randomly if that planet is a rocky or gas planet. More likely to be rocky.
		void display(); //displays all variables of the planet
		void inner_or_outer(); //must implement bc pure virtual!

	protected:
		bool flag; //the flag that means rocky or gas.
		
};



class Outer: public Planet //An outer planet is a Planet.
{
	public:
		Outer();
		bool rocky_or_gas(); //determines randomly if that planet is a rocky or gas planet. More likely to be gassy.
		void display(); //displays all variables of the planet
		void inner_or_outer(); //must implement bc pure virtual!

	protected:
		bool flag; //the flag that means rocky or gas.
};



class node //A node contains a Planet.
{
	public:
		node(); //default constructor, sets next and previous to NULL
		node(const node &); //copy constructor
		node(Planet *& in);
		~node(); //destructor
		node *& go_forward(); //returns a pointer to the next node
		int add_after(node *); //inserts node after
		void set_forward(node *in); //set the next pointer to variable passed in.
		void display(); //calls planet function that displays its data.
		Planet * get_data(); //returns data in order to access planet functions.
	
	protected: 
		Planet *data; //contains a planet.
		node * next;
};


