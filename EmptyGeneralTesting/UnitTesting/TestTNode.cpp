#include <cppunit/config/SourcePrefix.h>
#include "TestTNode.h"

void TNodeTest::setUp() {
}

void TNodeTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( TNodeTest ); // Note 4 

void TNodeTest::testConstructor() {
	TNode node1;
	TNode node2(Program);
	TNode node3(Var, "x");

	CPPUNIT_ASSERT(node1.getType()==Undefined);
	CPPUNIT_ASSERT(node1.getValue()=="");
	CPPUNIT_ASSERT(node2.getType()==Program);
	CPPUNIT_ASSERT(node2.getValue()=="");
	CPPUNIT_ASSERT(node3.getType()==Var);
	CPPUNIT_ASSERT(node3.getValue()=="x");
}

void TNodeTest::testGetChildAtIndex() {
}

void TNodeTest::testGetNumChildren() {
}