//학번: 201824641
//이름: 최성찬
//github id: brown0394
#include <vector>
#include "CourseRegistration.h"
#include "student.h"
#include "buffile.h"
#include "length.h"

template <class object>
void clearVector(vector<object*>& arr) {
	while (!arr.empty()) {
		object* elem = arr.back();
		delete elem;
		arr.pop_back();
	}
}

template <class Stable>
void inputRecord(vector<Stable*>& stable) {
	//to store a array of Student objects by inputing
	int count = 0;
	Stable object;
	cout << "the number of object records : ";
	cin >> count;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	for (int i = 0; i < count; i++)
	{
		cin >> object;
		//cout << student;
		stable.push_back(new Stable(object));			// copy constructor should be implemented			
	}
}

template <class Stable>
void display(vector<Stable*>& stable) {
	for (int i = 0; i < stable.size(); i++)
	{
		cout << *(stable[i]) << endl;// operator<< (operator overloading) should be implemented
	}
}

template <class Stable>
void writeFile(vector<Stable*>& stable, FixedFieldBuffer& Buff, char* filename, BufferFile& TestOut, int type) {
	// to write the array of Student objects into a file
	int recaddr;

	FixedFieldBuffer typeBuff(1);
	typeBuff.AddField(2);
	char classtype[10];
	if (type == 1) {
		typeBuff.Clear();
		typeBuff.Pack("st");
		sprintf(classtype, "%s", "Student");
		typeBuff.Write(TestOut.GetFile());
	}
	else {
		typeBuff.Clear();
		typeBuff.Pack("cr");
		sprintf(classtype, "%s", "Course");
		typeBuff.Write(TestOut.GetFile());
	}

	for (int i = 0; i < stable.size(); i++)
	{
		int recaddr;
		cout << *(stable[i]) << endl;
		Buff.Clear();
		stable[i]->Pack(Buff);
		recaddr = TestOut.Write();

		cout << classtype << " R[" << i << "] at recaddr " << recaddr << endl;
	}
}

template <class Stable, class Io>
void writeFile(vector<Stable*>& stable, Io &Buff, char* filename, BufferFile &TestOut, int type) {
	// to write the array of Student objects into a file
	int recaddr;

	char classtype[10];
	for (int i = 0; i < stable.size(); i++)
	{
		int recaddr;
		cout << *(stable[i]) << endl;
		if (type == 1) {
			Buff.Clear();
			Buff.Pack("st");
			sprintf(classtype, "%s", "Student");
			TestOut.Write();
		}
		else {
			Buff.Clear();
			Buff.Pack("cr");
			sprintf(classtype, "%s", "Course");
			TestOut.Write();
		}
		Buff.Clear();
		stable[i]->Pack(Buff);
		recaddr = TestOut.Write();

		cout << classtype << " R[" << i << "] at recaddr " << recaddr << endl;
	}
}

template <class Io>
void readFile(vector<Student*>& stStable, vector<CourseRegistration*>& crStable, Io &Buff, char* filename) {
	// to read the array of Student records from the file
	int recaddr;
	clearVector(stStable);
	clearVector(crStable);

	BufferFile TestIn(Buff);
	TestIn.Open(filename, ios::in);
	char which[3]{'\0'};
	int stidx = 0;
	int cridx = 0;
	while (true)
	{
		recaddr = TestIn.Read();
		if (recaddr == -1) break;
		Buff.Unpack(which);
		if (strcmp(which, "st") == 0) {
			recaddr = TestIn.Read();
			stStable.push_back(new Student());
			stStable[stidx]->Unpack(Buff);
			cout << *(stStable[stidx++]) << endl;
		}
		else {
			recaddr = TestIn.Read();
			crStable.push_back(new CourseRegistration());
			crStable[cridx]->Unpack(Buff);
			cout << *(crStable[cridx++]) << endl;
		}

	}
	//if (result != -1) cout << "Read past end of file! Error." << endl;
	//else cout << "Read past end of file failed! Correct." << endl;

}

