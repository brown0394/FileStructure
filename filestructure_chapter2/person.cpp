// person.cpp
#include <iostream>
#include <string.h>
#include "person.h"
Person::Person()
{//constructor
	LastName[0] = 0; FirstName[0] = 0; Address[0] = 0;
	City[0] = 0; State[0] = 0; ZipCode[0] = 0;
}

ostream& operator << (ostream& stream, Person& p)
{ // insert fields into file
	stream << p.LastName << p.FirstName << p.Address
		<< p.City << p.State << p.ZipCode;
	return stream;
}

istream& operator >> (istream& stream, Person& p)
{ // read fields from input
	cout << "Enter last name, or <cr> to end: " << flush;
	stream.getline(p.LastName, 30);
	if (strlen(p.LastName) == 0) return stream;
	cout << "Enter first name: " << flush; stream.getline(p.FirstName, 30);
	cout << "Enter address: " << flush; stream.getline(p.Address, 30);
	cout << "Enter city: " << flush; stream.getline(p.City, 30);
	cout << "Enter state: " << flush; stream.getline(p.State, 15);
	cout << "Enter zip code: " << flush; stream.getline(p.ZipCode, 10);
	return stream;
}

