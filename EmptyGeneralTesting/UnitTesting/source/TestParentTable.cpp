//#pragma once
//#include <cppunit/config/SourcePrefix.h>
//#include "ParentTable.h"
//#include "TestParentTable.h"
//
//
//#include <iostream>
//#include <vector>
//
//extern std::vector<int> OBJECT_NOT_FOUND;
//
//void ParentTableTest::setUp()
//{
//
//}
//
//void ParentTableTest::tearDown()
//{
//
//}
//
//// Registers the fixture into the 'registry'
//CPPUNIT_TEST_SUITE_REGISTRATION( ParentTableTest );
//
//void ParentTableTest::testInsertParent()
//{
//	ParentTable table;
//	table.insertParent(2, 3);
//
//	int parentStmt = table.getParentStmt(3);
//	CPPUNIT_ASSERT(2 == parentStmt);
//
//	std::vector<int> children = table.getChildStmt(2);
//	std::vector<int> expectedChildren (1, 3); // initialize new vector with one element, element's value = 2.
//	CPPUNIT_ASSERT(expectedChildren == children);
//
//	// CPPUNIT_ASSERT(true == table.isParent(2, 3));
//
//	int returnedIndex = table.insertParent(2, 3);
//	CPPUNIT_ASSERT(-1 == returnedIndex);
//
//	return;
//}
//
//void ParentTableTest::testIsParent()
//{
//	ParentTable table;
//	table.insertParent(2, 3);
//	table.insertParent(2, 4);
//	
//	CPPUNIT_ASSERT(true == table.isParent(2, 3));
//	CPPUNIT_ASSERT(true == table.isParent(2, 4));
//	CPPUNIT_ASSERT(false == table.isParent(3, 4));
//	return;
//}
//
//void ParentTableTest::testIsParentStar()
//{
//	ParentTable table;
//	table.insertParent(5, 6);
//	table.insertParent(5, 7);
//	table.insertParent(5, 10);
//	table.insertParent(5, 11);
//
//	table.insertParent(7, 8);
//	table.insertParent(7, 9);
//	table.insertParent(11, 12);
//	table.insertParent(12, 13);
//
//	CPPUNIT_ASSERT(false == table.isParentStar(13, 8));
//	CPPUNIT_ASSERT(false == table.isParentStar(7, 10));
//	CPPUNIT_ASSERT(true == table.isParentStar(5, 13));
//	return;
//}
//
//void ParentTableTest::testGetParentStmt()
//{
//	ParentTable table;
//	table.insertParent(2, 3);
//	table.insertParent(2, 4);
//
//	CPPUNIT_ASSERT(2 == table.getParentStmt(3));
//	CPPUNIT_ASSERT(2 == table.getParentStmt(4));
//	CPPUNIT_ASSERT(-1 == table.getParentStmt(2));
//	return;
//}
//
//void ParentTableTest::testGetChildStmt()
//{
//	ParentTable table;
//	table.insertParent(2, 3);
//	table.insertParent(2, 4);
//
//	std::vector<int> expectedChildren;
//	expectedChildren.push_back(3); expectedChildren.push_back(4); 
//	CPPUNIT_ASSERT(expectedChildren == table.getChildStmt(2));
//
//	for(size_t index=0; index < table.getChildStmt(1).size(); index++)
//	{
//		std::cout<<table.getChildStmt(1).at(index)<<" ";
//	}
//
//	//CPPUNIT_ASSERT(OBJECT_NOT_FOUND == table.getChildStmt(1));
//	return;
//}
//
//// This test is based on Source2 test case.
//void ParentTableTest::testGetChildStarStmt()
//{
//	ParentTable table;
//	table.insertParent(5, 6);
//	table.insertParent(5, 7);
//	table.insertParent(5, 10);
//	table.insertParent(5, 11);
//
//	table.insertParent(7, 8);
//	table.insertParent(7, 9);
//	table.insertParent(11, 12);
//	table.insertParent(12, 13);
//
//	std::vector<int> expectedChildrenStar_5;
//	expectedChildrenStar_5.push_back(6); expectedChildrenStar_5.push_back(7);
//	expectedChildrenStar_5.push_back(8); expectedChildrenStar_5.push_back(9);
//	expectedChildrenStar_5.push_back(10); expectedChildrenStar_5.push_back(11);
//	expectedChildrenStar_5.push_back(12); expectedChildrenStar_5.push_back(13);
//	
//	std::vector<int> expectedChildrenStar_11;
//	expectedChildrenStar_11.push_back(12); expectedChildrenStar_11.push_back(13);
//	
//	// be careful here as the content of 2 vectors might be the same, just elements are not in the same position.
//	// remember to sort the result in your implementation, not for your Prof to read it.
//	// but for this test to pass.
//	// we design the test case in this way.
//	/*CPPUNIT_ASSERT(expectedChildrenStar_5 == table.getChildStarStmt(5));
//	CPPUNIT_ASSERT(expectedChildrenStar_11 == table.getChildStarStmt(11));
//	CPPUNIT_ASSERT(OBJECT_NOT_FOUND == table.getChildStarStmt(13));*/
//
//	//std::vector<int> childrenStar = table.getChildStarStmt(5);
//	//for(size_t index=0; index < childrenStar.size(); index++)
//	//{
//	//	std::cout<<childrenStar.at(index)<<" ";
//	//}
//	
//
//	return;
//}
//
//void ParentTableTest::testGetParentStarStmt()
//{
//	ParentTable table;
//	table.insertParent(5, 6);
//	table.insertParent(5, 7);
//	table.insertParent(5, 10);
//	table.insertParent(5, 11);
//
//	table.insertParent(7, 8);
//	table.insertParent(7, 9);
//	table.insertParent(11, 12);
//	table.insertParent(12, 13);
//
//	std::vector<int> expectedParentStar_8;
//	expectedParentStar_8.push_back(5); expectedParentStar_8.push_back(7);
//
//	std::vector<int> expectedParentStar_13;
//	expectedParentStar_13.push_back(5); expectedParentStar_13.push_back(11);
//	expectedParentStar_13.push_back(12);
//
//	//CPPUNIT_ASSERT(expectedParentStar_8 == table.getParentStarStmt(8));
//	//CPPUNIT_ASSERT(expectedParentStar_13 == table.getParentStarStmt(13));
//	//CPPUNIT_ASSERT(OBJECT_NOT_FOUND == table.getParentStarStmt(5));
//	return;
//}
//
//void ParentTableTest::testGetAllParentStmt()
//{
//	ParentTable table;
//	table.insertParent(5, 6);
//	table.insertParent(5, 7);
//	table.insertParent(5, 10);
//	table.insertParent(5, 11);
//
//	table.insertParent(7, 8);
//	table.insertParent(7, 9);
//	table.insertParent(11, 12);
//	table.insertParent(12, 13);
//
//	std::vector<int> expectedParent;
//	expectedParent.push_back(5); expectedParent.push_back(5);
//	expectedParent.push_back(5); expectedParent.push_back(5);
//	expectedParent.push_back(7); expectedParent.push_back(7);
//	expectedParent.push_back(11); expectedParent.push_back(12);
//	CPPUNIT_ASSERT(expectedParent == table.getAllParentStmt());
//	return;
//}
//
//void ParentTableTest::testGetAllChildStmt()
//{
//	ParentTable table;
//	table.insertParent(5, 6);
//	table.insertParent(5, 7);
//	table.insertParent(5, 10);
//	table.insertParent(5, 11);
//
//	table.insertParent(7, 8);
//	table.insertParent(7, 9);
//	table.insertParent(11, 12);
//	table.insertParent(12, 13);
//
//	std::vector<int> expectedChildren;
//	expectedChildren.push_back(6); expectedChildren.push_back(7);
//	expectedChildren.push_back(10); expectedChildren.push_back(11);
//	expectedChildren.push_back(8); expectedChildren.push_back(9);
//	expectedChildren.push_back(12); expectedChildren.push_back(13);
//
//	CPPUNIT_ASSERT(expectedChildren == table.getAllChildStmt());
//	return;
//}