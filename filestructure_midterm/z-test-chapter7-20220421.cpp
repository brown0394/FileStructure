/*
supply.h에 다음 테이블을 class 로정의한다
spj(sno, pno, jno, city, qty) char sno[3], char pno[3], char jno[3], char city[10], char qty[3]
key는 (sno,pno, jno)로 구성됨
*/
#include "textind.h"
#include "delim.h"
#include "buffile.h"
#include "indfile.h"
#include <iostream>
#include "length.h"
#include "supply.h"
#include <vector>

//*
//Using class Index, the index object should be stored into the RecordFile


template <class object>
void clearVector(vector<object*>& arr) {
	while (!arr.empty()) {
		object* elem = arr.back();
		delete elem;
		arr.pop_back();
	}
}

void inputRecord(vector<Supply*>& stable) {
	//to store a array of Student objects by inputing
	int count = 10;
	Supply spp;

	for (int i = 0; i < count; i++)
	{
		cin >> spp;
		//cout << student;
		stable.push_back(new Supply(spp));			// copy constructor should be implemented			
	}
}

template <class Stable>
void display(vector<Stable*>& stable) {
	for (int i = 0; i < stable.size(); i++)
	{
		cout << *(stable[i]) << endl;// operator<< (operator overloading) should be implemented
	}
}

int writeToFile(char* filename, vector<Supply*>& stable, TextIndexedFile<Supply>& IndFile) {
	int result = IndFile.Create(filename, ios::out);
	cout << "Created file " << endl;
	if (!result)
	{
		cout << "Unable to Create file " << filename << endl;
		return 0;
	}

	for (int i = 0; i < stable.size(); i++)
	{
		IndFile.Append(*stable[i]);
	}
	IndFile.Close();
	return 1;
}

int readFromFile(char* filename, vector<Supply*>& stable, TextIndexedFile<Supply>& IndFile) {
	int result = IndFile.Open(filename, ios::in);
	if (result < 0)
	{
		cout << "Unable to read IndFile " << result << endl;
		return 0;
	}
	IndFile.RewindDataFile();
	clearVector(stable);
	Supply spp;
	while (true) {
		if (IndFile.Read(spp) == -1) break;
		cout << spp;
		stable.push_back(new Supply(spp));
	}
	//IndFile.Close();
	return 1;

}

void indexRead(char* indFileName, vector<Supply*>& stable, TextIndexedFile<Supply>& IndFile) {
	Supply spp;

	int result = IndFile.Open(indFileName, ios::in);
	if (result < 0)
	{
		cout << "Unable to read IndFile \"" << indFileName << "\"" << endl;
		return;
	}
	char key[20];
	cout << "Input key to read : ";
	cin >> key;
	int recaddr = IndFile.GetIndex().Search(key);
	if (result == -1) {
		cout << "key does not exist" << endl;
		return;
	}
	cout << endl << "Searck key::" << key << endl;
	result = IndFile.Read(key, spp);
	if (result == -1) {
		cout << "read failed" << endl;
		//IndFile.Close();
		return;
	}
	stable.push_back(new Supply(spp));
	cout << spp;
	//IndFile.Close();
}

void readInIndexOrder(char* indFileName, vector<Supply*>& stable, TextIndexedFile<Supply>& IndFile) {
	Supply spp;
	int recaddr = -1;
	int result = IndFile.Open(indFileName, ios::in);
	if (result < 0)
	{
		cout << "Unable to read IndFile \"" << indFileName << "\"" << endl;
		return;
	}
	recaddr = IndFile.GetFirstIndex();
	if (recaddr == -1) return;
	result = IndFile.Read(recaddr, spp);
	if (result == -1) {
		cout << "read failed" << endl;
		//IndFile.Close();
		return;
	}
	cout << spp;
	while (true) {
		recaddr = IndFile.GetNextIndex();
		if (recaddr == -1) return;
		result = IndFile.Read(recaddr, spp);
		if (result == -1) {
			cout << "key does not exist" << endl;
			return;
		}
		stable.push_back(new Supply(spp));
		cout << spp;
	}
	//IndFile.Close();
}

int main(void)
{
	char key[20];
	char filename[20];
	int select;
	vector<Supply*> R;

	DelimFieldBuffer Buff;

	TextIndexedFile<Supply> IndFile(Buff, 7, 10);
	cout << "Testing TextIndex Buffer" << endl;

	cout << "Enter the file name:" << flush;
	cin.getline(filename, 19);

	bool wrote = false;

	while (1)
	{
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5. use index file for reading data file, 6. print the records of Supply in key order, 7.Quit => ";
		cin >> select;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch (select) {
		case 1://
		{
			inputRecord(R);
			break;
		}
		case 2://입력된 레코드를 화면에 출력
		{
			// to display the array of objects into screen  
			display(R);
			break;
		}
		case 3: //file 생성 : data file, index file의 생성 - 단한번만 실행
		{
			// to write the array of objects into a file
			if (wrote) break;
			writeToFile(filename, R, IndFile);

			wrote = true;
			break;
		}
		case 4://data file을 순차적 read한다.
		{
			readFromFile(filename, R, IndFile);
			break;
		}

		case 5:
		{
			// read RecordFile by using index file.

			indexRead(filename, R, IndFile);
			break;
		}
		case 6://print the records of Supply in key order
		{
			// read RecordFile by using index file.
			
			/*
			교재 285, 13번 programming and design exercises
			add two methods to class textIndex:
			   1) int FirstRecAddr(); //index table에서 smallest key에 대한  reference address를 return
			   2) int NextRecAddr(); //index table에서 next key에 대한 reference address를 return
			 2개의 함수를 사용하여 키 값 순서로 Supply 레코드들을 출력 
			*/
			readInIndexOrder(filename, R, IndFile);

			break;
		}
		default:
			// others
			clearVector(R);
			exit(0);
			break;
		}
	}
	system("pause");
	return 1;
}
