#include "TestQueryPreprocessor.h"

void QueryPreprocessorTest::setUp() {
}

void QueryPreprocessorTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( QueryPreprocessorTest );

void QueryPreprocessorTest::testReadFileData() {
} 

void QueryPreprocessorTest::testBuildTree() {
	QueryPreprocessor qp;
	string query = "stmt s1; Select s1";
	qp.Preprocess(query);
	Tree tree = QueryRepresentator::getQueryTree(0);
	// tree.printTree();
}

void QueryPreprocessorTest::testBuildSuchThatCls() {
}

void QueryPreprocessorTest::testBuildPatternCls() {
}

void QueryPreprocessorTest::testBuildWithCls() {
}