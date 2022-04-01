#pragma once

#ifndef STUDENT
#define STUDENT

#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include "fixtext.h"
#include "lentext.h"
#include "deltext.h"

class Student
{
	// data members
	char* StudentId; char *Name; char *Address;
	char *DateOfFirstEnrollment; int NumberOfCreditHours;
	void studentStrCpy(char* &self, const char* str);

	friend std::ostream& operator << (std::ostream& stream, const Student& student);
	friend std::ofstream& operator << (std::ofstream& stream, const Student& student);
	friend std::istream& operator >> (std::istream& stream, Student& student);
	friend std::ifstream& operator >> (std::ifstream& stream, Student& student);
public:
	// method
	Student(); // default constructor
	Student(const Student&);
	Student(char* , char* , char* , char* , int);
	~Student();

	Student& operator =(const Student&);
	void setId(const char*);
	char *getId();
	void setCredit(int);
	int getCredit();
	void setName(const char*);
	char *getName();
	void setAddress(const char*);
	char *getAddress();
	void setDate(const char*);
	char* getDate();
	void creditIncr();

	void getFixedInput();
	void Clear();
	static int InitBuffer(FixedTextBuffer& Buffer);
	int Pack(FixedTextBuffer&) const;
	int Unpack(FixedTextBuffer&);
	static int InitBuffer(LengthTextBuffer&);
	int Unpack(LengthTextBuffer&);
	int Pack(LengthTextBuffer&) const;
	static int InitBuffer(DelimTextBuffer&);
	int Unpack(DelimTextBuffer&);
	int Pack(DelimTextBuffer&) const;
};

#endif