#pragma once

#ifndef SUPPLY
#define SUPPLY

#include <iostream>

#include "iobuffer.h"
#include "fixfld.h"
#include "length.h"
#include "delim.h"

class Supply
{
	char sno[3], pno[3], jno[3], city[10], qty[3];


public:
	friend std::ostream& operator << (std::ostream& stream, const Supply& supply);
	friend std::istream& operator >> (std::istream& stream, Supply& supply);


	Supply();
	Supply(Supply&);
	void Clear();
	char* Key() const;
	int Unpack(IOBuffer&);
	int Pack(IOBuffer&) const;
	static int InitBuffer(FixedFieldBuffer& Buffer);
	static int InitBuffer(LengthFieldBuffer&);
	static int InitBuffer(DelimFieldBuffer&);

};

#endif