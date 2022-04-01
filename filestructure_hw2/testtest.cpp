// test.cc// Copyright 1997, Gregory A. Riccardi
// 4장 과제2: while(1) { } 문을 완성한다.
#include <fstream>
#include <string.h>
#include <iomanip>
#include <vector>
#include "fixtext.h"
#include "lentext.h"
#include "deltext.h"
#include "person.h"
#include "CourseRegistration.h"
#include "student.h"
using namespace std;

int studentOrCourse() {
	int select;
	cout << "\n1. Student, 2. Course => ";
	cin >> select;
	return select;
}

template <class T>
void getRecordInput(vector<T*> &arr) {
	cout << "the number of object records : ";
	int count;
	cin >> count;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	T* object;
	for (int i = 0; i < count; i++)
	{
		object = new T;
		cin >> *object;
		cout << endl;
		arr.push_back(object);
	}
}

template <class T>
void displayRecords(const vector<T*>& arr) {
	for (int i = 0; i < arr.size(); i++)
	{
		cout << *(arr[i]);
	}
}

template <class T1, class T2>
void writeBuffer(ostream& stream, vector<T1*> &arr, T2 &buffer, int type) {// T1 Object Type, T2 Buffer Type
	for (int i = 0; i < arr.size(); i++)
	{
		buffer.Clear();
		if (type == 0)
			buffer.Pack("st");
		else
			buffer.Pack("cr");
		arr[i]->Pack(buffer);
		buffer.Write(stream);
	}
}

template <class T>
void clearVector(vector<T*> &arr) {
	while (!arr.empty()) {
		T* elem = arr.back();
		delete elem;
		arr.pop_back();
	}
}

void readFile(istream& stream, vector<Student*> &starr, FixedTextBuffer& stbuffer, FixedTextBuffer& crbuffer,
	FixedTextBuffer& typebuffer, vector<CourseRegistration*>& crarr) {//read fixed record
	stbuffer.Clear();
	crbuffer.Clear();
	typebuffer.Clear();
	clearVector(starr);
	clearVector(crarr);
	char which[3];
	while (1)
	{
		typebuffer.Read(stream);
		typebuffer.Unpack(which);
		if (which[0] == 0) break;
		if (strcmp(which, "st") == 0) {
			stbuffer.Read(stream);
			Student* st = new Student;
			st->Unpack(stbuffer);
			starr.push_back(st);
		}
		else {
			crbuffer.Read(stream);
			CourseRegistration* cr = new CourseRegistration;
			cr->Unpack(crbuffer);
			crarr.push_back(cr);
		}
	}
}

template <class T>
void readFile(istream& stream, vector<Student*>& starr, T& buffer, vector<CourseRegistration*>& crarr) {
	clearVector(starr);
	clearVector(crarr);
	char which[3];
	while (1)
	{
		buffer.Clear();
		buffer.Read(stream);
		if (!buffer.Unpack(which)) break;
		if (strcmp(which, "st") == 0) {
			Student* st = new Student;
			st->Unpack(buffer);
			starr.push_back(st);
		}
		else {
			CourseRegistration* cr = new CourseRegistration;
			cr->Unpack(buffer);
			crarr.push_back(cr);
		}
	}
}

