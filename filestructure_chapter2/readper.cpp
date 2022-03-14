// write a stream of persons, using fstream.h 
//Assignment to students - writestr.cpp를 참조하여 수정하여 완성: 실습
#include <fstream>
#include <iostream>
#include <string.h>
#include "person.h"
#include <vector>

enum {LASTNAME, FIRSTNAME, ADDRESS, CITY, STATE, ZIPCODE};
const int MaxBufferSize = 20;

int getLength(std::ifstream& stream) {
	char c;
	stream.get(c);
	int length = (int)c;
	stream.get(c);
	return length;
}

Person *makePerson(char *buffer, char *line, int length) {
	Person* person = new Person;
	int idxcount = 0;
	int kind = 0;
	for (int i = 0; i < length; ++i) {
		if (line[i] == '|') {
			buffer[idxcount] = '\0';

			switch (kind) {
			case LASTNAME: { strcpy(person->LastName, buffer); ++kind; break; }
			case FIRSTNAME: { strcpy(person->FirstName, buffer); ++kind; break; }
			case ADDRESS: { strcpy(person->Address, buffer); ++kind; break; }
			case CITY: { strcpy(person->City, buffer); ++kind; break; }
			case STATE: { strcpy(person->State, buffer); ++kind; break; }
			case ZIPCODE: { strcpy(person->ZipCode, buffer); kind = 0; break; }
			}
			idxcount = 0;
		}
		else
			buffer[idxcount++] = line[i];
	}
	return person;
}

Person *ReadPerson(std::ifstream& stream)
{
	
	char buffer[MaxBufferSize];
	char c;

	int length = getLength(stream);
	if (stream.eof()) {
		return nullptr;
	}

	char* line = new char[length];
	stream.read(line, length);
	Person* person = makePerson(buffer, line, length);

	delete[] line;
	return person;
}

int main() {
	char filename[20];
	vector<Person*> people;
	Person *person;
	std::cout << "Enter the file name:" << flush;
	std::cin.getline(filename, 19);
	ifstream stream(filename, ios::in);
	if (stream.fail()) {
		cout << "File open failed!" << endl;
		return 0;
	}
	while (true) {
		person = ReadPerson(stream);
		if (person == nullptr) break;
		people.push_back(person);
	}

	for (Person *p : people) {
		cout << (*p) << endl;
	}
	for (Person* p : people) {
		delete[] p;
	}
	system("pause");
	return 0;
}

