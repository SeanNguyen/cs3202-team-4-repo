#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "Tree.h"

class TreeTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( TreeTest ); // Note 3 
	CPPUNIT_TEST( testCreateNode );
	CPPUNIT_TEST( testRoot );
	CPPUNIT_TEST( testGetNumChildren );
	CPPUNIT_TEST( testGetChildAtIndex );
	CPPUNIT_TEST( testAddChild );
	CPPUNIT_TEST( testPrintTree );

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testCreateNode();
	void testRoot();
	void testGetNumChildren();
	void testGetChildAtIndex();
	void testAddChild();
	void testPrintTree();
};