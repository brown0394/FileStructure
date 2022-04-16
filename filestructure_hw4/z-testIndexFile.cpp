
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <vector>
#include "iobuffer.h"
#include "tindbuff.h"
#include "textind.h"
#include "indfile.h"
#include "student.h"


template <class object>
void clearVector(vector<object*>& arr) {
	while (!arr.empty()) {
		object* elem = arr.back();
		delete elem;
		arr.pop_back();
	}
}

void inputRecord(vector<Student*>& stable) {
	//to store a array of Student objects by inputing
	int count = 0;
	Student student;
	cout << "the number of object records : ";
	cin >> count;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	for (int i = 0; i < count; i++)
	{
		cin >> student;
		//cout << student;
		stable.push_back(new Student(student));			// copy constructor should be implemented			
	}
}

template <class Stable>
void display(vector<Stable*>& stable) {
	for (int i = 0; i < stable.size(); i++)
	{
		cout << *(stable[i]) << endl;// operator<< (operator overloading) should be implemented
	}
}

int writeToFile(char *filename, vector<Student*>& stable, TextIndexedFile<Student>& IndFile) {
	int result = IndFile.Create(filename, ios::out);
	cout << "Create file " << result << endl;
	if (!result)
	{
		cout << "Unable to Create file " << filename << endl;
		return 0;
	}

	for (int i = 0; i < stable.size(); i++)
	{
		IndFile.Append(*stable[i]);
	}
	IndFile.Close();
	return 1;
}

int readFromFile(char* filename, vector<Student*>& stable, TextIndexedFile<Student>& IndFile) {
	int result = IndFile.Open(filename, ios::in);
	if (result < 0)
	{
		cout << "Unable to read IndFile " << result << endl;
		return 0;
	}
	IndFile.RewindDataFile();
	clearVector(stable);
	Student student;
	while (true) {
		if (IndFile.Read(student) == -1) break;
		stable.push_back(new Student(student));
	}
	return 1;
}

void indexRead(char* indFileName, vector<Student*>& stable, TextIndexedFile<Student>& IndFile) {
	Student student;

	int result = IndFile.Open(indFileName, ios::in);
	if (result < 0)
	{
		cout << "Unable to read IndFile \"" << indFileName << "\"" << endl;
		return;
	}
	char keyid[50];
	char name[35];
	cout << "Input student id to read : ";
	cin >> keyid;
	cout << "Input name of student to read : ";
	cin >> name;
	strcat(keyid, name);
	int recaddr = IndFile.GetIndex().Search(keyid);
	if (result == -1) {
		cout << "key does not exist" << endl;
		return;
	}
	cout << "select " << keyid << " at recaddr " << recaddr << endl;
	result = IndFile.Read(keyid, student);
	cout << "read result: " << result << endl;
	if (result == -1) return;
	stable.push_back(new Student(student));
	cout << student;
}

void makeIndex(char* filename) {
	// make an indexed file from a Student file
	char recFilename[50] = { 0, };
	strcat(recFilename, filename);
	strcat(recFilename, ".dat");
	FixedFieldBuffer Buffer(5); // create a buffer
	Student::InitBuffer(Buffer);
	RecordFile<Student> RecFile(Buffer);
	TextIndexedFile<Student> IndFile(Buffer, 43, 10);
	int result;
	result = IndFile.Create("indfile");
	if (!result)
	{
		cout << "Unable to create indfile " << result << endl;
		return;
	}

	Student student;
	int recaddr = -1;


	result = RecFile.Open(recFilename, ios::in);
	if (!result)
	{
		cout << "Unable to open file " << recFilename << endl;
		return;
	}

	cout << "Read Index from Record File \"" << recFilename << "\"" << endl;
	while (1)
	{
		recaddr = RecFile.Read(student);
		if (recaddr < 0)
			break;
		IndFile.Append(student);
		cout << recaddr << student << endl;
	}
	cout << "Store index table into IndFile" << endl;
	IndFile.Close();
	cout << endl;
	RecFile.Close();
	cout << "Index saved at \"indfile.ind\"" << endl << endl;
}

void TestTextIndexBuffer() {
	char filename[20];
	int select;
	vector<Student*>stable;
	FixedFieldBuffer Buff(5);
	Student::InitBuffer(Buff);
	TextIndexedFile<Student> IndFile(Buff, 43, 10);
	cout << "Testing TextIndex Buffer" << endl;

	cout << "Enter the file name:" << flush;
	cin.getline(filename, 19);

	while (1)
	{
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5. make index file from data file, 6. use index file for reading data file, 7. Quit => ";
		cin >> select;

		switch (select) {
		case 1:
		{
			//to store a array of TextIndex objects by inputing
			inputRecord(stable);
			break;
		}
		case 2:
		{
			// to display the array of TextIndex objects into screen  
			display(stable);
			break;
		}
		case 3:
		{
			// to write the array of TextIndex objects into a file
			Buff.Print(cout);
			if (writeToFile(filename, stable, IndFile)) cout << "Wrote to file succesfully" << endl;
			break;
		}
		case 4:
		{
			if (readFromFile(filename, stable, IndFile)) cout << "Read from file succesfully" << endl;
			break;
		}
		case 5:
		{
			// make an indexed file from a Student file
			makeIndex(filename);

			break;
		}
		case 6:
		{
			// read RecordFile by using index file.
			indexRead(filename, stable, IndFile);
			break;
		}
		default:
			// others
			clearVector(stable);
			exit(0);
			break;
		}
	}
}

/*
Using class Index, the index object should be stored into the RecordFile
*/
int main(int argc, char ** argv)
{
	TestTextIndexBuffer();
	return 0;
}
