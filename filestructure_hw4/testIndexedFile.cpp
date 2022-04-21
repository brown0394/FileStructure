//testind.cc - TextindexedFile 사용 실습
#include "textind.h"
#include "delim.h"
#include "buffile.h"
#include "student.h"
#include "indfile.h"
#include <iostream>

void writeRecord(TextIndexedFile<Student> &IndFile) {
	int result = IndFile.Create("indfile", ios::out);
	if (!result)
	{
		cout << "Unable to open indfile " << result << endl;
		exit(0);
	}
	int recaddr;
	//write records
	Student* R[10];
	for (int i = 0; i < 10; i++)
	{
		R[i] = new Student;
		cin >> *R[i];
		recaddr = IndFile.Append(*R[i]);
		cout << "IndFile R[" << i << "] at recaddr " << recaddr << endl;
	}
	cout << "Record write completed\n" << endl;
}

void readRecord(TextIndexedFile<Student>& IndFile) {
	int result = IndFile.Open("indfile", ios::in);
	if (result < 0)
	{
		cout << "Unable to read IndFile " << result << endl;
		exit(0);
	}
	IndFile.RewindDataFile();
	Student student;
	while (true) {
		if (IndFile.Read(student) == -1) break;
		cout << student << endl;
	}
	cout << "Record read completed\n" << endl;
}

void readWithIndex(TextIndexedFile<Student>& IndFile) {
	int recaddr = -1;
	Student student;
	int result = IndFile.Open("indfile", ios::in);
	if (result < 0)
	{
		cout << "Unable to read IndFile " << result << endl;
		exit(0);
	}
	char keyid[50];
	char name[35];
	while (true) {
		cout << "Input student id to read, q to quit : ";
		cin >> keyid;
		if (0 == strcmp(keyid, "q")) break;
		cout << "Input name of student to read : ";
		cin >> name;
		strcat(keyid, name);
		recaddr = IndFile.GetIndex().Search(keyid);
		if (recaddr == -1) cout << "There are no key named " << keyid << endl;
		else {
			IndFile.Read(keyid, student);
			cout << student;
		}
	}
	cout << "Quit key input recognized\n" << endl;
}

int main (void)
{// first argument is the file name for the data file
	int result;

	//TextIndex RecIndex (10);
	DelimFieldBuffer Buffer; // create a buffer
	TextIndexedFile<Student> IndFile (Buffer, 12, 10);
	//TextIndexedFile<RecType>::TextIndexedFile(IOBuffer & buffer, int keySize, int maxKeys)
	writeRecord(IndFile);
	readRecord(IndFile);
	readWithIndex(IndFile);
	IndFile.Close();
	system("pause");
	return 1;
}

