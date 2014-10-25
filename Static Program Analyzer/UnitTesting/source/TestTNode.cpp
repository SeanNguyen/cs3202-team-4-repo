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
	// randomize some TNodes for testing
	// randomize some TNodes for testing
	TNode * root = new TNode(Program);
	TNode * node1 = new TNode(Procedure, "p");
	TNode * node2 = new TNode(StmtList);
	TNode * node3 = new TNode(Var, "x");
	TNode * node4 = new TNode(Const, "2");
	TNode * node1_1 = new TNode(While);
	TNode * node1_2 = new TNode(If);
	TNode * node1_3 = new TNode(Assign);
	TNode * node1_1_1 = new TNode(StmtList);
	TNode * node2_1 = new TNode(Var, "y");

	// build tree
	node1_1 -> addChild(node1_1_1);
	node1 -> addChild(node1_1);
	node1 -> addChild(node1_2);
	node1 -> addChild(node1_3);
	node2 -> addChild(node2_1);
	root -> addChild(node1);
	root -> addChild(node2);
	root -> addChild(node3);
	root -> addChild(node4);

	TNode * node = root -> getChildAtIndex(0);
	CPPUNIT_ASSERT(node -> getType()==Procedure);
	TNode * node_1 = node -> getChildAtIndex(1);
	CPPUNIT_ASSERT(node_1 -> getValue()=="");
}

void TNodeTest::testGetNumChildren() {
	// randomize some TNodes for testing
	TNode * root = new TNode(Program);
	TNode * node1 = new TNode(Procedure, "p");
	TNode * node2 = new TNode(StmtList);
	TNode * node3 = new TNode(Var, "x");
	TNode * node4 = new TNode(Const, "2");
	TNode * node1_1 = new TNode(While);
	TNode * node1_2 = new TNode(If);
	TNode * node1_3 = new TNode(Assign);
	TNode * node1_1_1 = new TNode(StmtList);
	TNode * node2_1 = new TNode(Var, "y");

	// build tree
	node1_1 -> addChild(node1_1_1);
	node1 -> addChild(node1_1);
	node1 -> addChild(node1_2);
	node1 -> addChild(node1_3);
	node2 -> addChild(node2_1);
	root -> addChild(node1);
	root -> addChild(node2);
	root -> addChild(node3);
	root -> addChild(node4);

	CPPUNIT_ASSERT_EQUAL(4, root -> getNumChildren());
	CPPUNIT_ASSERT_EQUAL(3, node1 -> getNumChildren());
	CPPUNIT_ASSERT_EQUAL(1, node1_1 -> getNumChildren());
	CPPUNIT_ASSERT_EQUAL(0, node4 -> getNumChildren());
}

void TNodeTest::testAddChild() {
	// randomize some TNodes for testing
	// randomize some TNodes for testing
	TNode * root = new TNode(Program);
	TNode * node1 = new TNode(Procedure, "p");
	TNode * node2 = new TNode(StmtList);
	TNode * node3 = new TNode(Var, "x");
	TNode * node4 = new TNode(Const, "2");
	TNode * node1_1 = new TNode(While);
	TNode * node1_2 = new TNode(If);
	TNode * node1_3 = new TNode(Assign);
	TNode * node1_1_1 = new TNode(StmtList);
	TNode * node2_1 = new TNode(Var, "y");

	// build tree
	node1_1 -> addChild(node1_1_1);
	node1 -> addChild(node1_1);
	node1 -> addChild(node1_2);
	node1 -> addChild(node1_3);
	node2 -> addChild(node2_1);
	root -> addChild(node1);
	root -> addChild(node2);
	root -> addChild(node3);
	root -> addChild(node4);

	// add child 
	TNode * node1_4 = new TNode(Calls);
	node1 -> addChild(node1_4);

	TNode * node = root -> getChildAtIndex(0);
	CPPUNIT_ASSERT_EQUAL(4, node -> getNumChildren());
	TNode * node_1 = node -> getChildAtIndex(3);
	CPPUNIT_ASSERT(node_1 -> getType()==Calls);
}

void TNodeTest::testPrintNode() {
	// randomize some TNodes for testing
	TNode * root = new TNode(Program);
	TNode * node1 = new TNode(Procedure, "p");
	TNode * node2 = new TNode(StmtList);
	TNode * node3 = new TNode(Var, "x");
	TNode * node4 = new TNode(Const, "2");
	TNode * node1_1 = new TNode(While);
	TNode * node1_2 = new TNode(If);
	TNode * node1_3 = new TNode(Assign);
	TNode * node1_1_1 = new TNode(StmtList);
	TNode * node2_1 = new TNode(Var, "y");

	// build tree
	node1_1 -> addChild(node1_1_1);
	node1 -> addChild(node1_1);
	node1 ->addChild(node1_2);
	node1 -> addChild(node1_3);
	node2 -> addChild(node2_1);
	root -> addChild(node1);
	root -> addChild(node2);
	root -> addChild(node3);
	root -> addChild(node4);

	cout <<endl;
	// root.printTNode();
}

void TNodeTest::testSortChildren() {
	TNode * root = populateData();
	root->sortChildrenList();
	root ->printTNode();
}

TNode * TNodeTest::populateData() {
	TNode * root = new TNode();
	TNode * node1 = new TNode(Program, "1");
	TNode * node2 = new TNode(StmtList, "2");
	TNode * node3 = new TNode(While, "3");
	TNode * node4 = new TNode(If, "4");
	TNode * node5 = new TNode(Var, "5");
	TNode * node6 = new TNode(Const, "6");
	TNode * node1_1 = new TNode(Const, "57");
	TNode * node2_1 = new TNode(Const, "23");
	node1->addChild(node1_1); node2->addChild(node2_1);
	root->addChild(node6); root->addChild(node2); root->addChild(node3); 
	root->addChild(node4); root->addChild(node5); root->addChild(node1);
	return root;
}