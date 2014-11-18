#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "QueryRepresentator.h"

class QueryRepresentatorTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( QueryRepresentatorTest );  
	CPPUNIT_TEST( testSymbolTable );
	CPPUNIT_TEST( testQueryTree );

	
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testSymbolTable();
	void testQueryTree();
private:
	void setUpData();
};