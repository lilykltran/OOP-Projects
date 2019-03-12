/* Lily Tran. 989558404. CS202 HW1. This client program contains class objects, function calls, and the text based menu that interacts
 * with the user. Prompting and error messages occur in this file.
*/

#include "HW1.h"

int main()
{

	//objects of classes
	Galaxy Gal;
	Solar_System *SS_Obj;

	srand(time(NULL)); //set RNG to current time.


	char SS[3][SIZE]; //Solar system names being stored. up to 3.
	char suns[3][SIZE]; //Sun names being stored. up to 3.

	char tempSS[SIZE2]; //the temp variable is the name of the solar system the user wants to fly to. stored here to then be searched later.
	char tempPlanet[SIZE2]; //temp planet name.

	int count = 0;

	char ans;

		do { //menu

		cout << "What would you like to do?" << endl;
		cout << "1. Create the solar systems." << endl;
		cout << "2. Travel to a certain destination via spaceship." << endl;
		cout << "3. Quit." << endl;
		
		cin >> ans;
		cin.ignore();

		if (ans == '1')
		{

			do {
				cout << endl;
				cout << "Enter the names of the three solar systems." << endl;
				cin.get(SS[count], SIZE, '\n'); //store each solar system in a new index.
				cin.ignore(100, '\n');
				cout << endl;
		
				cout << "Enter the names of the solar system's sun, in order." << endl;
				cin.get(suns[count], SIZE, '\n'); //store each sun in a new index.
				cin.ignore(100, '\n');
				cout << endl;

				Gal.create(suns[count], SS[count]); //call function that creates the array with what we just stored.

				++count; //next index!
			
			} while (count < 3); //up to 3 solar systems and suns
		
				
		}


		else if (ans == '2')
		{
			cout << endl;
			cout << "Here are all the solar systems available." << endl;
			Gal.display_all(); //call function that displays all the solar systems.
			cout << endl;

			cout << "Which solar system would you like to fly to?" << endl;
			cin.get(tempSS, SIZE2, '\n');
			cin.ignore(100, '\n');
			cout << endl;
		

			SS_Obj = Gal.SS_match(tempSS); //set Solar System's object equal to the function that finds a match to thta solar system.

			if (SS_Obj) //if we found a match,
			{
				cout << endl;
				cout << "That solar system's planets: " << endl;
				SS_Obj -> display_planets();
				//Gal.display_SS(tempSS); //call function that displays the planets.
				cout << endl;

				cout << "Which planet would you like to travel to?" << endl;
				cin.get(tempPlanet, SIZE2, '\n');
				cin.ignore(100, '\n');
				cout << endl;
					
				SS_Obj -> display_one_planet(tempPlanet); //display that planet's info.
			}
		
			else
				cerr << "No solar system match!" << endl;
			
		}

	} while (ans != '3'); //quit

	return 0;
}

