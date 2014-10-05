#pragma once

#include <cppunit/extensions/HelperMacros.h>

class MapTableTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( MapTableTest );
	CPPUNIT_TEST( TestInsert );
	CPPUNIT_TEST( TestIsMapped );
	CPPUNIT_TEST( TestIsMappedStar );
	CPPUNIT_TEST( TestGetValues );
	CPPUNIT_TEST( TestGetValuesStar );
	CPPUNIT_TEST_SUITE_END();

public:
	MapTableTest(void);
	~MapTableTest(void);

	void setUp();
	void tearDown();

	//test cases
	void TestInsert();
	void TestIsMapped();
	void TestIsMappedStar();
	void TestGetValues();
	void TestGetValuesStar();
};