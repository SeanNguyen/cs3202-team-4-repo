#include "TestQueryPreprocessor.h"

void QueryPreprocessorTest::setUp() {
}

void QueryPreprocessorTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( QueryPreprocessorTest );

void QueryPreprocessorTest::testReadFileData() {
} 

void QueryPreprocessorTest::testBuildSymbolTable() {
	QueryPreprocessor qp;
	string query = "stmt s1, s2, s3; variable x, y, s; constant this; Select s1";
	qp.Preprocess(query);
	SymbolTable table = QueryRepresentator::getSymbolTable(0);
	CPPUNIT_ASSERT_EQUAL(7, table.getSize());
	CPPUNIT_ASSERT(KEYWORD_STMT==table.getType(0));
	CPPUNIT_ASSERT("s1"==table.getName(0));
}


void QueryPreprocessorTest::testBuildTree() {
	QueryPreprocessor qp;
	string query = "stmt s1; Select s1";
	QueryRepresentator::reset();
	qp.Preprocess(query);
	int size = QueryRepresentator::getSize();
	CPPUNIT_ASSERT_EQUAL(1, size);
	Tree tree = QueryRepresentator::getQueryTree(0);
	TNode * root = tree.getRoot();
	cout << endl << "TEST BUILD TREE: Query: stmt s1; Select s1" <<endl;
	root -> printTNode();
	//cout <<endl<< SyntaxHelper::SymbolToString(root.getType()) << endl;
}

void QueryPreprocessorTest::testBuildSuchThatCls() {
	QueryPreprocessor qp;
	string query = "procedure p, q; Select p such that Calls*(p, q)";
	QueryRepresentator::reset();
	qp.Preprocess(query);

	Tree tree = QueryRepresentator::getQueryTree(0);
	TNode * root = tree.getRoot();
	cout << endl << "TEST BUILD TREE: Query: procedure p, q; Select p such that Calls*(p, q)" <<endl;
	root -> printTNode();
}

void QueryPreprocessorTest::testBuildPatternCls() {
	QueryPreprocessor qp;
	string query = "assign a; Select a pattern a(_,_)";
	QueryRepresentator::reset();
	qp.Preprocess(query);

	Tree tree = QueryRepresentator::getQueryTree(0);
	TNode * root = tree.getRoot();
	cout << endl << "TEST BUILD TREE: Query: assign a; Select a pattern a(_,_)" <<endl;
	root -> printTNode();
}

void QueryPreprocessorTest::testBuildWithCls() {
	QueryPreprocessor qp;
	string query = "procedure p; Select p with p.procName = \"Nothing\"";
	QueryRepresentator::reset();
	qp.Preprocess(query);

	Tree tree = QueryRepresentator::getQueryTree(0);
	TNode * root = tree.getRoot();
	cout << endl << "TEST BUILD TREE: Query: procedure p; Select p with p.procName = \"Nothing\"" <<endl;
	root -> printTNode();
}

void QueryPreprocessorTest::testBuildComplexQuery1() {
	QueryPreprocessor qp;
	string query = "assign s; while w; Select BOOLEAN such that Parent(w, s) pattern s(\"x\", _\"x+y+z\"_)";
	QueryRepresentator::reset();
	qp.Preprocess(query);

	Tree tree = QueryRepresentator::getQueryTree(0);
	TNode * root = tree.getRoot();
	cout << endl << "TEST BUILD TREE: Query: assign s; while w; Select BOOLEAN such that Parent(w, s) pattern s(\"x\", _\"x+y+z\"_)" <<endl;
	root -> printTNode();
} 