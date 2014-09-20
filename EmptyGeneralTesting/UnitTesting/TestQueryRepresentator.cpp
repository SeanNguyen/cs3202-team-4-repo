#include "TestQueryRepresentator.h"

void QueryRepresentatorTest::setUp() {
}

void QueryRepresentatorTest::tearDown() {
}

void QueryRepresentatorTest::setUpData() {
	QueryRepresentator::reset();
	// create a sample data using those queries:
	// Query 1: stmt s1; Select s1
	// Query 2: stmt s1; var x; Select s1 such that Uses(s1, x)
	// Query 3: stmt s1; while w; Select w such that Parent(w,s1) pattern s1("x",_)
	SymbolTable table1; QueryTree tree1;
	table1.setSymbol(KEYWORD_STMT, "s1");
	TNode *  root1 = new TNode(Select);
	TNode *  n1 = new TNode(ResultCls, "1"); 
	TNode *  n2 = new TNode(QuerySymbol, "s1");
	tree1.setRoot(root1);
	n1 -> addChild(n2); 
	root1 -> addChild(n1);

	SymbolTable table2; QueryTree tree2;
	table2.setSymbol(KEYWORD_STMT, "s1");
	table2.setSymbol(KEYWORD_VAR, "x");
	TNode *  root2 = new TNode(Select);
	TNode *  n3 = new TNode(ResultCls, "1");
	TNode *  n4 = new TNode(QuerySymbol, "s1");
	TNode *  n5 = new TNode(SuchThatCls);
	TNode *  n6 = new TNode(Uses);
	TNode *  n7 = new TNode(QuerySymbol, "s1");
	TNode *  n8 = new TNode(QuerySymbol, "x");
	tree2.setRoot(root2);
	n6 -> addChild(n7); n6 -> addChild(n8); n5 -> addChild(n6);
	n3 -> addChild(n4); root2 -> addChild(n3); root2 -> addChild(n5);

	SymbolTable table3; QueryTree tree3;
	table3.setSymbol(KEYWORD_STMT, "s1");
	table3.setSymbol(KEYWORD_WHILE, "w");
	TNode *  root3 = new TNode(Select);
	TNode *  n9 = new TNode(ResultCls, "1");
	TNode *  n10 = new TNode(QuerySymbol, "w");
	TNode *  n11 = new TNode(SuchThatCls);
	TNode *  n12 = new TNode(Parent);
	TNode *  n13 = new TNode(QuerySymbol, "w");
	TNode *  n14 = new TNode(QuerySymbol, "s1");
	TNode *  n15 = new TNode(PatternCls);
	TNode *  n16 = new TNode(QuerySymbol, "s1");
	TNode *  n17 = new TNode(Var, "x");
	TNode *  n18 = new TNode(Underline);
	n9 -> addChild(n10);
	tree3.setRoot(root3);
	n12-> addChild(n13); n12 -> addChild(n14); n11 -> addChild(n12);
	n15 -> addChild(n16); n15 -> addChild(n17); n15 -> addChild(n18);
	root3 -> addChild(n9); root3 -> addChild(n11); root3 -> addChild(n15);

	QueryRepresentator::addQuery(table1, tree1, true);
	QueryRepresentator::addQuery(table2, tree2, true);
	QueryRepresentator::addQuery(table3, tree3, true); 

}

void QueryRepresentatorTest::testSymbolTable() {
	setUpData();

	CPPUNIT_ASSERT_EQUAL(3, QueryRepresentator::getSize());

	SymbolTable table1 = QueryRepresentator::getSymbolTable(0);
	SymbolTable table2 = QueryRepresentator::getSymbolTable(1);
	SymbolTable table3 = QueryRepresentator::getSymbolTable(2);
	
	CPPUNIT_ASSERT_EQUAL(1, table1.getSize());
	CPPUNIT_ASSERT_EQUAL(KEYWORD_STMT, table1.getType(0));
	CPPUNIT_ASSERT("s1"==table1.getName(0));

	CPPUNIT_ASSERT_EQUAL(2, table2.getSize());
	CPPUNIT_ASSERT_EQUAL(KEYWORD_STMT, table2.getType(0));
	CPPUNIT_ASSERT("s1"==table2.getName(0));
	CPPUNIT_ASSERT_EQUAL(KEYWORD_VAR, table2.getType(1));
	CPPUNIT_ASSERT("x"==table2.getName(1));

	CPPUNIT_ASSERT_EQUAL(2, table3.getSize());
	CPPUNIT_ASSERT_EQUAL(KEYWORD_STMT, table3.getType(0));
	CPPUNIT_ASSERT("s1"==table3.getName(0));
	CPPUNIT_ASSERT_EQUAL(KEYWORD_WHILE, table3.getType(1));
	CPPUNIT_ASSERT("w"==table3.getName(1));
}

void QueryRepresentatorTest::testQueryTree() {
	QueryTree tree1 = QueryRepresentator::getQueryTree(2);
	TNode root1 = *tree1.getRoot();
	//CPPUNIT_ASSERT_EQUAL(1, root1.getNumChildren());
	cout<< endl;
	tree1.printTree();
	cout <<endl;
}

CPPUNIT_TEST_SUITE_REGISTRATION( QueryRepresentatorTest );