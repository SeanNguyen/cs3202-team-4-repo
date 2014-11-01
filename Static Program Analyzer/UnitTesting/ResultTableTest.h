#pragma once

#include <cppunit/extensions/HelperMacros.h>

class TestResultTable : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( TestResultTable);
	CPPUNIT_TEST( TestInsertSymbols );
	CPPUNIT_TEST( TestInsertVal );
	CPPUNIT_TEST( TestDeleteInvalidRow );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//test cases
	void TestInsertSymbols();
	void TestInsertVal();
	void TestDeleteInvalidRow();
};