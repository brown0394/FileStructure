#pragma once

#include <iostream>
#include <string>

#ifndef STUDENT
#define STUDENT

class Student
{
	// data members
	int Identifier; char *Name; char *Address;
	char *DateOfFirstEnrollment; int NumberOfCreditHours;
	enum attributeStr{NAME, ADDRESS, DATE};
	void studentStrCpy(attributeStr att, const char* str);

	friend std::ostream& operator << (std::ostream& stream, const Student& student);
public:
	// method
	Student(); // default constructor
	Student(const Student&);
	Student(int , char* , char* , char* , int);
	~Student();

	Student& operator =(const Student&);
	void setId(int);
	int getId();
	void setCredit(int);
	int getCredit();
	void setName(const char*);
	char *getName();
	void setAddress(const char*);
	char *getAddress();
	void setDate(const char*);
	char* getDate();
};

#endif