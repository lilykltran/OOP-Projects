/* Lily Tran. 98958404. CS202 HW2. This file contains the constructors, destructors
 * and implentation of the base class Galaxy, as well as class Solar Systems and the node.
*/

#include "HW2.h"

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

	delete [] solar_systems;
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
	return 0;
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

	return 0;
}


