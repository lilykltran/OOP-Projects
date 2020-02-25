//Lily Tran 989558404 CS202 HW3
#include "HW3.h"

int main()
{
	//objects
	LLL list;
	Meeting *a_meeting;
	Tree a_tree;
	Contact contacts[MAX_CONTACTS];

	int ans;

	char name[SIZE];
	int date;
	int time;
	char location[SIZE];
	char keyword[SIZE];
	char email[SIZE];
	int num = 0; 
	char response;

	do { 
	
		cout << "Enter a contact." << endl;
		cin.get(name, SIZE, '\n');
		cin.ignore(100, '\n');
		cout << endl;
		
		cout << "Enter their email." << endl;
		cin.get(email, SIZE, '\n');
		cin.ignore(100, '\n');
		cout << endl;
	
		contacts[num].set_name(name); //store name and email
		contacts[num].set_email(email);	
		
		++num; //increment number of contacts

		cout << "Do you want to enter another contact? (y or n)" << endl;
		cin >> response;
		cin.ignore();
		cout << endl;


	} while(num < MAX_CONTACTS && tolower(response) != 'n'); //can't go over max

	do
	{
		cout << endl;
		cout << "Enter a command." << endl;
		cout << "1. Create a new meeting." << endl;
		cout << "2. View meetings and its info (list)." << endl;
		cout << "3. View meetings based on a keyword (tree)." << endl;
		cout << "4. Quit." << endl;
		cout << endl;
		cin >> ans;
		cin.ignore();

		switch (ans)
		{

		case 1:
			cout << endl;
			cout << "What is the name of the meeting? (e.g; Lily's Lit af bday)" << endl;
			cin.get(name, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;
			
			cout << "Enter its date. (e.g; 08062017)" << endl;
			cin >> date;
			cin.ignore();
			cout << endl;
			
			cout << "Enter its time. (e.g; 1600)" << endl;
			cin >> time;
			cin.ignore();
			cout << endl;

			cout << "Enter its location. (e.g; Seaside beach)" << endl;
			cin.get(location, SIZE, '\n'); 
			cin.ignore(100, '\n');
			cout << endl;
		
			cout << "Enter its keyword. (e.g; birthday)" << endl;
			cin.get(keyword, SIZE, '\n');
			cin.ignore(100, '\n');
			cout << endl;

			a_meeting = new Meeting(name, date, time, location, keyword);//call constructor that stores these variables

			
			cout << endl;
			cout << "WHO WOULD YOU LIKE TO INVITE?" << endl;
	
			for (int i = 0; i < num; ++i)
			{
				contacts[i].display(); //call function that displays the contacts
			}

			do {

				cout << "Enter the name of the contact you want to add to the meeting." << endl;
				cin.get(name, SIZE, '\n');
				cin.ignore(100, '\n');
				
			
				for (int i = 0; i < MAX_CONTACTS; ++i)
				{
					if(contacts[i].match(name)) //call match function
					a_meeting -> add_contact(contacts[i]); //adds contact to the meeting
				}	

				cout << "Do you want to add another contact? (y or n)" << endl;
				cin >> response;
				cin.ignore();
				
			} while (tolower(response) != 'n');

			list.add_meeting(a_meeting); //adds meeting to list

			a_tree.insert(*a_meeting); //adds meeting to tree
		
			break;

		case 2:
			list.display();	//displays all info in the list
			break;

		case 3:
			cout << "Enter the keyword." << endl;
			cin.get(keyword, SIZE, '\n');
			cin.ignore(100, '\n');

			RBT_Node * ret = a_tree.find(keyword); //catch function
			ret -> display(); //display all info in the tree
			break;

		}

	} while (ans != 4);

	list.write(); //write out meetings to file function call
	
	return 0;
}
