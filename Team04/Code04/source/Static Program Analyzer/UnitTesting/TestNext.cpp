//#include <cppunit/config/SourcePrefix.h>
//#include "TestNext.h"
//
//DesignExtractor designextractor;
//
//TestNext::TestNext(void)
//{
//}
//
//
//TestNext::~TestNext(void)
//{
//}
//
//void TestNext::setUp() {	
//	PKB::resetPKB();
//	string source = "..\\..\\Tests\\TestNextSource.txt";
//	
//	Parser parser;
//	parser.parse(source);
//	parser.buildPKB();
//	designextractor.buildPKB();
//}
//
//void TestNext::tearDown() {
//
//}
//
//CPPUNIT_TEST_SUITE_REGISTRATION( TestNext );
//
//void TestNext::TestisNext() {
//
//	CPPUNIT_ASSERT( PKB::isNext(1, 2) );
//	CPPUNIT_ASSERT( PKB::isNext(2, 3) );
//	CPPUNIT_ASSERT( PKB::isNext(2, 5) );
//	CPPUNIT_ASSERT( PKB::isNext(3, 4) );
//	CPPUNIT_ASSERT( PKB::isNext(5, 6) );
//	CPPUNIT_ASSERT( PKB::isNext(6, 7) );
//	CPPUNIT_ASSERT( PKB::isNext(4, 7) );
//	CPPUNIT_ASSERT( PKB::isNext(7, 8) );
//	CPPUNIT_ASSERT( PKB::isNext(8, 9) );
//	CPPUNIT_ASSERT( PKB::isNext(9, 10) );
//	CPPUNIT_ASSERT( PKB::isNext(10, 7) );
//	CPPUNIT_ASSERT( PKB::isNext(7, 11) );
//	CPPUNIT_ASSERT( PKB::isNext(11, 12) );
//}
//
//void TestNext::TestIsNextStar() {
//
//	CPPUNIT_ASSERT( PKB::isNextStar(1, 4) );
//	CPPUNIT_ASSERT( PKB::isNextStar(1, 5) );
//	CPPUNIT_ASSERT( PKB::isNextStar(1, 11) );
//	CPPUNIT_ASSERT( PKB::isNextStar(1, 12) );
//	CPPUNIT_ASSERT( PKB::isNextStar(1, 7) );
//	CPPUNIT_ASSERT( PKB::isNextStar(1, 10) );
//	CPPUNIT_ASSERT( PKB::isNextStar(1, 3) );
//	CPPUNIT_ASSERT( PKB::isNextStar(1, 6) );						
//	CPPUNIT_ASSERT( PKB::isNextStar(1, 9) );	
//	
//	CPPUNIT_ASSERT( PKB::isNextStar(2, 4) );
//	CPPUNIT_ASSERT( PKB::isNextStar(2, 5) );
//	CPPUNIT_ASSERT( PKB::isNextStar(2, 11) );
//	CPPUNIT_ASSERT( PKB::isNextStar(2, 12) );
//	CPPUNIT_ASSERT( PKB::isNextStar(2, 7) );
//	CPPUNIT_ASSERT( PKB::isNextStar(2, 10) );
//	CPPUNIT_ASSERT( PKB::isNextStar(2, 3) );
//	CPPUNIT_ASSERT( PKB::isNextStar(2, 6) );						
//	CPPUNIT_ASSERT( PKB::isNextStar(2, 9) );						
//	
//	CPPUNIT_ASSERT( PKB::isNextStar(3, 4) );
//	CPPUNIT_ASSERT( PKB::isNextStar(3, 7) );
//	CPPUNIT_ASSERT( PKB::isNextStar(3, 11) );
//	CPPUNIT_ASSERT( PKB::isNextStar(3, 12) );
//	CPPUNIT_ASSERT( PKB::isNextStar(3, 10) );
//	CPPUNIT_ASSERT( PKB::isNextStar(3, 9) );	
//
//	CPPUNIT_ASSERT( PKB::isNextStar(5, 6) );
//	CPPUNIT_ASSERT( PKB::isNextStar(5, 11) );
//	CPPUNIT_ASSERT( PKB::isNextStar(5, 12) );
//	CPPUNIT_ASSERT( PKB::isNextStar(5, 7) );
//	CPPUNIT_ASSERT( PKB::isNextStar(5, 10) );
//	CPPUNIT_ASSERT( PKB::isNextStar(5, 9) );						
//
//	CPPUNIT_ASSERT( PKB::isNextStar(6, 11) );
//	CPPUNIT_ASSERT( PKB::isNextStar(6, 12) );
//	CPPUNIT_ASSERT( PKB::isNextStar(6, 7) );
//	CPPUNIT_ASSERT( PKB::isNextStar(6, 10) );
//	CPPUNIT_ASSERT( PKB::isNextStar(6, 9) );						
//
//	CPPUNIT_ASSERT( PKB::isNextStar(7, 8) );
//	CPPUNIT_ASSERT( PKB::isNextStar(7, 9) );
//	CPPUNIT_ASSERT( PKB::isNextStar(7, 10) );
//	CPPUNIT_ASSERT( PKB::isNextStar(7, 11) );
//	CPPUNIT_ASSERT( PKB::isNextStar(7, 12) );
//
//	CPPUNIT_ASSERT( PKB::isNextStar(9, 10) );
//	CPPUNIT_ASSERT( PKB::isNextStar(9, 8) );
//	CPPUNIT_ASSERT( PKB::isNextStar(9, 7) );
//	CPPUNIT_ASSERT( PKB::isNextStar(9, 11) );
//	CPPUNIT_ASSERT( PKB::isNextStar(9, 9) );
//	CPPUNIT_ASSERT( PKB::isNextStar(9, 12) );
//}
//
//void TestNext::TestgetNextStmts() {
//
//	int stmts[] = {2};
//	vector<int> nextstmts(stmts, stmts + sizeof(stmts) / sizeof(int) );
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(0), (PKB::getNextStmts(1)).at(0));
//
//	int stmts2[] = {3, 5, 7};
//	vector<int> nextstmts2(stmts2, stmts2 + sizeof(stmts2) / sizeof(int) );
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(0), (PKB::getNextStmts(2)).at(0));
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(1), (PKB::getNextStmts(2)).at(1));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts2.at(2), (PKB::getNextStmts(2)).at(2));
//
//	int stmts4[] = {4};
//	vector<int> nextstmts4(stmts4, stmts4 + sizeof(stmts4) / sizeof(int) );
//	CPPUNIT_ASSERT_EQUAL(nextstmts4.at(0), (PKB::getNextStmts(3)).at(0));
//
//	int stmts3[] = {8, 11};
//	vector<int> nextstmts3(stmts3, stmts3 + sizeof(stmts3) / sizeof(int) );
//	CPPUNIT_ASSERT_EQUAL(nextstmts3.at(0), (PKB::getNextStmts(7)).at(0));
//	CPPUNIT_ASSERT_EQUAL(nextstmts3.at(1), (PKB::getNextStmts(7)).at(1));
//}
//
//void TestNext::TestgetPreviousStmts() {
//
//	int stmts[] = {2};
//	vector<int> prevstmts(stmts, stmts + sizeof(stmts) / sizeof(int) );
//	CPPUNIT_ASSERT_EQUAL(prevstmts.at(0), (PKB::getPreviousStmts(3)).at(0));
//
//	int stmts5[] = {2};
//	vector<int> prevstmts5(stmts5, stmts5 + sizeof(stmts5) / sizeof(int) );
//	CPPUNIT_ASSERT_EQUAL(prevstmts5.at(0), (PKB::getPreviousStmts(5)).at(0));
//
//	int stmts2[] = {4, 6, 10};
//	vector<int> prevstmts2(stmts2, stmts2 + sizeof(stmts2) / sizeof(int) );
//	CPPUNIT_ASSERT_EQUAL(prevstmts2.at(0), (PKB::getPreviousStmts(7)).at(0));
//	CPPUNIT_ASSERT_EQUAL(prevstmts2.at(1), (PKB::getPreviousStmts(7)).at(1));
//	CPPUNIT_ASSERT_EQUAL(prevstmts2.at(2), (PKB::getPreviousStmts(7)).at(2));
//
//	int stmts4[] = {9};
//	vector<int> prevstmts4(stmts4, stmts4 + sizeof(stmts4) / sizeof(int) );
//	CPPUNIT_ASSERT_EQUAL(prevstmts4.at(0), (PKB::getPreviousStmts(10)).at(0));
//
//	int stmts3[] = {7};
//	vector<int> prevstmts3(stmts3, stmts3 + sizeof(stmts3) / sizeof(int) );
//	CPPUNIT_ASSERT_EQUAL(prevstmts3.at(0), (PKB::getPreviousStmts(11)).at(0));
//
//	int stmts6[] = {11};
//	vector<int> prevstmts6(stmts6, stmts6 + sizeof(stmts6) / sizeof(int) );
//	CPPUNIT_ASSERT_EQUAL(prevstmts6.at(0), (PKB::getPreviousStmts(12)).at(0));
//}
//
//void TestNext::TestgetPreviousStarStmts() {
//	int stmts[] = {1,2,3,4,5,6,7,8,9,10,11};
//	vector<int> nextstmts(stmts, stmts + sizeof(stmts) / sizeof(int) );
//	vector<int> prevstarstmts = PKB::getPreviousStarStmts(12);
//	sort(prevstarstmts.begin(), prevstarstmts.end());
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(0), prevstarstmts.at(0));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(1), prevstarstmts.at(1));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(2), prevstarstmts.at(2));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(3), prevstarstmts.at(3));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(4), prevstarstmts.at(4));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(5), prevstarstmts.at(5));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(6), prevstarstmts.at(6));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(7), prevstarstmts.at(7));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(8), prevstarstmts.at(8));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(9), prevstarstmts.at(9));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(10), prevstarstmts.at(10));
//
//	int stmts2[] = {1,2,3,4,5,6,7};
//	vector<int> prevstmts2(stmts2, stmts2 + sizeof(stmts2) / sizeof(int) );
//	prevstarstmts = PKB::getPreviousStarStmts(7);
//	sort(prevstarstmts.begin(), prevstarstmts.end());
//	CPPUNIT_ASSERT_EQUAL(prevstmts2.at(0), prevstarstmts.at(0));
//	CPPUNIT_ASSERT_EQUAL(prevstmts2.at(1), prevstarstmts.at(1));
//	CPPUNIT_ASSERT_EQUAL(prevstmts2.at(2), prevstarstmts.at(2));
//	CPPUNIT_ASSERT_EQUAL(prevstmts2.at(3), prevstarstmts.at(3));
//	CPPUNIT_ASSERT_EQUAL(prevstmts2.at(4), prevstarstmts.at(4));
//	CPPUNIT_ASSERT_EQUAL(prevstmts2.at(5), prevstarstmts.at(5));
//	CPPUNIT_ASSERT_EQUAL(prevstmts2.at(6), prevstarstmts.at(6));
//
//	//int stmts4[] = {4,7,8,9,10,11,12};
//	//vector<int> nextstmts4(stmts4, stmts4 + sizeof(stmts4) / sizeof(int) );
//	//nextstarstmts = PKB::getNextStarStmts(3);
//	//sort(nextstarstmts.begin(), nextstarstmts.end());
//	//CPPUNIT_ASSERT_EQUAL(nextstmts4.at(0), nextstarstmts.at(0));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts4.at(1), nextstarstmts.at(1));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts4.at(2), nextstarstmts.at(2));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts4.at(3), nextstarstmts.at(3));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts4.at(4), nextstarstmts.at(4));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts4.at(5), nextstarstmts.at(5));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts4.at(6), nextstarstmts.at(6));
//
//	//int stmts3[] = {6,7,8,9,10,11,12};
//	//vector<int> nextstmts3(stmts3, stmts3 + sizeof(stmts3) / sizeof(int) );
//	//nextstarstmts = PKB::getNextStarStmts(5);
//	//sort(nextstarstmts.begin(), nextstarstmts.end());
//	//CPPUNIT_ASSERT_EQUAL(nextstmts3.at(0), nextstarstmts.at(0));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts3.at(1), nextstarstmts.at(1));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts3.at(2), nextstarstmts.at(2));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts3.at(3), nextstarstmts.at(3));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts3.at(4), nextstarstmts.at(4));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts3.at(5), nextstarstmts.at(5));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts3.at(6), nextstarstmts.at(6));
//
//	//int stmts5[] = {7,8,9,10,11,12};
//	//vector<int> nextstmts5(stmts5, stmts5 + sizeof(stmts5) / sizeof(int) );
//	//nextstarstmts = PKB::getNextStarStmts(7);
//	//sort(nextstarstmts.begin(), nextstarstmts.end());
//	//CPPUNIT_ASSERT_EQUAL(nextstmts5.at(0), nextstarstmts.at(0));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts5.at(1), nextstarstmts.at(1));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts5.at(2), nextstarstmts.at(2));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts5.at(3), nextstarstmts.at(3));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts5.at(4), nextstarstmts.at(4));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts5.at(5), nextstarstmts.at(5));
//
//	//int stmts6[] = {7,8,9,10,11,12};
//	//vector<int> nextstmts6(stmts6, stmts6 + sizeof(stmts6) / sizeof(int) );
//	//nextstarstmts = PKB::getNextStarStmts(10);
//	//sort(nextstarstmts.begin(), nextstarstmts.end());
//	//CPPUNIT_ASSERT_EQUAL(nextstmts6.at(0), nextstarstmts.at(0));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts6.at(1), nextstarstmts.at(1));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts6.at(2), nextstarstmts.at(2));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts6.at(3), nextstarstmts.at(3));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts6.at(4), nextstarstmts.at(4));
//	//CPPUNIT_ASSERT_EQUAL(nextstmts6.at(5), nextstarstmts.at(5));
//
//	//int stmts7[] = {12};
//	//vector<int> nextstmts7(stmts7, stmts7 + sizeof(stmts7) / sizeof(int) );
//	//nextstarstmts = PKB::getNextStarStmts(11);
//	//sort(nextstarstmts.begin(), nextstarstmts.end());
//	//CPPUNIT_ASSERT_EQUAL(nextstmts7.at(0), nextstarstmts.at(0));
//}
//
//void TestNext::TestgetNextStarStmts() {
//
//	int stmts[] = {2,3,4,5,6,7,8,9,10,11,12};
//	vector<int> nextstmts(stmts, stmts + sizeof(stmts) / sizeof(int) );
//	vector<int> nextstarstmts = PKB::getNextStarStmts(1);
//	sort(nextstarstmts.begin(), nextstarstmts.end());
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(0), nextstarstmts.at(0));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(1), nextstarstmts.at(1));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(2), nextstarstmts.at(2));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(3), nextstarstmts.at(3));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(4), nextstarstmts.at(4));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(5), nextstarstmts.at(5));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(6), nextstarstmts.at(6));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(7), nextstarstmts.at(7));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(8), nextstarstmts.at(8));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(9), nextstarstmts.at(9));
//	CPPUNIT_ASSERT_EQUAL(nextstmts.at(10), nextstarstmts.at(10));
//
//	int stmts2[] = {3,4,5,6,7,8,9,10,11,12};
//	vector<int> nextstmts2(stmts2, stmts2 + sizeof(stmts2) / sizeof(int) );
//	nextstarstmts = PKB::getNextStarStmts(2);
//	sort(nextstarstmts.begin(), nextstarstmts.end());
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(0), nextstarstmts.at(0));
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(1), nextstarstmts.at(1));
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(2), nextstarstmts.at(2));
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(3), nextstarstmts.at(3));
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(4), nextstarstmts.at(4));
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(5), nextstarstmts.at(5));
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(6), nextstarstmts.at(6));
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(7), nextstarstmts.at(7));
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(8), nextstarstmts.at(8));
//	CPPUNIT_ASSERT_EQUAL(nextstmts2.at(9), nextstarstmts.at(9));
//
//	int stmts4[] = {4,7,8,9,10,11,12};
//	vector<int> nextstmts4(stmts4, stmts4 + sizeof(stmts4) / sizeof(int) );
//	nextstarstmts = PKB::getNextStarStmts(3);
//	sort(nextstarstmts.begin(), nextstarstmts.end());
//	CPPUNIT_ASSERT_EQUAL(nextstmts4.at(0), nextstarstmts.at(0));
//	CPPUNIT_ASSERT_EQUAL(nextstmts4.at(1), nextstarstmts.at(1));
//	CPPUNIT_ASSERT_EQUAL(nextstmts4.at(2), nextstarstmts.at(2));
//	CPPUNIT_ASSERT_EQUAL(nextstmts4.at(3), nextstarstmts.at(3));
//	CPPUNIT_ASSERT_EQUAL(nextstmts4.at(4), nextstarstmts.at(4));
//	CPPUNIT_ASSERT_EQUAL(nextstmts4.at(5), nextstarstmts.at(5));
//	CPPUNIT_ASSERT_EQUAL(nextstmts4.at(6), nextstarstmts.at(6));
//
//	int stmts3[] = {6,7,8,9,10,11,12};
//	vector<int> nextstmts3(stmts3, stmts3 + sizeof(stmts3) / sizeof(int) );
//	nextstarstmts = PKB::getNextStarStmts(5);
//	sort(nextstarstmts.begin(), nextstarstmts.end());
//	CPPUNIT_ASSERT_EQUAL(nextstmts3.at(0), nextstarstmts.at(0));
//	CPPUNIT_ASSERT_EQUAL(nextstmts3.at(1), nextstarstmts.at(1));
//	CPPUNIT_ASSERT_EQUAL(nextstmts3.at(2), nextstarstmts.at(2));
//	CPPUNIT_ASSERT_EQUAL(nextstmts3.at(3), nextstarstmts.at(3));
//	CPPUNIT_ASSERT_EQUAL(nextstmts3.at(4), nextstarstmts.at(4));
//	CPPUNIT_ASSERT_EQUAL(nextstmts3.at(5), nextstarstmts.at(5));
//	CPPUNIT_ASSERT_EQUAL(nextstmts3.at(6), nextstarstmts.at(6));
//
//	int stmts5[] = {7,8,9,10,11,12};
//	vector<int> nextstmts5(stmts5, stmts5 + sizeof(stmts5) / sizeof(int) );
//	nextstarstmts = PKB::getNextStarStmts(7);
//	sort(nextstarstmts.begin(), nextstarstmts.end());
//	CPPUNIT_ASSERT_EQUAL(nextstmts5.at(0), nextstarstmts.at(0));
//	CPPUNIT_ASSERT_EQUAL(nextstmts5.at(1), nextstarstmts.at(1));
//	CPPUNIT_ASSERT_EQUAL(nextstmts5.at(2), nextstarstmts.at(2));
//	CPPUNIT_ASSERT_EQUAL(nextstmts5.at(3), nextstarstmts.at(3));
//	CPPUNIT_ASSERT_EQUAL(nextstmts5.at(4), nextstarstmts.at(4));
//	CPPUNIT_ASSERT_EQUAL(nextstmts5.at(5), nextstarstmts.at(5));
//
//	int stmts6[] = {7,8,9,10,11,12};
//	vector<int> nextstmts6(stmts6, stmts6 + sizeof(stmts6) / sizeof(int) );
//	nextstarstmts = PKB::getNextStarStmts(10);
//	sort(nextstarstmts.begin(), nextstarstmts.end());
//	CPPUNIT_ASSERT_EQUAL(nextstmts6.at(0), nextstarstmts.at(0));
//	CPPUNIT_ASSERT_EQUAL(nextstmts6.at(1), nextstarstmts.at(1));
//	CPPUNIT_ASSERT_EQUAL(nextstmts6.at(2), nextstarstmts.at(2));
//	CPPUNIT_ASSERT_EQUAL(nextstmts6.at(3), nextstarstmts.at(3));
//	CPPUNIT_ASSERT_EQUAL(nextstmts6.at(4), nextstarstmts.at(4));
//	CPPUNIT_ASSERT_EQUAL(nextstmts6.at(5), nextstarstmts.at(5));
//
//	int stmts7[] = {12};
//	vector<int> nextstmts7(stmts7, stmts7 + sizeof(stmts7) / sizeof(int) );
//	nextstarstmts = PKB::getNextStarStmts(11);
//	sort(nextstarstmts.begin(), nextstarstmts.end());
//	CPPUNIT_ASSERT_EQUAL(nextstmts7.at(0), nextstarstmts.at(0));
//}