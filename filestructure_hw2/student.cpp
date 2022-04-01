#include "student.h"

Student::Student() :NumberOfCreditHours{ 0 }
{
	this->StudentId = new char[10];
	this->StudentId[0] = '\0';
	this->Address = new char[20];
	this->Address[0] = '\0';
	this->DateOfFirstEnrollment = new char[11];
	this->DateOfFirstEnrollment[0] = '\0';
	this->Name = new char[35];
	this->Name[0] = '\0';
}

void Student::studentStrCpy(char *&self, const char* str) {
	if (strlen(self) < strlen(str)) {
		delete[] self;
		self = new char[strlen(str) + 1];
		strcpy(self, str);
	}
	else {
		strcpy(self, str);
	}
}

Student::Student(const Student& student) {
	this->StudentId = student.StudentId;
	this->NumberOfCreditHours = student.NumberOfCreditHours;

	this->StudentId = new char[strlen(student.StudentId) + 1];
	strcpy(this->StudentId, student.StudentId);
	this->Address = new char[strlen(student.Address) + 1];
	strcpy(this->Address, student.Address);
	this->Name = new char[strlen(student.Name) + 1];
	strcpy(this->Name, student.Name);
	this->DateOfFirstEnrollment = new char[strlen(student.DateOfFirstEnrollment) + 1];
	strcpy(this->DateOfFirstEnrollment, student.DateOfFirstEnrollment);
}

Student::Student(char* id, char* name, char* address, char* date, int creditHour) {
	this->NumberOfCreditHours = creditHour;

	this->StudentId = new char[strlen(id) + 1];
	strcpy(this->StudentId, id);

	this->Address = new char[strlen(address) + 1];
	strcpy(this->Address, address);

	this->Name = new char[strlen(name) + 1];
	strcpy(this->Name, name);

	this->DateOfFirstEnrollment = new char[strlen(date) + 1];
	strcpy(this->DateOfFirstEnrollment, date);
}
Student::~Student() {
	delete[] StudentId;
	delete[] Name;
	delete[] Address;
	delete[] DateOfFirstEnrollment;
}

Student& Student::operator =(const Student& student) {
	this->NumberOfCreditHours = student.NumberOfCreditHours;

	studentStrCpy(StudentId, student.StudentId);
	studentStrCpy(Address, student.Address);
	studentStrCpy(Name, student.Name);
	studentStrCpy(DateOfFirstEnrollment, student.DateOfFirstEnrollment);
	return *this;
}

void Student::setId(const char * id) {
	studentStrCpy(StudentId, id);
}
char* Student::getId() {
	return this->StudentId;
}
void Student::setCredit(int credit) {
	this->NumberOfCreditHours = credit;
}
int Student::getCredit() {
	return this->NumberOfCreditHours;
}
void Student::setName(const char *name) {
	studentStrCpy(Name, name);
}
char* Student::getName() {
	return this->Name;
}
void Student::setAddress(const char *address) {
	studentStrCpy(Address, address);
}
char* Student::getAddress() {
	return this->Address;
}
void Student::setDate(const char *date) {
	studentStrCpy(DateOfFirstEnrollment, date);
}
char* Student::getDate() {
	return this->DateOfFirstEnrollment;
}

std::ostream& operator << (std::ostream& stream, const Student& student) {
	stream << "Student Id : " << student.StudentId << "\nStudent Name : " << student.Name <<
		"\nAddress : " << student.Address << "\nDate of Enrollment : " << student.DateOfFirstEnrollment
		<< "\nNumber of Credit Hours : " << student.NumberOfCreditHours << "\n\n";
	return stream;
}

/*
std::ofstream& operator << (std::ofstream& stream, const Student& student) {//delimiter
	stream << student.StudentId << '|' << student.Name <<
		'|' << student.Address << '|' << student.DateOfFirstEnrollment
		<< '|' << student.NumberOfCreditHours << '|';
	return stream;
}*/
/*
std::ifstream& operator >> (std::ifstream& stream, Student& student)
{
	char delim = '|';
	stream.getline(student.StudentId, 30, delim);
	if (strlen(student.StudentId) == 0) return stream;
	stream.getline(student.Name, 30, delim);
	stream.getline(student.Address, 30, delim);
	stream.getline(student.DateOfFirstEnrollment, 30, delim);
	char credit[15];
	stream.getline(credit, 15, delim);
	student.NumberOfCreditHours = atoi(credit);

	return stream;
}*/

const int MaxBufferSize = 200;

std::ofstream& operator << (std::ofstream& stream, const Student& student) {//vardel
	char buffer[MaxBufferSize];
	strcpy(buffer, student.StudentId); strcat(buffer, "|");
	strcat(buffer, student.Name); strcat(buffer, "|");
	strcat(buffer, student.Address);  strcat(buffer, "|");
	strcat(buffer, student.DateOfFirstEnrollment);  strcat(buffer, "|");
	char credit[10];
	sprintf(credit, "%d", student.NumberOfCreditHours);
	strcat(buffer, credit);  strcat(buffer, "|");
	
	short length = strlen(buffer);
	stream.write((char*)&length, sizeof(length)); // write length
	stream.write(&buffer[0], length);

	return stream;
}

void setStudentStream (std::istream& stream, Student& student)
{
	char delim = '|';
	char buffer[31];
	stream.getline(buffer, 30, delim);
	student.setId(buffer);
	stream.getline(buffer, 30, delim);
	student.setName(buffer);
	stream.getline(buffer, 30, delim);
	student.setAddress(buffer);
	stream.getline(buffer, 30, delim);
	student.setDate(buffer);
	stream.getline(buffer, 30, delim);
	student.setCredit(atoi(buffer));
}

