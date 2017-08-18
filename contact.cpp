//Lily Tran 989558404 CS202 HW3
#include "HW3.h"

//default constructor
Contact::Contact()
{
	name[0] = '\n';
	email[0] = '\n';
}


//copy constructor
Contact::Contact(const Contact & to_copy)
{	
	strcpy(name, to_copy.name);	
	strcpy(email, to_copy.email);
}


//returns the value of the match
int Contact::match(char *name)
{
	return !strcmp(this -> name, name);
}


//displays contact info
void Contact::display()
{
	cout << endl;
	cout << "Name: " << name << endl;
	cout << "Email: " << email << endl;
	cout << endl;
}


//sets our name to the name passed in
void Contact::set_name(char *name)
{
	strcpy(this -> name, name);
}



//sets our email to the email passed in
void Contact::set_email(char *email)
{
	strcpy(this -> email, email);
}


//returns name
char* Contact::get_name()
{
	return name;
}


//returns email
char *Contact::get_email()
{
	return email;
}


//displays contact info
void Contact::write(ostream & out)
{
	out << name << "," << email << "|";
}
