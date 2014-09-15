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
	Tree tree;
	TNode root = tree.createNode();
	tree.setRoot(root);

	TNode _root = *tree.getRoot();

	CPPUNIT_ASSERT(_root.getType()==Undefined);
	CPPUNIT_ASSERT(_root.getValue()=="");
}

void TreeTest::testGetNumChildren() {
	Tree tree;
	// randomize some nodes
	TNode root = tree.createNode(Program);
	TNode node1 = tree.createNode(Procedure, "First");
	TNode node1_1 = tree.createNode(StmtList);
	TNode node1_2 = tree.createNode(While);
	TNode node2 = tree.createNode(If);

	tree.setRoot(root);
	tree.addChild(root, node1);
	tree.addChild(node1, node1_1);
	tree.addChild(node1, node1_2);
	tree.addChild(root, node2);

	// testing
	TNode _root = *tree.getRoot();
	TNode _child1 = *tree.getChildAtIndex(_root, 0);

	CPPUNIT_ASSERT_EQUAL(2, _root.getNumChildren());
	CPPUNIT_ASSERT_EQUAL(2, _child1.getNumChildren());
}

void TreeTest::testGetChildAtIndex() {
}

void TreeTest::testAddChild() {
	Tree tree;
	// randomize some nodes
	TNode root = tree.createNode(Program);
	TNode node1 = tree.createNode(Procedure, "First");
	TNode node1_1 = tree.createNode(StmtList);
	TNode node1_2 = tree.createNode(While);
	TNode node2 = tree.createNode(If);

	tree.setRoot(root);
	tree.addChild(root, node1);
	tree.addChild(node1, node1_1);
	tree.addChild(node1, node1_2);
	tree.addChild(root, node2);

	// testing
	TNode _root = *tree.getRoot();
	TNode _child1 = *tree.getChildAtIndex(_root, 0);

	CPPUNIT_ASSERT_EQUAL(2, _root.getNumChildren());
	CPPUNIT_ASSERT_EQUAL(Procedure, _child1.getType());
	CPPUNIT_ASSERT_EQUAL(2, _child1.getNumChildren());
}

void TreeTest::testPrintTree() {
	Tree tree;
	// randomize some nodes
	TNode root = tree.createNode(Program);
	TNode node1 = tree.createNode(Procedure, "First");
	TNode node1_1 = tree.createNode(StmtList);
	TNode node1_2 = tree.createNode(While);
	TNode node2 = tree.createNode(If);

	tree.setRoot(root);
	tree.addChild(root, node1);
	tree.addChild(node1, node1_1);
	tree.addChild(node1, node1_2);
	tree.addChild(root, node2);

	/*cout <<endl;
	tree.printTree();
	cout <<endl;*/
}