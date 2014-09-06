#include <cppunit/config/SourcePrefix.h>
#include "UseTable.h"
#include "TestUseTable.h"

#include <iostream>
#include <string>
#include <vector>

void
UseTest::setUp()
{
}

void 
UseTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( UseTest ); // Note 4 


void UseTest::testInsert(){

	Use useObj;
	
	// verify that the insertion is correct - Note 7
	int result1 = useObj.insertUses(1,1);
	int result2 = useObj.insertUses(2,2);

	std::cout << result1;
	std::cout << result2;

	CPPUNIT_ASSERT_EQUAL(100, result1);
	CPPUNIT_ASSERT_EQUAL(100, result2);

	int result3 = useObj.insertUses(1,1);

	std::cout << useObj.isUses(1,1);

	// attempt to insert a pair which already exists
	CPPUNIT_ASSERT_EQUAL(100, result3);

	return;
}

void UseTest::testisUse(){

	Use useObj;

	//insert a few pairs first
	useObj.insertUses(1, 1);
	useObj.insertUses(2, 2);

	
	// verify that the pair exists - Note 7
	CPPUNIT_ASSERT_EQUAL(true, useObj.isUses(1, 1));
	CPPUNIT_ASSERT_EQUAL(true, useObj.isUses(2, 2));

	// attempt to check a pair which does not exists
	CPPUNIT_ASSERT_EQUAL(false, useObj.isUses(5, 3));

	return;
}

void UseTest::testgetUsedVarAtStmt(){

	Use useObj;

	//insert a few pairs first
	int result = useObj.insertUses(1, 1);
	int result1 = useObj.insertUses(2, 2);
	int result2 = useObj.insertUses(2, 3);

	std::vector<int> actual = useObj.getUsedVarAtStmt(2);

	std::cout<<"getUsedVarAtStmt";
	
	for(std::size_t i = 0; i < actual.size(); i++){
		std::cout << actual[i] << std::endl;
	}

	return;
}

void UseTest::testgetStmtUsingVar(){

	Use useObj;

	//insert a few pairs first
	int result = useObj.insertUses(1, 1);
	int result1 = useObj.insertUses(2, 2);
	int result2 = useObj.insertUses(5, 2);
	int result3 = useObj.insertUses(7, 2);

	std::vector<int> actual = useObj.getStmtUsingVar(2);

	std::cout<<"getStmtUsingVar";
	
	for(std::size_t i = 0; i < actual.size(); i++){
		std::cout << actual[i] << std::endl;
	 }

	return;
}

void UseTest::testgetAllUsingStmt(){
	
	Use useObj;

	//insert a few pairs first
	int result = useObj.insertUses(1, 1);
	int result1 = useObj.insertUses(2, 2);
	int result2 = useObj.insertUses(3, 3);
	int result3 = useObj.insertUses(9, 4);

	std::vector<int> actual = useObj.getAllUsingStmt();

	std::cout<<"getAllUsingStmt";
	
	for(std::size_t i = 0; i < actual.size(); i++){
		std::cout << actual[i] << std::endl;
	 }

	return;
}

void UseTest::testgetAllUsedVar(){
	
	Use useObj;

	//insert a few pairs first
	int result = useObj.insertUses(1, 1);
	int result1 = useObj.insertUses(2, 2);
	int result2 = useObj.insertUses(3, 3);
	int result3 = useObj.insertUses(9, 4);

	std::vector<int> actual = useObj.getAllUsedVar();

	std::cout<<"getAllUsedVar";
	
	for(std::size_t i = 0; i < actual.size(); i++){
		std::cout << actual[i] << std::endl;
	 }

	return;
}

		
		

