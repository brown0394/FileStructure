// D.4 writestr.cpp
// write a stream of persons, using fstream.h 
#include <fstream>
#include <iostream>
#include <string.h>
#include "person.h"

int main (void){
	char filename [20];
	Person p;
	cout << "Enter the file name:"<<flush;
	cin.getline(filename, 19);
	ofstream stream (filename, ios::out);
	if (stream.fail()) {
		cout << "File open failed!" <<endl;
		return 0;
	}
	while (1) {
		cin >> p; // read fields of person
		if (strlen(p.LastName)==0) break;
		// write person to output stream
		stream << p; // write fields of person
	}
	system("pause");
	return 1;
}

