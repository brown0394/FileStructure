// test.cc// Copyright 1997, Gregory A. Riccardi
// 4장 과제2: while(1) { } 문을 완성한다.
#include <fstream>
#include <string.h>
#include <iomanip>
#include "fixtext.h"
#include "lentext.h"
#include "deltext.h"
#include "person.h"
using namespace std;
//*
void testFixText()
{
	Person person;
	FixedTextBuffer Buff(6);
	Person::InitBuffer(Buff);
	strcpy(person.LastName, "Ames      ");
	strcpy(person.FirstName, "Mary      ");
	strcpy(person.Address, "123 Maple      ");
	strcpy(person.City, "Stillwater     ");
	strcpy(person.State, "OK");
	strcpy(person.ZipCode, "74075    ");
	person.Print(cout);
	person.Pack(Buff);
	Buff.Print(cout);
	ofstream TestOut("fixtext.dat", ios::out | ios::binary);
	Buff.Write(TestOut);
	TestOut.close();
	ifstream TestIn("fixtext.dat", ios::in | ios::binary);
	FixedTextBuffer InBuff(6);
	Person::InitBuffer(InBuff);
	Buff.Read(TestIn);
	person.Unpack(Buff);
	person.Print(cout);
	Person person;
	Person* stable[10];
	FixedTextBuffer Buff(6);
	Person::InitBuffer(Buff);
	char filename[20];
	cout << "Enter the file name:" << flush;
	cin.getline(filename, 19);
	//*
	while (1)
	{
		int count;
		int select;
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Person objects by inputing
			cout << "the number of Person object records : ";
			cin >> count;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			for (int i = 0; i < count; i++)
			{
			}
			break;
		case 2:
			// to display the array of Person objects into screen
			for (int i = 0; i < count; i++)
			{

			}
			break;
		case 3:
		{
			// to write the array of Person objects into a file
			ofstream fostream(filename, ios::out | ios::in);
			if (fostream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			Person::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{

			}
			fostream.close();
			break;
		}
		case 4:
		{
			// to read the array of Person records from the file
			ifstream fistream(filename, ios::in | ios::binary);
			if (fistream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			Person::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{

			}
			fistream.close();
			break;
		}
		default:
			// others
			exit(0);
			break;
		}
	}
}
//*/
//*
int testLenText()
{
	char filename[20];
	cout << "\nTesting LengthTextBuffer" << endl;
	Person person;
	LengthTextBuffer Buff;
	Person::InitBuffer(Buff);
	strcpy(person.LastName, "Ames");
	strcpy(person.FirstName, "Mary");
	strcpy(person.Address, "123 Maple");
	strcpy(person.City, "Stillwater");
	strcpy(person.State, "OK");
	strcpy(person.ZipCode, "74075");
	person.Print(cout);
	Buff.Print(cout);
	cout << "pack person " << person.Pack(Buff) << endl;
	Buff.Print(cout);
	ofstream TestOut("lentext.dat", ios::out | ios::binary);
	Buff.Write(TestOut);
	Buff.Write(TestOut);
	strcpy(person.FirstName, "Dave");
	person.Print(cout);
	person.Pack(Buff);
	Buff.Write(TestOut);
	TestOut.close();
	ifstream TestIn("lentext.dat", ios::in | ios::binary);
	LengthTextBuffer InBuff;
	Person::InitBuffer(InBuff);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << person.Unpack(Buff) << endl;
	person.Print(cout);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << person.Unpack(Buff) << endl;
	person.Print(cout);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << person.Unpack(Buff) << endl;
	person.Print(cout);
	//*
	while (1)
	{
		int count;
		int select;
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Person objects by inputing
			cout << "the number of Person object records : ";
			cin >> count;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			for (int i = 0; i < count; i++)
			{
			}
			break;
		case 2:
			// to display the array of Person objects into screen
			for (int i = 0; i < count; i++)
			{

			}
			break;
		case 3:
			{
			// to write the array of Person objects into a file
			ofstream fostream(filename, ios::out | ios::in);
			if (fostream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			Person::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{

			}
			fostream.close();
			break;
			}
		case 4:
			{
			// to read the array of Person records from the file
			ifstream fistream(filename, ios::in | ios::binary);
			if (fistream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			Person::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{

			}
			fistream.close();
			break;
			}
		default:
			// others
			exit(0);
			break;
		}
	}
	return 1;
}
//*/
int testDelText()
{
	char filename[20];
	cout << "\nTesting DelimTextBuffer" << endl;
	Person person;
	strcpy(person.LastName, "Ames");
	strcpy(person.FirstName, "Mary");
	strcpy(person.Address, "123 Maple");
	strcpy(person.City, "Stillwater");
	strcpy(person.State, "OK");
	strcpy(person.ZipCode, "74075");
	person.Print(cout);
	DelimTextBuffer Buff;
	Person::InitBuffer(Buff);
	Buff.Print(cout);
	cout << "pack person " << person.Pack(Buff) << endl;
	Buff.Print(cout);
	ofstream TestOut("deltextperson.txt", ios::out | ios::binary | ios::trunc);
	Buff.Write(TestOut);
	Buff.Write(TestOut);
	strcpy(person.FirstName, "Dave");
	person.Print(cout);
	person.Pack(Buff);
	Buff.Write(TestOut);
	TestOut.close();
	ifstream TestIn("deltextperson.txt", ios::in | ios::binary);
	DelimTextBuffer InBuff;	Person::InitBuffer(InBuff);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << person.Unpack(Buff) << endl;
	person.Print(cout);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << person.Unpack(Buff) << endl;
	person.Print(cout);
	cout << "read " << Buff.Read(TestIn) << endl;
	cout << "unpack " << person.Unpack(Buff) << endl;
	person.Print(cout);
	//*
	while (1)
	{
		int count; int select;
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Person objects by inputing
			cout << "the number of Person object records : ";
			cin >> count;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			for (int i = 0; i < count; i++)
			{
			}
			break;
		case 2:
			// to display the array of Person objects into screen
			for (int i = 0; i < count; i++)
			{

			}
			break;
		case 3:
		{
			// to write the array of Person objects into a file
			ofstream fostream(filename, ios::out | ios::in);
			if (fostream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			Person::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{

			}
			fostream.close();
			break;
		}
		case 4:
		{
			// to read the array of Person records from the file
			ifstream fistream(filename, ios::in | ios::binary);
			if (fistream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			Person::InitBuffer(InBuff);
			for (int i = 0; i < count; i++)
			{

			}
			fistream.close();
			break;
		}
		default:
			// others
			exit(0);
			break;
		}
	}
		//*/
	return 1;
}


int main(void)
{
	testFixText();
	testLenText();
	testDelText();
	system("pause");
	return 1;
}
