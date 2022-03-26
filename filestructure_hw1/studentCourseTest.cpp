#include <fstream>
#include <iostream>
#include "student.h"
#include "CourseRegistration.h"

char* getFileName() {
	char *filename = new char [30];
	std::cout << "Enter the file name:" << std::flush;
	std::cin.getline(filename, 19);
	filename[20] = '\0';
	return filename;
}

void writeCourse(std::ofstream& file, CourseRegistration &course) {
	file.write("cr|", 3);
	std::cin >> course;
	file << course;
}

void writeStudent(std::ofstream &file, Student &student) {
	file.write("st|", 3);
	std::cin >> student;
	file << student;
}

void readStudent(std::ifstream &file, Student &student) {
	file >> student;
	std::cout << student;
}

void readCourse(std::ifstream &file, CourseRegistration &course) {
	file >> course;
	std::cout << course;
}

void writeList(Student &student, CourseRegistration &course, char *filename) {
	std::ofstream file(filename, std::ios::out);
	if (file.fail()) {
		std::cout << "File open failed!" << std::endl;
	}
	char input = 0;
	while (1) {
		std::cout << "1 : write Student\n2 : write Course\n3 : quit" << std::endl;
		std::cin >> input; std::cin.seekg(0, std::ios::end); std::cin.clear();
		if (input == '1') {
			writeStudent(file, student);
		}
		else if (input == '2') {
			writeCourse(file, course);
		}
		else break;
	}
}

void readList(Student& student, CourseRegistration& course, char* filename) {
	std::ifstream file(filename, std::ios::in);
	if (file.fail()) {
		std::cout << "File open failed!" << std::endl;
	}
	char recordType[4];
	
	while (1) {
		file.getline(recordType, 4, '|');
		if (file.fail()) break;
		if (strcmp(recordType, "st") == 0) {
			readStudent(file, student);
		}
		else if (strcmp(recordType, "cr") == 0) {
			readCourse(file, course);
		}
	}

}

int main() {
	Student student;
	CourseRegistration course;

	char* filename = getFileName();

	//writeList(student, course, filename);
	readList(student, course, filename);

	delete[] filename;
	system("pause");
	
	return 1;
}