std::ifstream& operator >> (std::ifstream& stream, Student& student)
{
	short length;
	//istream& read(const char*, streamsize);
	stream.read((char*)&length, sizeof(length)); 

	//if (stream.fail()) { student.StudentId[0] = 0; return stream; }
	char* buffer = new char[length + 1];
	stream.read(buffer, length);
	buffer[length] = 0; // terminate buffer with null

	
	std::istrstream strbuff(buffer);
	setStudentStream(strbuff, student);
	//strbuff >> student;
	delete[] buffer;
	return stream;
}

std::istream& operator >> (std::istream& stream, Student& student) {
	char buffer[36];
	std::cout << "Enter student id: " << std::flush; //, or <cr> to end: " << std::flush;
	stream.getline(buffer, 10);
	student.setId(buffer);
	//if (strlen(student.StudentId) == 0) return stream;
	std::cout << "Enter name: " << std::flush; stream.getline(buffer, 20);
	student.setName(buffer);
	std::cout << "Enter address: " << std::flush; stream.getline(buffer, 12);
	student.setAddress(buffer);
	std::cout << "Enter date of frist enrollment: " << std::flush; stream.getline(buffer, 35);
	student.setDate(buffer);

	std::cout << "Enter number of credit hours: " << std::flush; stream.getline(buffer, 5);
	for (char c : buffer) {
		if (c == '\0') break;
		if (!(isdigit(c))) {
			buffer[0] = '0'; buffer[1] = '\0'; break;
		}
	}
	student.setCredit(atoi(buffer));
	return stream;
}



void Student::creditIncr() {
	++(this->NumberOfCreditHours);
}

int Student::InitBuffer(FixedTextBuffer& Buffer)
// initialize a FixedTextBuffer to be used for Persons
{
	int result;
	result = Buffer.AddField(9); // StudentId [10];
	result = result && Buffer.AddField(34); // Name [35];
	result = result && Buffer.AddField(19); // Address [20];
	result = result && Buffer.AddField(10); // DateOfFirstEnrollment [11];
	result = result && Buffer.AddField(4); // NumberOfCreditHours [5];
	return result;
}

void itoString(char *str, const int number) {
	sprintf(str, "%-4d", number);
}

int Student::Pack(FixedTextBuffer& Buffer) const
{// pack the fields into a FixedTextBuffer, return TRUE if all succeed, FALSE o/w
	int result;
	//Buffer.Clear();
	result = Buffer.Pack(StudentId);
	result = result && Buffer.Pack(Name);
	result = result && Buffer.Pack(Address);
	result = result && Buffer.Pack(DateOfFirstEnrollment);
	char credit[5];
	itoString(credit, NumberOfCreditHours);
	result = result && Buffer.Pack(credit);

	return result;
}

int Student::Pack(LengthTextBuffer& Buffer) const
{// pack the fields into a FixedTextBuffer, return TRUE if all succeed, FALSE o/w
	int result;
	//Buffer.Clear();
	result = Buffer.Pack(StudentId);
	result = result && Buffer.Pack(Name);
	result = result && Buffer.Pack(Address);
	result = result && Buffer.Pack(DateOfFirstEnrollment);
	char credit[5];
	itoString(credit, NumberOfCreditHours);
	result = result && Buffer.Pack(credit);

	return result;
}

void Student::Clear()
{
	// set each field to an empty string
	StudentId[0] = 0;
	Address[0] = 0;
	DateOfFirstEnrollment[0] = 0;
	Name[0] = 0;
	NumberOfCreditHours = 0;
}

int Student::Unpack(FixedTextBuffer& Buffer)
{
	Clear();
	int result;
	result = Buffer.Unpack(StudentId);
	result = result && Buffer.Unpack(Name);
	result = result && Buffer.Unpack(Address);
	result = result && Buffer.Unpack(DateOfFirstEnrollment);
	char num[5];
	result = result && Buffer.Unpack(num);
	if (result)
		NumberOfCreditHours = atoi(num);
	return result;
}

int Student::Unpack(LengthTextBuffer& Buffer)
{
	Clear();
	int result;
	result = Buffer.Unpack(StudentId);
	result = result && Buffer.Unpack(Name);
	result = result && Buffer.Unpack(Address);
	result = result && Buffer.Unpack(DateOfFirstEnrollment);
	char num[5];
	result = result && Buffer.Unpack(num);
	if (result)
		NumberOfCreditHours = atoi(num);
	return result;
}

int Student::InitBuffer(LengthTextBuffer& Buffer)
// initialize a LengthTextBuffer to be used for Persons
{
	return TRUE;
}

int Student::InitBuffer(DelimTextBuffer& Buffer)
// initialize a DelimTextBuffer to be used for Persons
{
	return TRUE;
}

int Student::Pack(DelimTextBuffer& Buffer) const
{// pack the fields into a FixedTextBuffer, return TRUE if all succeed, FALSE o/w
	int result;
	//Buffer.Clear();
	result = Buffer.Pack(StudentId);
	result = result && Buffer.Pack(Name);
	result = result && Buffer.Pack(Address);
	result = result && Buffer.Pack(DateOfFirstEnrollment);
	char credit[5];
	itoString(credit, NumberOfCreditHours);
	result = result && Buffer.Pack(credit);

	return result;
}

int Student::Unpack(DelimTextBuffer& Buffer)
{
	Clear();
	int result;
	result = Buffer.Unpack(StudentId);
	result = result && Buffer.Unpack(Name);
	result = result && Buffer.Unpack(Address);
	result = result && Buffer.Unpack(DateOfFirstEnrollment);
	char num[5];
	result = result && Buffer.Unpack(num);
	if (result)
		NumberOfCreditHours = atoi(num);
	return result;
}