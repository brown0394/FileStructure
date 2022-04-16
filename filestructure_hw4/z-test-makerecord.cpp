//makerec.cc
#include "buffile.h"
#include "student.h"
#include "delim.h"
#include <iostream>
#include "recfile.h"
#include <fstream>
#include <iomanip>
#include "iobuffer.h"
#include "textind.h"
#include "tindbuff.h"

//file�� write �� �Ŀ� read�Ͽ� ����ϴ� ���α׷� �ۼ� �ǽ� 
// create two files with the recordings of Figure 7.2
//    the file "record.dat" is created using class BufferFile
//    the file "record2.dat" is created using class RecordFile<Recording>
using namespace std;

int RetrieveRecording(Student& student, char* key,
	TextIndex& RecordingIndex, BufferFile& RecordingFile)
	// read and unpack the recording, return TRUE if succeeds
{
	int result;
	cout << "Retrieve " << key << " at recaddr " << RecordingIndex.Search(key) << endl;
	result = RecordingFile.Read(RecordingIndex.Search(key));
	cout << "read result: " << result << endl;
	if (result == -1) return FALSE;
	result = student.Unpack(RecordingFile.GetBuffer());
	return result;
}

void WriteFile() {
	int recaddr;
	int result;
	DelimFieldBuffer::SetDefaultDelim('|');
	DelimFieldBuffer Buffer;
	Student::InitBuffer(Buffer);
	TextIndex index(10);
	TextIndexBuffer IndexBuffer(43, 10);
	BufferFile IndexedFile(IndexBuffer);

	char* myfile = "record.ind";
	result = IndexedFile.Create(myfile, ios::out);
	cout << "main()::create file " << result << endl;
	if (!result)
	{
		cout << "main()::Unable to create file " << myfile << endl;
		result = IndexedFile.Open(myfile, ios::out);
		cout << "main()::open file " << result << endl;
		if (!result)
		{
			cout << "main()::Unable to open file " << myfile << endl;
			system("pause");

			exit(0);
		}
	}
	RecordFile<Student> RecordedFile(Buffer);
	RecordedFile.Create("recording.dat", ios::out);

	Student* R[10]; //=> 1�忡�� ���� Student record�� �����Ѵ�.
	R[0] = new Student("201824641", "sungchanchoi", "suwon", "2020.03.01", 255);
	R[1] = new Student("201824641", "�ּ���", "������", "2020.03.01", 255);
	R[2] = new Student("20110075", "kimchulsoo", "Sokcho", "2011.03.01", 555);
	R[3] = new Student("202201235", "ö��Ŵ", "�λ�� ������", "2022.09.01", 10);
	R[4] = new Student("20191190", "�迵��", "����Ư����", "2019.02.30", 219);
	R[5] = new Student("19960914", "�ݰ�ȣ", "���ν�", "1996.03.01", 996);
	R[6] = new Student("20020303", "������", "����", "2002.04.05", 10);
	R[7] = new Student("20203214", "GunGangLee", "Incheon", "2020.03.05", 150);
	R[8] = new Student("20131348", "��ȣö", "����", "2013.01.13", 13);
	R[9] = new Student("20060758", "SongGangHo", "Ulsan", "2006.07.08", 777);
	for (int i = 0; i < 10; i++)
	{
		//TextIndex�� ������ index.Insert()
		recaddr = RecordedFile.Write(*R[i]);
		cout << "Recordin2 R[" << i << "] at recaddr " << recaddr << endl;
		index.Insert(R[i]->Key(), recaddr);
		delete R[i];
	}
	IndexBuffer.Pack(index);
	IndexedFile.Write();
	//IndexedFile, RecordFile�� write�� ���ڵ带 �д� �ڵ带 �߰��Ѵ�
	//IndexedFile�� ������ index�� ����
	IndexedFile.Close();
	RecordedFile.Close();
}

void ReadFileWithKey() {
	int recaddr;
	int result;
	DelimFieldBuffer::SetDefaultDelim('|');
	DelimFieldBuffer Buffer;
	Student::InitBuffer(Buffer);
	TextIndex index(10);
	TextIndexBuffer IndexBuffer(43, 10);
	BufferFile IndexedFile(IndexBuffer);
	RecordFile<Student> RecordedFile(Buffer);
	Student student;

	IndexedFile.Open("record.ind", ios::in); //�ٽ� open
	RecordedFile.Open("recording.dat", ios::in);//�ٽ� open
	//char *keyname = "DG18807"; ȭ�鿡�� �Է¹޾Ƽ� �ݺ� �����ϰ� ó��
	//�Էµ� key�� ���� index�� search�� �Ŀ� �ش� ���ڵ带 ����ϴ� ���α׷� - makeind-2.cpp�� �����Ͽ�
	// �� ���α׷��� �����Ͽ� �ϼ�
	result = IndexedFile.Read();
	if (result == -1) return;
	result = IndexBuffer.Unpack(index);
	if (result == -1) return;

	char keyid[50];
	char name[35];

	while (true) {
		cout << "Input student id to read, input q to quit => ";
		cin >> keyid;
		if (strcmp(keyid, "q") == 0) break;
		cout << "Input name of student to read => ";
		cin >> name;
		strcat(keyid, name);
		recaddr = index.Search(keyid);
		if (recaddr == -1) cout << "There are no key named \"" << keyid << "\"" << endl;
		else {
			RecordedFile.Read(student, recaddr);
			cout << student << endl;
		}
	}
	IndexedFile.Close();
	RecordedFile.Close();
}

int main(void)
{
	WriteFile();
	ReadFileWithKey();


	system("pause");
	return 1;
}


