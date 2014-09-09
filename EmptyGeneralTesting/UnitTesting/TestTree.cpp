#include "TestTree.h"

void TreeTest::setUp() {
}

void TreeTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( TreeTest );

void TreeTest::testCreateNode() {
	Tree tree;
	TNode node1 = tree.createNode();
	TNode node2 = tree.createNode(Program);
	TNode node3 = tree.createNode(Var, "test");

	CPPUNIT_ASSERT_EQUAL(Undefined, node1.getType());
	CPPUNIT_ASSERT_EQUAL(Program,	node2.getType());
	CPPUNIT_ASSERT_EQUAL(Var,		node3.getType());
	CPPUNIT_ASSERT(""==node1.getValue());
	CPPUNIT_ASSERT(""==node2.getValue());
	CPPUNIT_ASSERT("test"==node3.getValue());
}

void TreeTest::testRoot() {
}

void TreeTest::testGetNumChildren() {
}

void TreeTest::testGetChildAtIndex() {
}

void TreeTest::testAddChild() {
}