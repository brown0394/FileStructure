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