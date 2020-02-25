//Lily Tran 989558404 CS202 HW3
#include "HW3.h"

//default constructor
Meeting::Meeting()
{
	name[0] = '\n';
	time = 0;
	date = 0;
	location[0] = '\n';
	keyword[0] = '\n';
	num_contacts = 0;

/*
	for(int i = 0; i < num_contacts; ++i)
	{
		contacts[i] = NULL;
	}
*/
}


//sets our members to the variables passed in
Meeting::Meeting(char *name, int time, int date, char *location, char *keyword)
{
	strcpy(this -> name, name);
	this -> time = time;
	this -> date = date;
	strcpy(this -> location, location);
	strcpy(this -> keyword, keyword);
}


void Meeting::add_contact(Contact &a_contact)
{
	Contact temp = a_contact;
	contacts[num_contacts] = temp; //calls copy constructor when use = between 2 objects
	++num_contacts;
}


char* Meeting::get_name() { return name; } 

int Meeting::get_time() { return time; }

int Meeting::get_date() { return date; }

char* Meeting::get_location() { return location; }

char* Meeting::get_keyword() { return keyword; }

int Meeting::get_num_contacts() { return num_contacts; }

void Meeting::display_contacts(ostream & out)
{	
	for (int i = 0; i < num_contacts; ++i)
	{
		contacts[i].write(out);	
	}
}


//displays all of our members
void Meeting::display()
{
	cout << endl;
	cout << "Name: " << name << endl;
	cout << "Time: " << time << endl;
	cout << "Date: " << date << endl;
	cout << "Location: " << location << endl;
	cout << "Keyword: " << keyword << endl;
	cout << "Contacts: " << endl;

	for (int i = 0; i < num_contacts; ++i)
	{
		contacts[i].display();
	}
	
	cout << "-----------------------------------------" << endl;
}
