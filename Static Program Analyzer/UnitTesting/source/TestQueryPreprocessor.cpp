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
	// cout << endl << "TEST BUILD TREE: Query: stmt s1; Select s1" <<endl;
	// root -> printTNode();
}

void QueryPreprocessorTest::testBuildSuchThatCls() {
	QueryPreprocessor qp;
	string query = "procedure p, q; Select p such that Calls*(p, q)";
	QueryRepresentator::reset();
	qp.Preprocess(query);

	Tree tree = QueryRepresentator::getQueryTree(0);
	TNode * root = tree.getRoot();
	/* cout << endl << "TEST BUILD TREE: Query: procedure p, q; Select p such that Calls*(p, q)" <<endl;
	 root -> printTNode();*/
}

void QueryPreprocessorTest::testBuildPatternCls() {
	QueryPreprocessor qp;
	string query = "assign a; Select a pattern a(_,_)";
	QueryRepresentator::reset();
	qp.Preprocess(query);

	Tree tree = QueryRepresentator::getQueryTree(0);
	TNode * root = tree.getRoot();
	// cout << endl << "TEST BUILD TREE: Query: assign a; Select a pattern a(_,_)" <<endl;
	// root -> printTNode();
}

void QueryPreprocessorTest::testBuildWithCls() {
	QueryPreprocessor qp;
	string query = "stmt s; prog_line p; Select BOOLEAN with p = 1";
	QueryRepresentator::reset();
	qp.Preprocess(query);

	Tree tree = QueryRepresentator::getQueryTree(0);
	TNode * root = tree.getRoot();
	/* cout << endl << "TEST BUILD TREE: Query: stmt s, prog_line p; Select BOOLEAN with p = 1" <<endl;
	 root -> printTNode();*/
}

void QueryPreprocessorTest::testBuildTupleResult() {
	QueryPreprocessor qp;
	string query = "assign a1, a2; while w1, w2; Select <a1, a2>";	
	QueryRepresentator::reset();
	qp.Preprocess(query);

	Tree tree = QueryRepresentator::getQueryTree(0);
	TNode * root = tree.getRoot();
	/*cout << endl << "TEST BUILD TREE: assign a1, a2; while w1, w2; Select <a1, a2>" <<endl;
	root -> printTNode();*/
}


void QueryPreprocessorTest::testBuildComplexQuery1() {
	QueryPreprocessor qp;
	string query = "assign a1, a2; while w1, w2; Select a2 pattern a1(\"x\",_) and a2(\"x\",_\"x\"_) such that Affects(a1, a2) and Parent*(w2, a2) and Parent*(w1, w2)";
	QueryRepresentator::reset();
	qp.Preprocess(query);

	Tree tree = QueryRepresentator::getQueryTree(0);
	TNode * root = tree.getRoot();
	/*cout << endl << "TEST BUILD TREE: Query: assign a1, a2; while w1, w2; Select a2 pattern a1(\"x\",_) and a2(\"x\",_\"x\"_) such that Affects(a1, a2) and Parent*(w2, a2) and Parent*(w1, w2)" <<endl;
	root -> printTNode();*/
} 