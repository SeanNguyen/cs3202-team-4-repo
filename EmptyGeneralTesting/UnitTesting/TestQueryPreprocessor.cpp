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
	string query = "stmt s1, s2, s3; variable x, y, s; const this; Select s1";
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
	//TNode root = *tree.getRoot();
	//cout <<endl<< SyntaxHelper::SymbolToString(root.getType()) << endl;
}

void QueryPreprocessorTest::testBuildSuchThatCls() {
}

void QueryPreprocessorTest::testBuildPatternCls() {
}

void QueryPreprocessorTest::testBuildWithCls() {
}