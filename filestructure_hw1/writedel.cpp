// writedel.cpp => readdel.cpp
// write a stream of persons, using fstream.h 
/*
istream::getline
istream& getline(char*s, streamsize n);//입력 stream 으로 부터 문자를 읽어들여 s에 저장한다. delimiter를 '\n'를 사용한다.
istream& getline(char*s, streamsize n, char delim);//delimiter가 나타날 때까지 읽게 된다. delimiter는 delim 으로 전달된다.
*/
#include <iostream>
#include <fstream>
#include "person.h"
using namespace std;
// Figure 4.1 => 2장 소스코드로 실습
ostream & operator << (ostream & stream, Person & p)
{ // insert fields into file
	stream << p.LastName <<'|'<< p.FirstName <<'|'
		<< p.Address << '|' << p.City << '|'
		<< p.State <<'|' << p.ZipCode << '|';
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
int main (void){
	char filename [20];
	Person p;
	cout << "Enter the file name:"<<flush;
	cin.getline(filename, 19);
	ofstream file (filename, ios::out);
	if (file.fail()) {
		cout << "File open failed!" <<endl;
		return 0;
	}
	while (1) {
		// read fields of person
		cin >> p;
		if (strlen(p.LastName)==0) break;
		// write person to file
		file << p;
	}
	system("pause");
	return 1;
}
