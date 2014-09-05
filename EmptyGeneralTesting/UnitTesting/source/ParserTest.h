#ifndef ParserTest_h
#define ParserTest_h

#include <cppunit/extensions/HelperMacros.h>

class ParserTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( ParserTest );
	CPPUNIT_TEST( testParse );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//test cases
	void testParse();
};

#endif