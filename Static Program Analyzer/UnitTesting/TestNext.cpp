#include <cppunit/config/SourcePrefix.h>
#include "TestNext.h"

TestNext::TestNext(void)
{
}


TestNext::~TestNext(void)
{
}

void TestNext::setUp() {	
	PKB::resetPKB();
}

void TestNext::tearDown() {

}

CPPUNIT_TEST_SUITE_REGISTRATION( TestNext );

void TestNext::TestisNext() {
	string source = "..\\..\\Tests\\TestNextSource.txt";
	Parser parser;
	PKB pkb;
	DesignExtractor designextractor;
	
	parser.parse(source);
	parser.buildPKB();
//	designextractor.buildPKB();

	CPPUNIT_ASSERT( pkb.isNext(1, 2) );
	CPPUNIT_ASSERT( pkb.isNext(2, 3) );
	CPPUNIT_ASSERT( pkb.isNext(2, 5) );
	CPPUNIT_ASSERT( pkb.isNext(3, 4) );
	CPPUNIT_ASSERT( pkb.isNext(5, 6) );
	CPPUNIT_ASSERT( pkb.isNext(6, 7) );
	CPPUNIT_ASSERT( pkb.isNext(4, 7) );
	CPPUNIT_ASSERT( pkb.isNext(7, 8) );
	CPPUNIT_ASSERT( pkb.isNext(8, 9) );
	CPPUNIT_ASSERT( pkb.isNext(9, 10) );
	CPPUNIT_ASSERT( pkb.isNext(10, 7) );
	CPPUNIT_ASSERT( pkb.isNext(7, 11) );
	CPPUNIT_ASSERT( pkb.isNext(11, 12) );
}

void TestNext::TestIsNextStar() {
	string source = "..\\..\\Tests\\TestNextSource.txt";
	Parser parser;
	PKB pkb;
	DesignExtractor designextractor;
	
	parser.parse(source);
	parser.buildPKB();
//	designextractor.buildPKB();

	CPPUNIT_ASSERT( pkb.isNextStar(1, 4) );
	CPPUNIT_ASSERT( pkb.isNextStar(1, 5) );
	CPPUNIT_ASSERT( pkb.isNextStar(1, 11) );
	CPPUNIT_ASSERT( pkb.isNextStar(1, 12) );
	CPPUNIT_ASSERT( pkb.isNextStar(1, 7) );
	CPPUNIT_ASSERT( pkb.isNextStar(1, 10) );
	CPPUNIT_ASSERT( pkb.isNextStar(1, 3) );
	CPPUNIT_ASSERT( pkb.isNextStar(1, 6) );						
	CPPUNIT_ASSERT( pkb.isNextStar(1, 9) );	
	
	CPPUNIT_ASSERT( pkb.isNextStar(2, 4) );
	CPPUNIT_ASSERT( pkb.isNextStar(2, 5) );
	CPPUNIT_ASSERT( pkb.isNextStar(2, 11) );
	CPPUNIT_ASSERT( pkb.isNextStar(2, 12) );
	CPPUNIT_ASSERT( pkb.isNextStar(2, 7) );
	CPPUNIT_ASSERT( pkb.isNextStar(2, 10) );
	CPPUNIT_ASSERT( pkb.isNextStar(2, 3) );
	CPPUNIT_ASSERT( pkb.isNextStar(2, 6) );						
	CPPUNIT_ASSERT( pkb.isNextStar(2, 9) );						
	
	CPPUNIT_ASSERT( pkb.isNextStar(3, 4) );
	CPPUNIT_ASSERT( pkb.isNextStar(3, 7) );
	CPPUNIT_ASSERT( pkb.isNextStar(3, 11) );
	CPPUNIT_ASSERT( pkb.isNextStar(3, 12) );
	CPPUNIT_ASSERT( pkb.isNextStar(3, 10) );
	CPPUNIT_ASSERT( pkb.isNextStar(3, 9) );	

	CPPUNIT_ASSERT( pkb.isNextStar(5, 6) );
	CPPUNIT_ASSERT( pkb.isNextStar(5, 11) );
	CPPUNIT_ASSERT( pkb.isNextStar(5, 12) );
	CPPUNIT_ASSERT( pkb.isNextStar(5, 7) );
	CPPUNIT_ASSERT( pkb.isNextStar(5, 10) );
	CPPUNIT_ASSERT( pkb.isNextStar(5, 9) );						

	CPPUNIT_ASSERT( pkb.isNextStar(6, 11) );
	CPPUNIT_ASSERT( pkb.isNextStar(6, 12) );
	CPPUNIT_ASSERT( pkb.isNextStar(6, 7) );
	CPPUNIT_ASSERT( pkb.isNextStar(6, 10) );
	CPPUNIT_ASSERT( pkb.isNextStar(6, 9) );						

	CPPUNIT_ASSERT( pkb.isNextStar(7, 8) );
	CPPUNIT_ASSERT( pkb.isNextStar(7, 9) );
	CPPUNIT_ASSERT( pkb.isNextStar(7, 10) );
	CPPUNIT_ASSERT( pkb.isNextStar(7, 11) );
	CPPUNIT_ASSERT( pkb.isNextStar(7, 12) );

	CPPUNIT_ASSERT( pkb.isNextStar(9, 10) );
	CPPUNIT_ASSERT( pkb.isNextStar(9, 8) );
	CPPUNIT_ASSERT( pkb.isNextStar(9, 7) );
	CPPUNIT_ASSERT( pkb.isNextStar(9, 11) );
	CPPUNIT_ASSERT( pkb.isNextStar(9, 9) );
	CPPUNIT_ASSERT( pkb.isNextStar(9, 12) );
}

void TestNext::TestgetNextStmts() {
	string source = "..\\..\\Tests\\TestNextSource.txt";
	Parser parser;
	PKB pkb;
	DesignExtractor designextractor;
	
	parser.parse(source);
	parser.buildPKB();
//	designextractor.buildPKB();

	int stmts[] = {2};
	vector<int> nextstmts(stmts, stmts + sizeof(stmts) / sizeof(int) );
	//sort(expectedvars.begin(), nextstmts.end()); 
	CPPUNIT_ASSERT_EQUAL(nextstmts.at(0), (pkb.getNextStmts(1)).at(0));
	//CPPUNIT_ASSERT_EQUAL(nextstmts.at(1), (pkb.getNextStmts(1)).at(1));

	int stmts2[] = {3, 5};
	vector<int> nextstmts2(stmts2, stmts2 + sizeof(stmts2) / sizeof(int) );
	//sort(expectedvars.begin(), nextstmts.end()); 
	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(0), (pkb.getNextStmts(2)).at(0));

}

void TestNext::TestgetPreviousStmts() {

}

void TestNext::TestgetPreviousStarStmts() {
	
}

void TestNext::TestgetNextStarStmts() {
	
}