//testind.cc - TextindexedFile 사용 실습
#include "textind.h"
#include "delim.h"
#include "buffile.h"
#include "recordng.h"
#include "indfile.h"
#include <iostream>

int main (void)
{// first argument is the file name for the data file
	int result;

	TextIndex RecIndex (10);
	DelimFieldBuffer Buffer; // create a buffer
	TextIndexedFile<Recording> IndFile (Buffer, 12, 10);
	//TextIndexedFile<RecType>::TextIndexedFile(IOBuffer & buffer, int keySize, int maxKeys)
	result = IndFile . Create ("indfile", ios::out);
	if (!result) 
	{
		cout<<"Unable to open indfile "<<result<<endl;
		return 0;
	}	
	int recaddr;
	//write records
	Recording* R[10], foundRecord;

	R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
	R[1] = new Recording("RCA", "2626", "Quartet in C Sharp Minor", "Beethoven", "Julliard");
	R[2] = new Recording("WAR", "23699", "Touchstone", "Corea", "Corea");
	R[3] = new Recording("ANG", "3795", "Symphony No. 9", "Beethoven", "Giulini");
	R[4] = new Recording("COL", "38358", "Nebraska", "Springsteen", "Springsteen");
	R[5] = new Recording("DG", "18807", "Symphony No. 9", "Beethoven", "Karajan");
	R[6] = new Recording("MER", "75016", "Coq d'or Suite", "Rimsky-Korsakov", "Leinsdorf");
	R[7] = new Recording("COL", "31809", "Symphony No. 9", "Dvorak", "Bernstein");
	R[8] = new Recording("DG", "139201", "Violin Concerto", "Beethoven", "Ferras");
	R[9] = new Recording("FF", "245", "Good News", "Sweet Honey in the Rock", "Sweet Honey in the Rock");
	for (int i = 0; i < 10; i++)
	{
		recaddr = IndFile.Append(*R[i]);
		cout << "IndFile R[" << i << "] at recaddr " << recaddr << endl;
	}

	char* searchKey = "DG139201";
	IndFile.Read(searchKey, foundRecord);
	foundRecord.Print(cout);
	IndFile.Close();
	system("pause");
	return 1;
}

