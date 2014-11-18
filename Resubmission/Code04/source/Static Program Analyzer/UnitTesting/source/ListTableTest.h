#pragma once

#include <cppunit/extensions/HelperMacros.h>

class ListTableTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( ListTableTest );
	CPPUNIT_TEST( TestInsert );
	CPPUNIT_TEST( TestGetIndexes );
	CPPUNIT_TEST( TestGetValue );
	CPPUNIT_TEST_SUITE_END();

public:
	ListTableTest(void);
	~ListTableTest(void);

	void setUp();
	void tearDown();

	//test cases
	void TestInsert();
	void TestGetIndexes();
	void TestGetValue();
};

