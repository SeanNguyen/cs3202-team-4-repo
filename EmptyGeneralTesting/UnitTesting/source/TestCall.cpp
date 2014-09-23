#include <cppunit/config/SourcePrefix.h>
#include "CallTable.h"
#include "TestCall.h"
#include <string>
#include <iostream>
#include <vector>

void
CallTest::setUp()
{
}

void 
CallTest::tearDown()
{
}

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( CallTest ); // Note 4 


void CallTest::testInsert(){

	Call callObj;
	
	// verify that the insertion is correct - Note 7
	int result1 = callObj.insertCalls(1,2);
	int result2 = callObj.insertCalls(2,3);

	CPPUNIT_ASSERT_EQUAL(99, result1);
	CPPUNIT_ASSERT_EQUAL(99, result2);

	int result3 = callObj.insertCalls(1, 2);

	// attempt to insert a pair which already exists
	CPPUNIT_ASSERT_EQUAL(-1, result3);

	return;
}

void CallTest::testisCalls(){

	Call callObj;

	//insert a few pairs first
	int res1 = callObj.insertCalls(1, 2);
	int res2 = callObj.insertCalls(2, 3);

	//for(int i=0;i<callObj.callTable.size(); i++) {
 //     for (int j=0;j<callObj.callTable[i].size(); j++)
  //      std::cout << callObj.callTable[1][2] << " "; 
		//std::cout <<res1;
   //   std::cout << std::endl;
   //}
	
	// verify that the pair exists - Note 7
	CPPUNIT_ASSERT_EQUAL(true, callObj.isCalls(1, 2));
	CPPUNIT_ASSERT_EQUAL(false, callObj.isCalls(3, 2));
	CPPUNIT_ASSERT_EQUAL(true, callObj.isCalls(2, 3));

	// attempt to check a pair which does not exists
	CPPUNIT_ASSERT_EQUAL(false, callObj.isCalls(5, 6));

	//std::cout << callObj.isCalls(1, 2);
	//std::cout << callObj.isCalls(2,3);
	//std::cout << callObj.isCalls(5,6);


	//for(int i=0;i<callObj.callTable.size(); i++) {
 //     for (int j=0;j<callObj.callTable[i].size(); j++)
 //       std::cout << callObj.callTable[i][j] << " "; 
 //     std::cout << std::endl;
 //  }

	return;
}

void CallTest::testisCallStar()                               
{
	Call callObj;
	callObj.insertCalls(1, 2);
	callObj.insertCalls(2, 3);
	callObj.insertCalls(3, 4);

	CPPUNIT_ASSERT_EQUAL(false, callObj.isCallStar(4, 5));
	CPPUNIT_ASSERT_EQUAL(false, callObj.isCallStar(2, 1));
	CPPUNIT_ASSERT_EQUAL(true, callObj.isCallStar(1, 4));
	CPPUNIT_ASSERT_EQUAL(true, callObj.isCallStar(2, 4));
	CPPUNIT_ASSERT_EQUAL(true, callObj.isCallStar(1, 3));
	std::cout << "TEST CALL THIS: " << " ";
	std::cout <<  callObj.isCallStar(1, 3) << " ";
	std::cout << std::endl;
	return;
}

void CallTest::testgetCallingProc(){

	Call callObj;
	vector<int> callingProc;

	//insert a few pairs first
	int result = callObj.insertCalls(1, 2);
	int result1 = callObj.insertCalls(2, 3);
	int result2 = callObj.insertCalls(5, 6);
	int result4 = callObj.insertCalls(4, 6);
	int result3 = callObj.insertCalls(1, 3);

	//insert results in a vector
	callingProc.push_back(2);
	callingProc.push_back(1);
	
	// verify that the pair exists - Note 7
	CPPUNIT_ASSERT_EQUAL(callingProc.at(1), callObj.getCallingProc(3).at(0));
	CPPUNIT_ASSERT_EQUAL(callingProc.at(0), callObj.getCallingProc(3).at(1));
	callingProc.clear();
	callingProc.push_back(1);
	CPPUNIT_ASSERT_EQUAL(callingProc.at(0), callObj.getCallingProc(2).at(0));
	callingProc.clear();
	callingProc.push_back(5);
	callingProc.push_back(4);
	CPPUNIT_ASSERT_EQUAL(callingProc.at(1), callObj.getCallingProc(6).at(0));
	CPPUNIT_ASSERT_EQUAL(callingProc.at(0), callObj.getCallingProc(6).at(1));


	// attempt to get one which does not exist
	callingProc.clear();
	CPPUNIT_ASSERT_THROW(callObj.getCallingProc(7).at(0), std::out_of_range );

	return;
}

