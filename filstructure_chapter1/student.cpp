#include <iostream>
#include <string>
#include "student.h"

Student::Student() :Identifier{ 0 }, Name{ nullptr }, Address{ nullptr }, DateOfFirstEnrollment{ nullptr }, NumberOfCreditHours{ 0 }
{//constructor
}

Student::Student(const Student& student) {
	this->Identifier = student.Identifier;
	this->NumberOfCreditHours = student.NumberOfCreditHours;

	if (student.Address == nullptr) this->Address = nullptr;
	else {
		this->Address = new char[strlen(student.Address) + 1];
		strcpy(this->Address, student.Address);
	}
	if (student.Name == nullptr) this->Name = nullptr;
	else {
		this->Name = new char[strlen(student.Name) + 1];
		strcpy(this->Name, student.Name);
	}
	if (student.DateOfFirstEnrollment == nullptr) this->DateOfFirstEnrollment = nullptr;
	else {
		this->DateOfFirstEnrollment = new char[strlen(student.DateOfFirstEnrollment) + 1];
		strcpy(this->DateOfFirstEnrollment, student.DateOfFirstEnrollment);
	}
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

Student& Student::operator =(const Student&) {

}