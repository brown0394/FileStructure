#include "student.h"

Student::Student() :Identifier{ 0 }, NumberOfCreditHours{ 0 }
{
	this->Address = new char[10];
	this->DateOfFirstEnrollment = new char[10];
	this->Name = new char[10];
}

void Student::studentStrCpy(attributeStr att, const char* str) {
	char *self = nullptr;
	switch (att) {
	case NAME: { self = this->Name; break; }
	case ADDRESS: {self = this->Address; break; }
	case DATE: { self = this->DateOfFirstEnrollment; break; }
	default: { std::cout << "Wrong parameter used\n"; return; }
	}

	if (strlen(self) > strlen(str)) {
		delete[] self;
		self = new char[strlen(str) + 1];
		strcpy(self, str);
	}
	else {
		strcpy(self, str);
	}

	switch (att) {
	case NAME: { this->Name = self; break; }
	case ADDRESS: {this->Address = self; break; }
	case DATE: { this->DateOfFirstEnrollment = self; break; }
	}
}

Student::Student(const Student& student) {
	this->Identifier = student.Identifier;
	this->NumberOfCreditHours = student.NumberOfCreditHours;

	this->Address = new char[strlen(student.Address) + 1];
	strcpy(this->Address, student.Address);
	this->Name = new char[strlen(student.Name) + 1];
	strcpy(this->Name, student.Name);
	this->DateOfFirstEnrollment = new char[strlen(student.DateOfFirstEnrollment) + 1];
	strcpy(this->DateOfFirstEnrollment, student.DateOfFirstEnrollment);
}

Student::Student(int id, char* name, char* address, char* date, int creditHour) {
	this->Identifier = id;
	this->NumberOfCreditHours = creditHour;

	this->Address = new char[strlen(address) + 1];
	strcpy(this->Address, address);

	this->Name = new char[strlen(name) + 1];
	strcpy(this->Name, name);

	this->DateOfFirstEnrollment = new char[strlen(date) + 1];
	strcpy(this->DateOfFirstEnrollment, date);
}
Student::~Student() {
	delete[] Name;
	delete[] Address;
	delete[] DateOfFirstEnrollment;
}

Student& Student::operator =(const Student& student) {
	this->Identifier = student.Identifier;
	this->NumberOfCreditHours = student.NumberOfCreditHours;

	studentStrCpy(ADDRESS, student.Address);
	studentStrCpy(NAME, student.Name);
	studentStrCpy(DATE, student.DateOfFirstEnrollment);
	return *this;
}

std::ostream& operator << (std::ostream& stream, const Student& student) {
	stream << "Student ID : " << student.Identifier << "\nName : " << student.Name <<
		"\nAddress : " << student.Address << "\nDate of first enrollment : " << student.DateOfFirstEnrollment
		<< "\nNumber of credit hours : " << student.NumberOfCreditHours << "\n\n";
	return stream;
}

void Student::setId(int id) {
	this->Identifier = id;
}
int Student::getId() {
	return this->Identifier;
}
void Student::setCredit(int credit) {
	this->NumberOfCreditHours = credit;
}
int Student::getCredit() {
	return this->NumberOfCreditHours;
}
void Student::setName(const char *name) {
	studentStrCpy(NAME, name);
}
char* Student::getName() {
	return this->Name;
}
void Student::setAddress(const char *address) {
	studentStrCpy(ADDRESS, address);
}
char* Student::getAddress() {
	return this->Address;
}
void Student::setDate(const char *date) {
	studentStrCpy(DATE, date);
}
char* Student::getDate() {
	return this->DateOfFirstEnrollment;
}