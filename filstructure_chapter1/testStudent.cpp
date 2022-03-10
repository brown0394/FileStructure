// create a list of student information
#include "student.h"


int main() {
	Student st1;
	Student st2(2018, "CHOI", "Suwon, Seryu", "2020.03.01", 10);
	st1 = st2;
	Student st3(st1);


	st3.setAddress("Pusan, JangJEon");
	st3.setDate("2020.09.01");
	std::cout << st1 << st2 << st3;
	return 0;
}