#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include "student.h"

Student::Student() :NumberOfCreditHours{ 0 }
{
	this->StudentId = new char[10];
	this->StudentId[0] = '\0';
	this->Address = new char[10];
	this->Address[0] = '\0';
	this->DateOfFirstEnrollment = new char[10];
	this->DateOfFirstEnrollment[0] = '\0';
	this->Name = new char[10];
	this->Name[0] = '\0';
}

void Student::studentStrCpy(char *&self, const char* str) {
	if (strlen(self) < strlen(str)) {
		delete[] self;
		self = new char[strlen(str) + 1];
		strcpy(self, str);
	}
	else {
		strcpy(self, str);
	}
}

Student::Student(const Student& student) {
	this->StudentId = student.StudentId;
	this->NumberOfCreditHours = student.NumberOfCreditHours;

	this->StudentId = new char[strlen(student.StudentId) + 1];
	strcpy(this->StudentId, student.StudentId);
	this->Address = new char[strlen(student.Address) + 1];
	strcpy(this->Address, student.Address);
	this->Name = new char[strlen(student.Name) + 1];
	strcpy(this->Name, student.Name);
	this->DateOfFirstEnrollment = new char[strlen(student.DateOfFirstEnrollment) + 1];
	strcpy(this->DateOfFirstEnrollment, student.DateOfFirstEnrollment);
}

Student::Student(char* id, char* name, char* address, char* date, int creditHour) {
	this->NumberOfCreditHours = creditHour;

	this->StudentId = new char[strlen(id) + 1];
	strcpy(this->StudentId, id);

	this->Address = new char[strlen(address) + 1];
	strcpy(this->Address, address);

	this->Name = new char[strlen(name) + 1];
	strcpy(this->Name, name);

	this->DateOfFirstEnrollment = new char[strlen(date) + 1];
	strcpy(this->DateOfFirstEnrollment, date);
}
Student::~Student() {
	delete[] StudentId;
	delete[] Name;
	delete[] Address;
	delete[] DateOfFirstEnrollment;
}

Student& Student::operator =(const Student& student) {
	this->NumberOfCreditHours = student.NumberOfCreditHours;

	studentStrCpy(StudentId, student.StudentId);
	studentStrCpy(Address, student.Address);
	studentStrCpy(Name, student.Name);
	studentStrCpy(DateOfFirstEnrollment, student.DateOfFirstEnrollment);
	return *this;
}

void Student::setId(const char * id) {
	studentStrCpy(StudentId, id);
}
char* Student::getId() {
	return this->StudentId;
}
void Student::setCredit(int credit) {
	this->NumberOfCreditHours = credit;
}
int Student::getCredit() {
	return this->NumberOfCreditHours;
}
void Student::setName(const char *name) {
	studentStrCpy(Name, name);
}
char* Student::getName() {
	return this->Name;
}
void Student::setAddress(const char *address) {
	studentStrCpy(Address, address);
}
char* Student::getAddress() {
	return this->Address;
}
void Student::setDate(const char *date) {
	studentStrCpy(DateOfFirstEnrollment, date);
}
char* Student::getDate() {
	return this->DateOfFirstEnrollment;
}

std::ostream& operator << (std::ostream& stream, const Student& student) {
	stream << "Student Id : " << student.StudentId << "\nStudent Name : " << student.Name <<
		"\nAddress : " << student.Address << "\nDate of Enrollment : " << student.DateOfFirstEnrollment
		<< "\nNumber of Credit Hours : " << student.NumberOfCreditHours << "\n\n";
	return stream;
}

/*
std::ofstream& operator << (std::ofstream& stream, const Student& student) {//delimiter
	stream << student.StudentId << '|' << student.Name <<
		'|' << student.Address << '|' << student.DateOfFirstEnrollment
		<< '|' << student.NumberOfCreditHours << '|';
	return stream;
}*/
/*
std::ifstream& operator >> (std::ifstream& stream, Student& student)
{
	char delim = '|';
	stream.getline(student.StudentId, 30, delim);
	if (strlen(student.StudentId) == 0) return stream;
	stream.getline(student.Name, 30, delim);
	stream.getline(student.Address, 30, delim);
	stream.getline(student.DateOfFirstEnrollment, 30, delim);
	char credit[15];
	stream.getline(credit, 15, delim);
	student.NumberOfCreditHours = atoi(credit);

	return stream;
}*/

const int MaxBufferSize = 200;

std::ofstream& operator << (std::ofstream& stream, const Student& student) {//vardel
	char buffer[MaxBufferSize];
	strcpy(buffer, student.StudentId); strcat(buffer, "|");
	strcat(buffer, student.Name); strcat(buffer, "|");
	strcat(buffer, student.Address);  strcat(buffer, "|");
	strcat(buffer, student.DateOfFirstEnrollment);  strcat(buffer, "|");
	char credit[10];
	sprintf(credit, "%d", student.NumberOfCreditHours);
	strcat(buffer, credit);  strcat(buffer, "|");
	
	short length = strlen(buffer);
	stream.write((char*)&length, sizeof(length)); // write length
	stream.write(&buffer[0], length);

	return stream;
}

void setStudentStream (std::istream& stream, Student& student)
{
	char delim = '|';
	char buffer[31];
	stream.getline(buffer, 30, delim);
	student.setId(buffer);
	stream.getline(buffer, 30, delim);
	student.setName(buffer);
	stream.getline(buffer, 30, delim);
	student.setAddress(buffer);
	stream.getline(buffer, 30, delim);
	student.setDate(buffer);
	stream.getline(buffer, 30, delim);
	student.setCredit(atoi(buffer));
}

std::ifstream& operator >> (std::ifstream& stream, Student& student)
{
	short length;
	//istream& read(const char*, streamsize);
	stream.read((char*)&length, sizeof(length)); 

	//if (stream.fail()) { student.StudentId[0] = 0; return stream; }
	char* buffer = new char[length + 1];
	stream.read(buffer, length);
	buffer[length] = 0; // terminate buffer with null

	
	std::istrstream strbuff(buffer);
	setStudentStream(strbuff, student);
	//strbuff >> student;
	delete[] buffer;
	return stream;
}

std::istream& operator >> (std::istream& stream, Student& student) {
	char buffer[31];
	std::cout << "Enter student id: " << std::flush; //, or <cr> to end: " << std::flush;
	stream.getline(buffer, 30);
	student.setId(buffer);
	//if (strlen(student.StudentId) == 0) return stream;
	std::cout << "Enter name: " << std::flush; stream.getline(buffer, 30);
	student.setName(buffer);
	std::cout << "Enter address: " << std::flush; stream.getline(buffer, 30);
	student.setAddress(buffer);
	std::cout << "Enter date of frist enrollment: " << std::flush; stream.getline(buffer, 30);
	student.setDate(buffer);

	std::cout << "Enter number of credit hours: " << std::flush; stream.getline(buffer, 30);
	for (char c : buffer) {
		if (c == '\0') break;
		if (!(isdigit(c))) {
			buffer[0] = '0'; buffer[1] = '\0'; break;
		}
	}
	student.setCredit(atoi(buffer));
	return stream;
}

void Student::creditIncr() {
	++(this->NumberOfCreditHours);
}