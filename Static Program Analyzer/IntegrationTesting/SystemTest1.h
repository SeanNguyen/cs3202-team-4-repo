#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include "../AutoTester/source/AbstractWrapper.h"
#include "Parser.h"
#include "QueryProcessor.h"

/* SYSTEM TESTING FOR ITERATION 0 AND 1 */
class SystemTest1 : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( SystemTest1 ); 
	/*CPPUNIT_TEST( test1 );
	CPPUNIT_TEST( test2 );*/
	CPPUNIT_TEST( test3 );
	/*CPPUNIT_TEST( test4 );
	CPPUNIT_TEST( test5 );
	CPPUNIT_TEST( test6 );
	CPPUNIT_TEST( testCallsCallStar );
	CPPUNIT_TEST( testWithCls );
	CPPUNIT_TEST( testNext );
	CPPUNIT_TEST( test7 );
	CPPUNIT_TEST( test8 );
	CPPUNIT_TEST( TestModifyUsesProc );*/
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
private:
	void test1();
	void test2();
	void test3();
	void test4();
	void test5();
	void test6();
	void test7();
	void testCallsCallStar();
	void testWithCls();
	void testNext();
	void test8();
	//void TestModifyUsesProc();
};