int testFixText()
{
	vector<Student*> studentStable;
	vector<CourseRegistration*> courseStable;
	FixedTextBuffer stBuff(6);
	FixedTextBuffer stInBuff(5);
	FixedTextBuffer crBuff(5);
	FixedTextBuffer crInBuff(4);
	FixedTextBuffer typeInBuff(1);
	typeInBuff.AddField(2);
	stBuff.AddField(2);
	crBuff.AddField(2);
	Student::InitBuffer(stBuff);
	Student::InitBuffer(stInBuff);
	CourseRegistration::InitBuffer(crBuff);
	CourseRegistration::InitBuffer(crInBuff);

	int breakpoint = 1;

	char filename[20];
	cout << "Enter the file name:" << flush;
	cin.getline(filename, 19);
	

	while (breakpoint)
	{
		int select=0;
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Person objects by inputing
			if (1 == studentOrCourse()) getRecordInput(studentStable);
			else getRecordInput(courseStable);
			break;
		case 2:
			// to display the array of Person objects into screen
			displayRecords(studentStable);
			displayRecords(courseStable);
			break;
		case 3:
		{
			// to write the array of Person objects into a file
			ofstream fostream(filename, ios::out | ios::binary);
			if (fostream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			writeBuffer(fostream, studentStable, stBuff, 0);
			writeBuffer(fostream, courseStable, crBuff, 1);
			fostream.close();
			cout << "File wrote succesfully" << endl;
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
			readFile(fistream, studentStable, stInBuff, crInBuff, typeInBuff, courseStable);
			fistream.close();
			cout << "File Read Completed" << endl;
			break;
		}
		default:
			// others
			clearVector(studentStable);
			clearVector(courseStable);
			breakpoint = 0;
			break;
		}
	}
	return 1;
}

int testLenText()
{
	vector<Student*> studentStable;
	vector<CourseRegistration*> courseStable;
	LengthTextBuffer stBuff;
	LengthTextBuffer crBuff;
	Student::InitBuffer(stBuff);
	CourseRegistration::InitBuffer(crBuff);
	LengthTextBuffer inBuff;
	int breakpoint = 1;

	char filename[20];
	cout << "Enter the file name:" << flush;
	cin.getline(filename, 19);
	while (breakpoint)
	{
		int count;
		int select;
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Person objects by inputing
			if (1 == studentOrCourse()) getRecordInput(studentStable);
			else getRecordInput(courseStable);
			break;
		case 2:
			// to display the array of Person objects into screen
			displayRecords(studentStable);
			displayRecords(courseStable);
			break;
		case 3:
		{
			// to write the array of Person objects into a file
			ofstream fostream(filename, ios::out | ios::binary);
			if (fostream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			writeBuffer(fostream, studentStable, stBuff, 0);
			writeBuffer(fostream, courseStable, crBuff, 1);
			fostream.close();
			cout << "File wrote succesfully" << endl;
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
			readFile(fistream, studentStable, inBuff, courseStable);
			fistream.close();
			cout << "File Read Completed" << endl;
			break;
		}
		default:
			// others
			clearVector(studentStable);
			clearVector(courseStable);
			breakpoint = 0;
			break;
		}
	}
	return 1;
}


int testDelText()
{
	vector<Student*> studentStable;
	vector<CourseRegistration*> courseStable;
	DelimTextBuffer stBuff;
	DelimTextBuffer crBuff;
	DelimTextBuffer inBuff;
	int breakpoint = 1;

	char filename[20];
	cout << "Enter the file name:" << flush;
	cin.getline(filename, 19);
	while (breakpoint)
	{
		int count; int select;
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Person objects by inputing
			if (1 == studentOrCourse()) getRecordInput(studentStable);
			else getRecordInput(courseStable);
			break;
		case 2:
			// to display the array of Person objects into screen
			displayRecords(studentStable);
			displayRecords(courseStable);
			break;
		case 3:
		{
			// to write the array of Person objects into a file
			ofstream fostream(filename, ios::out | ios::binary);
			if (fostream.fail()) {
				cout << "File open failed!" << endl;
				return 0;
			}
			writeBuffer(fostream, studentStable, stBuff, 0);
			writeBuffer(fostream, courseStable, crBuff, 1);
			fostream.close();
			cout << "File wrote succesfully" << endl;
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
			readFile(fistream, studentStable, inBuff, courseStable);
			fistream.close();
			cout << "File Read Completed" << endl;
			break;
		}
		default:
			// others
			clearVector(studentStable);
			clearVector(courseStable);
			breakpoint = 0;
			break;
		}
	}
	return 1;
}

int main(void)
{
	testFixText();
	//testLenText();
	//testDelText();
	system("pause");
	return 1;
}
