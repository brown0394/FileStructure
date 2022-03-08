#pragma once
#ifndef STUDENT
#define STUDENT

class Student
{
public:
	// data members
	int Identifier; char* Name; char* Address;
	char* DateOfFirstEnrollment; int NumberOfCreditHours;
	// method
	Student(); // default constructor
	Student(const Student&);
};

#endif