template <class Stable, class Io>
void readFile(vector<Stable*>& stable, Io& Buff, char* filename, int type) {
	// to read the array of Student records from the file
	int recaddr;
	clearVector(stable);

	BufferFile TestIn(Buff);
	TestIn.Open(filename, ios::in);
	FixedFieldBuffer typeBuff(1);
	typeBuff.AddField(2);
	typeBuff.Read(TestIn.GetFile());
	char which[3]{ '\0' };
	typeBuff.Unpack(which);
	if (strcmp(which, "st") == 0 && type != 1) {
		cout << "Read this File with Student mode" << endl;
		return;
	}
	else if (strcmp(which, "cr") == 0 && type != 2) {
		cout << "Read this File with Course mode" << endl;
		return;
	}
	else if (strcmp(which, "") == 0) {
		cout << "Chose wrong  mode. Cannot Read File" << endl;
		return;
	}

	int idx = 0;
	while (true)
	{
		recaddr = TestIn.Read();
		if (recaddr == -1) break;
		stable.push_back(new Stable());
		stable[idx]->Unpack(Buff);
		cout << *(stable[idx++]) << endl;
	}
	//if (result != -1) cout << "Read past end of file! Error." << endl;
	//else cout << "Read past end of file failed! Correct." << endl;

}

int studentOrCourse() {
	int select;
	cout << "\n1. Student, 2. Course => ";
	cin >> select;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return select;
}

template <class Buffer>
void testBuff(Buffer& Buff) {
	int select = 0;
	char filename[20];
	vector<Student*> stStable;
	vector<CourseRegistration*> crStable;
	cout << "Enter the file name:" << flush;
	cin.getline(filename, 19);

	while (1)
	{
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Student objects by inputing
			if (1 == studentOrCourse()) inputRecord(stStable);
			else inputRecord(crStable);
			break;
		case 2:
			// to display the array of Student objects into screen  
			display(stStable);
			display(crStable);
			break;
		case 3:
		{
			int result;
			BufferFile TestOut(Buff);
			result = TestOut.Create(filename, ios::in | ios::out);
			cout << "create file " << filename << endl;
			if (!result)
			{
				cout << "Unable to create file " << filename << endl;
			}
			writeFile(stStable, Buff, filename, TestOut, 1);
			writeFile(crStable, Buff, filename, TestOut, 2);
			break;
		}
		case 4:
		{
			readFile(stStable, crStable, Buff, filename);
			break;
		}
		default:
			// others
			clearVector(stStable);
			clearVector(crStable);
			exit(0);
			break;
		}
	}
}

template <class Stable>
void testBuff(FixedFieldBuffer& Buff, vector<Stable*> &stable, int type) {
	int select = 0;
	char filename[20];
	cout << "Enter the file name:" << flush;
	cin.getline(filename, 19);

	while (1)
	{
		cout << "\nSelect command 1: record input, 2. display, 3. write to file, 4. read from file, 5: Quit => ";
		cin >> select;

		switch (select) {
		case 1:
			//to store a array of Student objects by inputing
			inputRecord(stable);
			break;
		case 2:
			// to display the array of Student objects into screen  
			display(stable);
			break;
		case 3:
		{
			int result;
			BufferFile TestOut(Buff);
			result = TestOut.Create(filename, ios::in | ios::out);
			cout << "create file " << filename << endl;
			if (!result)
			{
				cout << "Unable to create file " << filename << endl;
			}
			writeFile(stable, Buff, filename, TestOut, type);
			break;
		}
		case 4:
		{
			readFile(stable, Buff, filename, type);
			break;
		}
		default:
			// others
			clearVector(stable);
			exit(0);
			break;
		}
	}
}

int main(int argc, char ** argv)
{
	cout << "Select buffer type 1 : DelimFieldBuffer, 2: FixedTextBuffer, 3: LengthTextBuffer =>";
	int select;
	cin >> select;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	switch (select) {
		case 1: {
			cout << "\nTesting DelimFieldBuffer" << endl;
			DelimFieldBuffer dBuff;
			testBuff(dBuff);
			break;
		}
		case 2: {
			cout << "\nTesting FixedTextBuffer" << endl;
			if (1 == studentOrCourse()) {
				vector<Student*> st;
				FixedFieldBuffer stBuff(5);
				Student::InitBuffer(stBuff);
				testBuff(stBuff, st, 1);
			}
			else {
				vector<CourseRegistration*> cr;
				FixedFieldBuffer crBuff(4);
				CourseRegistration::InitBuffer(crBuff);
				testBuff(crBuff, cr, 2);
			}
			break;
		}
		case 3: {
			cout << "\nTesting LengthTextBuffer" << endl;
			LengthFieldBuffer lBuff;
			testBuff(lBuff);
			break;
		}
	}

	return 1;
}