void CallTest::testgetCalledByProc(){

	Call callObj;
	vector<int> callingProc;

	//insert a few pairs first
	int result = callObj.insertCalls(1, 2);
	int result1 = callObj.insertCalls(2, 3);
	int result2 = callObj.insertCalls(5, 6);
	int result4 = callObj.insertCalls(4, 6);
	int result5 = callObj.insertCalls(4, 8);
	int result3 = callObj.insertCalls(1, 3);

	//insert results in a vector
	callingProc.push_back(2);
	callingProc.push_back(3);
	
	// verify that the pair exists - Note 7
	CPPUNIT_ASSERT_EQUAL(callingProc.at(0), callObj.getCalledByProc(1).at(0));
	CPPUNIT_ASSERT_EQUAL(callingProc.at(1), callObj.getCalledByProc(1).at(1));
	callingProc.clear();
	callingProc.push_back(6);
	CPPUNIT_ASSERT_EQUAL(callingProc.at(0), callObj.getCalledByProc(5).at(0));
	callingProc.clear();
	callingProc.push_back(6);
	callingProc.push_back(8);
	CPPUNIT_ASSERT_EQUAL(callingProc.at(0), callObj.getCalledByProc(4).at(0));
	CPPUNIT_ASSERT_EQUAL(callingProc.at(1), callObj.getCalledByProc(4).at(1));


	// attempt to get one which does not exist
	callingProc.clear();
	CPPUNIT_ASSERT_THROW(callObj.getCalledByProc(7).at(0), std::out_of_range );

	return;
}

// getCallingStarProc( proc ) gets all procedures that call proc directly and indirectly
void CallTest::testgetCallingStarProc(){
	
	Call callObj;
	vector<int> callingStarProc;

	//insert a few pairs first
	int result = callObj.insertCalls(1, 2);
	int result1 = callObj.insertCalls(2, 3);
	int result2 = callObj.insertCalls(5, 6);
	int result4 = callObj.insertCalls(4, 6);
	int result3 = callObj.insertCalls(3, 6);

	//insert results in a vector
	callingStarProc.push_back(1);
	callingStarProc.push_back(2);
	callingStarProc.push_back(3);
	callingStarProc.push_back(4);
	callingStarProc.push_back(5);
	
	// verify that the pair exists - Note 7
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(2), callObj.getCallingStarProc(6).at(0));
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(3), callObj.getCallingStarProc(6).at(1));
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(4), callObj.getCallingStarProc(6).at(2));
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(1), callObj.getCallingStarProc(6).at(3));
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(0), callObj.getCallingStarProc(6).at(4));
	callingStarProc.clear();
	callingStarProc.push_back(1);
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(0), callObj.getCallingStarProc(2).at(0));
	callingStarProc.clear();
	callingStarProc.push_back(2);
	callingStarProc.push_back(1);
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(0), callObj.getCallingStarProc(3).at(0));
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(1), callObj.getCallingStarProc(3).at(1));


	// attempt to get one which does not exist
	callingStarProc.clear();
	CPPUNIT_ASSERT_THROW(callObj.getCallingStarProc(7).at(0), std::out_of_range );

	return;
}

// getCalledByStarProc( proc ) gets all procedures that are called by proc directly and indirectly
void CallTest::testgetCalledByStarProc(){
	
	Call callObj;
	vector<int> callingStarProc;

	//insert a few pairs first
	int result = callObj.insertCalls(1, 2);
	int result1 = callObj.insertCalls(2, 3);
	int result2 = callObj.insertCalls(5, 6);
	int result4 = callObj.insertCalls(4, 6);
	int result3 = callObj.insertCalls(3, 6);

	//insert results in a vector
	callingStarProc.push_back(2);
	callingStarProc.push_back(3);
	callingStarProc.push_back(6);
	
	// verify that the pair exists - Note 7
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(0), callObj.getCallingStarProc(6).at(0));
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(1), callObj.getCallingStarProc(6).at(1));
	CPPUNIT_ASSERT_EQUAL(callingStarProc.at(2), callObj.getCallingStarProc(6).at(2));

	//callingStarProc.clear();
	//callingStarProc.push_back(1);
	//CPPUNIT_ASSERT_EQUAL(callingStarProc.at(0), callObj.getCallingStarProc(2).at(0));
	//callingStarProc.clear();
	//callingStarProc.push_back(2);
	//callingStarProc.push_back(1);
	//CPPUNIT_ASSERT_EQUAL(callingStarProc.at(0), callObj.getCallingStarProc(3).at(0));
	//CPPUNIT_ASSERT_EQUAL(callingStarProc.at(1), callObj.getCallingStarProc(3).at(1));


	//// attempt to get one which does not exist
	//callingStarProc.clear();
	//CPPUNIT_ASSERT_THROW(callObj.getCallingStarProc(7).at(0), std::out_of_range );

	return;
}