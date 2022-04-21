#include "supply.h"
#include <strstream>
#include <string.h>


Supply::Supply(){
	Clear();
}

Supply::Supply(Supply& other) {
	Clear();
	strcpy(this->sno, other.sno);
	strcpy(this->pno, other.pno);
	strcpy(this->jno, other.jno);
	strcpy(this->city, other.city);
	strcpy(this->qty, other.qty);
}

void Supply::Clear()
{
	// set each field to an empty string
	sno[0] = 0;
	pno[0] = 0;
	jno[0] = 0;
	city[0] = 0;
	qty[0] = 0;
}

int Supply::InitBuffer(FixedFieldBuffer& Buffer)
// initialize a FixedTextBuffer to be used for Persons
{
	int result;
	result = Buffer.AddField(2); // sno[3]
	result = result && Buffer.AddField(2); // pno[3]
	result = result && Buffer.AddField(2); // jno[3]
	result = result && Buffer.AddField(9); // city[10]
	result = result && Buffer.AddField(2); // qty[3];
	return result;
}

int Supply::InitBuffer(LengthFieldBuffer& Buffer)
// initialize a LengthTextBuffer to be used for Persons
{
	return TRUE;
}

int Supply::InitBuffer(DelimFieldBuffer& Buffer)
// initialize a DelimTextBuffer to be used for Persons
{
	return TRUE;
}

int Supply::Pack(IOBuffer& Buffer) const
{// pack the fields into a FixedFieldBuffer, 
 // return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer.Clear();
	numBytes = Buffer.Pack(sno);//동적 바인딩
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(pno);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(jno);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(city);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(qty);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int Supply::Unpack(IOBuffer& Buffer)
{
	Clear();
	int numBytes;
	//power of virtual functions
	numBytes = Buffer.Unpack(sno);//Unpack()에 대항 F12를 누르면 일치하는 3개 함수 존재 - 동적 바인딩
	if (numBytes == -1) return FALSE;
	sno[numBytes] = 0;
	numBytes = Buffer.Unpack(pno);
	if (numBytes == -1) return FALSE;
	pno[numBytes] = 0;
	numBytes = Buffer.Unpack(jno);
	if (numBytes == -1) return FALSE;
	jno[numBytes] = 0;
	numBytes = Buffer.Unpack(city);
	if (numBytes == -1) return FALSE;
	city[numBytes] = 0;
	numBytes = Buffer.Unpack(qty);
	if (numBytes == -1) return FALSE;
	qty[numBytes] = 0;
	return TRUE;
}

char* Supply::Key() const
{// produce key as concatenation of Label and IdNum
	std::ostrstream key;
	key << sno << pno << jno << ends;
	return key.str();
}

std::ostream& operator << (std::ostream& stream, const Supply& supply) {
	stream << "sno : " << supply.sno << "\npno : " << supply.pno <<
		"\njno : " << supply.jno << "\ncity : " << supply.city
		<< "\nqty : " << supply.qty << "\n\n";
	return stream;
}

std::istream& operator >> (std::istream& stream, Supply& supply) {
	char buffer[36];
	std::cout << "Enter sno: " << std::flush; //, or <cr> to end: " << std::flush;
	stream.getline(buffer, 3);
	strcpy(supply.sno, buffer);
	//if (strlen(student.StudentId) == 0) return stream;
	std::cout << "Enter pno: " << std::flush; stream.getline(buffer, 3);
	strcpy(supply.pno, buffer);
	std::cout << "Enter jno: " << std::flush; stream.getline(buffer, 3);
	strcpy(supply.jno, buffer);
	std::cout << "Enter city: " << std::flush; stream.getline(buffer, 10);
	strcpy(supply.city, buffer);
	std::cout << "Enter qty: " << std::flush; stream.getline(buffer, 3);
	strcpy(supply.qty, buffer);
	return stream;
}