#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include "CourseRegistration.h"

CourseRegistration::CourseRegistration() :numberOfCreditHours{ 0 }, grade{0.0f}
{
	this->courseId = new char[10];
	this->courseId[0] = '\0';
	this->studentId = new char[10];
	this->studentId[0] = '\0';
}

void CourseRegistration::courseStrCpy(char*& self, const char* str) {
	if (strlen(self) < strlen(str)) {
		delete[] self;
		self = new char[strlen(str) + 1];
		strcpy(self, str);
	}
	else {
		strcpy(self, str);
	}
}

CourseRegistration::CourseRegistration(const CourseRegistration& course) {
	this->grade = course.grade;
	this->numberOfCreditHours = course.numberOfCreditHours;

	this->studentId = new char[strlen(course.studentId) + 1];
	strcpy(this->studentId, course.studentId);
	this->courseId = new char[strlen(course.courseId) + 1];
	strcpy(this->courseId, course.courseId);
}

CourseRegistration::CourseRegistration(char* courseId, char* studentId, int credit, float grade) {
	this->numberOfCreditHours = credit;
	this->grade = grade;

	this->studentId = new char[strlen(studentId) + 1];
	strcpy(this->studentId, studentId);
	this->courseId = new char[strlen(courseId) + 1];
	strcpy(this->courseId, courseId);

}
CourseRegistration::~CourseRegistration() {
	delete[] studentId;
	delete[] courseId;
}

CourseRegistration& CourseRegistration::operator =(const CourseRegistration& course) {
	this->numberOfCreditHours = course.numberOfCreditHours;
	this->grade = course.grade;

	courseStrCpy(studentId, course.studentId);
	courseStrCpy(courseId, course.studentId);
	return *this;
}

void CourseRegistration::setStudentId(const char* id) {
	courseStrCpy(studentId, id);
}
char* CourseRegistration::getStudentId() {
	return this->studentId;
}
void CourseRegistration::setCredit(int credit) {
	this->numberOfCreditHours = credit;
}
int CourseRegistration::getCredit() {
	return this->numberOfCreditHours;
}
void CourseRegistration::setCourseId(const char* id) {
	courseStrCpy(courseId, id);
}
char* CourseRegistration::getCourseId() {
	return this->courseId;
}
void CourseRegistration::setGrade(float grade) {
	this->grade = grade;
}
float CourseRegistration::getGrade() {
	return this->grade;
}


std::ostream& operator << (std::ostream& stream, const CourseRegistration& course) {
	stream << "Course Id : " << course.studentId << "\nStudent Id : " << course.studentId <<
		"\nNumber of Credit Hours : " << course.numberOfCreditHours << "\nGrade : " << course.grade
		<< "\n\n";
	return stream;
}

/*
std::ofstream& operator << (std::ofstream& stream, const CourseRegistration& course) {//delimiter
	stream << course.courseId << '|' << course.studentId <<
		'|' << course.numberOfCreditHours << '|' << course.grade << '|' ;
	return stream;
}

std::ifstream& operator >> (std::ifstream& stream, CourseRegistration& course)
{
	char delim = '|';
	stream.getline(course.courseId, 30, delim);
	if (strlen(course.courseId) == 0) return stream;
	stream.getline(course.studentId, 30, delim);
	char temp[30];
	stream.getline(temp, 30, delim);
	course.setCredit(atoi(temp));
	stream.getline(temp, 30, delim);
	course.setGrade(atof(temp));
	return stream;
}*/

const int MaxBufferSize = 200;

std::ofstream& operator << (std::ofstream& stream, const CourseRegistration& course) {//vardel
	char buffer[MaxBufferSize];
	strcpy(buffer, course.courseId); strcat(buffer, "|");
	strcat(buffer, course.studentId); strcat(buffer, "|");
	char temp[10];
	sprintf(temp, "%d", course.numberOfCreditHours);
	strcat(buffer, temp);  strcat(buffer, "|");
	sprintf(temp, "%.2f", course.grade);
	strcat(buffer, temp);  strcat(buffer, "|");

	short length = strlen(buffer);
	stream.write((char*)&length, sizeof(length)); // write length
	stream.write(&buffer[0], length);

	return stream;
}

void setStudentStream(std::istream& stream, CourseRegistration& course)
{
	char delim = '|';
	char buffer[31];
	stream.getline(buffer, 30, delim);
	course.setCourseId(buffer);
	stream.getline(buffer, 30, delim);
	course.setStudentId(buffer);
	stream.getline(buffer, 30, delim);
	course.setCredit(atoi(buffer));
	stream.getline(buffer, 30, delim);
	course.setGrade(atof(buffer));
}

std::ifstream& operator >> (std::ifstream& stream, CourseRegistration& course)
{
	short length;
	//istream& read(const char*, streamsize);
	stream.read((char*)&length, sizeof(length));

	//if (stream.fail()) { course.courseId[0] = 0; return stream; }
	char* buffer = new char[length + 1];
	stream.read(buffer, length);
	buffer[length] = 0; // terminate buffer with null


	std::istrstream strbuff(buffer);
	setStudentStream(strbuff, course);
	//strbuff >> student;
	delete[] buffer;
	return stream;
}

void checkValid(char *str) {
	for (char* c = str; *c != '\0'; ++c) {
		if (!(isdigit(*c))) {
			if ((*c) == '.') {
				continue;
			}
			str[0] = '0'; str[1] = '\0'; break;
		}
	}
}

std::istream& operator >> (std::istream& stream, CourseRegistration& course) {
	char buffer[31];
	std::cout << "Enter course id: " << std::flush;
	stream.getline(buffer, 30);//, or <cr> to end: " << std::flush;
	
	course.setCourseId(buffer);
	//if (strlen(course.courseId) == 0) return stream;
	std::cout << "Enter student id: " << std::flush; stream.getline(buffer, 30);
	course.setStudentId(buffer);
	std::cout << "Enter number of credit hours: " << std::flush; stream.getline(buffer, 30);
	checkValid(buffer);
	course.setCredit(atoi(buffer));
	std::cout << "Enter course grade: " << std::flush; stream.getline(buffer, 30);
	checkValid(buffer);
	course.setGrade(atof(buffer));
	return stream;
}