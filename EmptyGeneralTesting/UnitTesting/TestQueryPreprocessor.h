#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "QueryPreprocessor.h"

class QueryPreprocessorTest : public CPPUNIT_NS::TestFixture {
	CPPUNIT_TEST_SUITE( QueryPreprocessorTest );  
	CPPUNIT_TEST( testReadFileData );
	CPPUNIT_TEST( testBuildSymbolTable );
	CPPUNIT_TEST( testBuildTree );
	CPPUNIT_TEST( testBuildSuchThatCls );
	CPPUNIT_TEST( testBuildPatternCls );
	CPPUNIT_TEST( testBuildWithCls );

	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testReadFileData();
	void testBuildSymbolTable();
	void testBuildTree();
	void testBuildSuchThatCls();
	void testBuildPatternCls();
	void testBuildWithCls();
};
