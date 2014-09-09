#pragma once

#ifndef ParserTest_h
#define ParserTest_h

#include <cppunit/extensions/HelperMacros.h>

class ParserTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( ParserTest );
	CPPUNIT_TEST( testParseEmptyProcedure );
	CPPUNIT_TEST( testParseCall );
	CPPUNIT_TEST( testParseWhile );
	CPPUNIT_TEST( testParseIf );
	CPPUNIT_TEST( testParseSimpleAssign );
	CPPUNIT_TEST( testParseComplexAssign );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	//test cases
	void testParseEmptyProcedure();
	void testParseCall();
	void testParseWhile();
	void testParseIf();
	void testParseSimpleAssign();
	void testParseComplexAssign();
};

#endif