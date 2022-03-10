// D.3 person.h
#ifndef PERSON
#define PERSON
using namespace std;
class Person 
{ public:
	// data members
	char LastName [11]; char FirstName [11]; char Address [16];
	char City [16]; char State [3]; char ZipCode [10];
	// method
	Person (); // default constructor
	friend ostream& operator << (ostream& stream, Person& p);
	friend istream& operator >> (istream& stream, Person& p);
};
#endif