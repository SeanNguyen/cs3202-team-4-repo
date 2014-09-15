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
	QueryRepresentator::reset();
	qp.Preprocess(query);
	//int size = QueryRepresentator::getSize();
	//CPPUNIT_ASSERT_EQUAL(1, size);
	//Tree tree = QueryRepresentator::getQueryTree(0);
	//TNode root = *tree.getRoot();
	//cout << root.getType() << endl;
}

void QueryPreprocessorTest::testBuildSuchThatCls() {
}

void QueryPreprocessorTest::testBuildPatternCls() {
}

void QueryPreprocessorTest::testBuildWithCls() {
}