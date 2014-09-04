//#include <cppunit/config/SourcePrefix.h>
//#include "Student.h"
//#include "TestStudent.h"
//
//#include <iostream>
//#include <string>
//
//void 
//StudentTest::setUp()
//{
//}
//
//void 
//StudentTest::tearDown()
//{
//}
//
//// Registers the fixture into the 'registry'
//CPPUNIT_TEST_SUITE_REGISTRATION( StudentTest ); // Note 4 
//
//// method to test the constructor
//void StudentTest::testConstructor()
//{  // Note 5
//	// create a student object
//	Student stu("Tan Meng Chee", "94-1111B-13");
//
//	// check that the object is constructed correctly - Note 6
//	std::string student_name = stu.getStuName();
//	CPPUNIT_ASSERT(student_name == "Tan Meng Chee");
//
//	std::string student_number = stu.getStuNumber();
//	CPPUNIT_ASSERT(student_number == "94-1111B-13");
//
//	return;
//}
//
//// method to test the assigning and retrieval of grades
//void StudentTest::testAssignAndRetrieveGrades()
//{
//	// create a student
//	Student stu("Jimmy", "946302B");
//
//	// assign a few grades to this student
//	stu.assignGrade("cs2102", 60);
//	stu.assignGrade("cs2103", 70);
//	stu.assignGrade("cs3215", 80);
//
//	// verify that the assignment is correct - Note 7
//	CPPUNIT_ASSERT_EQUAL(60, stu.getGrade("cs2102"));
//	CPPUNIT_ASSERT_EQUAL(70, stu.getGrade("cs2103"));
//
//	// attempt to retrieve a course that does not exist
//	CPPUNIT_ASSERT_EQUAL(-1, stu.getGrade("cs21002"));
//
//	return;
//}