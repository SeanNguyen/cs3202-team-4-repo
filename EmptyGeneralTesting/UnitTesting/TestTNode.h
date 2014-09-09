#pragma once

#include <cppunit/extensions/HelperMacros.h>

#include "TNode.h"

class TNodeTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( TNodeTest ); // Note 3 
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST( testGetNumChildren );
	CPPUNIT_TEST( testGetChildAtIndex );
	CPPUNIT_TEST( testAddChild );

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	void testConstructor();
	void testGetNumChildren();
	void testGetChildAtIndex();
	void testAddChild();
};