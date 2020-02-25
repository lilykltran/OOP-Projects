//Lily Tran 989558404 CS202 HW3
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;

const int SIZE = 30;
const int MAX_CONTACTS = 10;


class Contact //Class contact has the variables of a contact
{
	public:
		Contact(); //default constructor
		Contact(const Contact &); //copy constructor
		void display(); //displays members
		void set_name(char *name); //sets member to name passed in
		void set_email(char *email); //sets member to name passed in
		int match(char *); 
		char* get_name(); //returns name
		char* get_email(); //returns email
		void write(ostream &); //returns contacts 

	protected:
		char name[SIZE]; //name of the contact
		char email[SIZE]; //email of the contact
};


class Meeting //Class meeting contains array of contacts
{
	public:
		Meeting(); //default constructor
		Meeting(char *name, int time, int date, char *location, char *keyword); //sets members to variables passed in
		void add_contact(Contact &a_contact); //adds contact to the meeting
		void display(); //displays members
		void display_contacts(ostream &); //displays list of contacts
		char* get_name(); //returns name
		int get_time(); //returns time
		int get_date(); //returns date
		char* get_location(); //returns location
		char* get_keyword(); //returns keyword
		int get_num_contacts(); //returns number of contacts

	protected:
		char name[SIZE]; //name of meeting
		int time; //time of meeting in military time
		int date; //date of meeting without delimitors
		char location[SIZE]; //location of meeting
		char keyword[SIZE]; //keyword of meeting. This is will be stored in RBT_Node
		Contact contacts[MAX_CONTACTS]; //Class meeting contains array of contacts up to 10
		int num_contacts; //number of contacts in the array
};



class LLL_Node //class LLL_node contains a Meeting
{
	public:

	LLL_Node(Meeting* a_meeting); //Default constructor
	~LLL_Node(); //Destructor
	LLL_Node* & get_next(); //Returns the next pointer by reference
	Meeting* get_data(); //returns data
	int set_data(Meeting* a_meeting); //Sets the datas
	int append(LLL_Node* a_node); //sets next pointer to the argument passed in
	int display(); //Displays meeting info
	int set_next(LLL_Node *to_add); //set next to argument passed in
	int add_contact(Contact &a_contact);


	protected:
		Meeting *data; //Data in the LLL's node is a meeting.
		LLL_Node *next; 
};



class LLL //class LLL has the list of all the meetings
{
	public:
		LLL(); //default constructor 
		LLL(const LLL &); //copy constructor. Calls the copy_list function.
		~LLL(); //destructor
		int display(); //displays all the meetings in the list.
		int add_meeting(Meeting *a_meeting); //adds a meeting to the list
		void write(); //writes out to file meetings.txt
		
		//Assigns the list to just contain one list, or copy another list
		LLL & operator=(const Meeting &);
		LLL & operator=(const LLL &);

		//Add a meeting to the list, or add two list together
		LLL & operator+=(const Meeting &);
		LLL & operator+=(const LLL &);

		//Add a meeting to a list, or add two lists together
		friend LLL operator+(const Meeting &, const LLL &);
		friend LLL operator+(const LLL &, const Meeting &);
		friend LLL operator+(const LLL &, const LLL&);

		//Check if a meeting is in the list, or if two lists are the same
		friend bool operator==(const Meeting &, const LLL &);
		friend bool operator==(const LLL &, const Meeting &);
		friend bool operator==(const LLL &, const LLL &);

		friend bool operator!=(const Meeting &, const LLL &);
		friend bool operator!=(const LLL &, const Meeting &);
		friend bool operator!=(const LLL &, const LLL &);

		friend bool operator>(const LLL &, const LLL &);

		friend bool operator>=(const LLL &, const LLL &);

		friend bool operator<(const LLL &, const LLL &);

		friend bool operator<=(const LLL &, const LLL &);

		friend std::ostream & operator<<(std::ostream &, const LLL &); //Displays all meetings in the list

		Meeting & operator[](int) const; //Get a meeting from the list.

	protected:
		LLL_Node *head;
		LLL_Node *tail;
		int num_meetings;
		int copy(LLL_Node* & dest, LLL_Node* source); //copies list
};



class RBT_Node //class RBT_Node contains the LLL that has the meetings and the keyword of each meeting
{
	public:
		RBT_Node(LLL a_meeting); //default constructor
		RBT_Node(const RBT_Node &); //copy constructor
		RBT_Node(Meeting to_add);
	        ~RBT_Node(); //destructor	
		RBT_Node* & get_left(); //return left pointer
		RBT_Node* & get_right(); //return right pointer
		RBT_Node* & get_parent(); //return parent pointer
		bool get_internal(); //return internal pointer
		void set_internal(bool); //sets internal value to argument
		int add_meeting(Meeting); //adds meeting to the node
		char *get_title(); //returns title
		void display () { meetings.display(); }	//calls meeting's display function
		

	protected:
		LLL meetings; //RBT's node contains the linear linked list 
		char *title; //store meetings keyword
		RBT_Node *left;
		RBT_Node *right;
		RBT_Node *parent;
		bool internal; //flag 
};



class Tree //class Tree adds LLL of meetings according to its node's keyword
{
	public:
		Tree(); //default constructor
		Tree(const Tree &); //copy constructor
		~Tree(); //destructor
		int insert(Meeting a_meeting); //insert meeting to tree
		int compare(char *, char*); //compares keyword in tree to keyword passed in by user
		RBT_Node* find(char *); //finds matching keyword
		void display(); //displays meetings in tree
		int copy(const Tree & source);
		int remove_all(); //removes all nodes. called in destructor.

		//Assigns the list to just contain one list, or copy another list
		Tree & operator=(const Meeting &);
		Tree & operator=(const Tree &);

		//Add a meeting to the list, or add two list together
		Tree & operator+=(const Meeting &);
		Tree & operator+=(const Tree &);

		//Add a meeting to a list, or add two lists together
		friend Tree operator+(const Meeting &, const Tree &);
		friend Tree operator+(const Tree &, const Meeting &);
		friend Tree operator+(const Tree &, const Tree &);

		//Check if a meeting is in the list, or if two lists are the same
		friend bool operator==(const Meeting &, const Tree &);
		friend bool operator==(const Tree &, const Meeting &);
		friend bool operator==(const Tree &, const Tree &);

		friend bool operator!=(const Meeting &, const Tree &);
		friend bool operator!=(const Tree &, const Meeting &);
		friend bool operator!=(const Tree &, const Tree &);

		friend bool operator>(const Tree &, const Tree &);

		friend bool operator>=(const Tree &, const Tree &);

		friend bool operator<(const Tree &, const Tree &);

		friend bool operator<=(const Tree &, const Tree &);

		friend std::ostream & operator<<(std::ostream &, const Tree &); //Displays all meetings in the list

		Meeting & operator[](int) const; //Get a meeting from the tree

			
	protected:
		RBT_Node *root;
		int copy(RBT_Node* & dest, RBT_Node* source); //Copies the tree recursively
		void display(RBT_Node *root); //displays tree recursively
		int insert(RBT_Node *&root, Meeting a_meeting); //recursive insert function
		int remove_all(RBT_Node *& root); //removes all nodes recursively
		RBT_Node *find(RBT_Node *root, char *); //recursive find function
		int balance(RBT_Node* added, Meeting a_meeting); //Balances the tree
		void rotate_left(RBT_Node* root); //Rotates a set of nodes left
		void rotate_right(RBT_Node* root); //Rotates a set of nodes right
};

