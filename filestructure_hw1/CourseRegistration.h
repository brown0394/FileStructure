#pragma once
class CourseRegistration
{
	char *courseId; char *studentId;
	int numberOfCreditHours; float grade;
	void courseStrCpy(char*& self, const char* str);

	friend std::ostream& operator << (std::ostream& stream, const CourseRegistration& course);
	friend std::ofstream& operator << (std::ofstream& stream, const CourseRegistration& course);
	friend std::istream& operator >> (std::istream& stream, CourseRegistration& course);
	friend std::ifstream& operator >> (std::ifstream& stream, CourseRegistration& course);
public:
	// method
	CourseRegistration(); // default constructor
	CourseRegistration(const CourseRegistration&);
	CourseRegistration(char *courseId, char *studentId, int credit, float grade);
	~CourseRegistration();

	CourseRegistration& operator =(const CourseRegistration&);
	void setStudentId(const char*);
	char* getStudentId();
	void setCredit(int);
	int getCredit();
	void setCourseId(const char*);
	char* getCourseId();
	void setGrade(float);
	float getGrade();

};

