#pragma once

#include <cppunit/extensions/HelperMacros.h>

class TestAffects : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( TestAffects );
	CPPUNIT_TEST( TestisAffect );
	CPPUNIT_TEST( TestIsAffectStar );
	CPPUNIT_TEST( TestgetAffected );
	CPPUNIT_TEST( TestgetAffecting );
	CPPUNIT_TEST( TestgetAffectingStar );
	CPPUNIT_TEST_SUITE_END();

public:
	TestAffects(void);
	~TestAffects(void);

	void setUp();
	void tearDown();

	//test cases
	void TestisAffect();
	void TestIsAffectStar();
	void TestgetAffected();
	void TestgetAffecting();
	void TestgetAffectingStar();
};