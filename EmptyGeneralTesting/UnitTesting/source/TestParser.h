#ifndef TestParser_h
#define TestParser_h

#include <cppunit/extensions/HelperMacros.h> // Note 1

class ParserTest : public CPPUNIT_NS::TestFixture // Note 2
{
	CPPUNIT_TEST_SUITE( ParserTest ); // Note 3 
	CPPUNIT_TEST(testBuildVarTable);
	CPPUNIT_TEST(testBuildFollowTable);
	CPPUNIT_TEST(testBuildModifyTable);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	void testBuildVarTable();
	void testBuildFollowTable();
	void testBuildModifyTable();
};

#endif