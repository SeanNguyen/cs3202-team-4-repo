//#include <cppunit/config/SourcePrefix.h>
//#include "SystemTest2.h"
//
//void SystemTest2::setUp() {
//	PKB::resetPKB();
//}
//
//void SystemTest2::tearDown() {
//}
//
//CPPUNIT_TEST_SUITE_REGISTRATION( SystemTest2 );
//
//void SystemTest2::processModify() {
//	string source = "..\\..\\Tests\\TestDesignExtractorSource.txt";
//	Parser parser;
//	PKB pkb;
//	DesignExtractor designextractor;
//	
//	parser.parse(source);
//	parser.buildPKB();
//	designextractor.buildPKB();
//
//	int A = pkb.getProcIndex("A").at(0);
//	int B = pkb.getProcIndex("B").at(0);
//	int C = pkb.getProcIndex("C").at(0);
//	int D = pkb.getProcIndex("D").at(0);
//	int E = pkb.getProcIndex("E").at(0);
//
//	int x = pkb.getVarIndex("x");
//	int a = pkb.getVarIndex("a");
//	int c = pkb.getVarIndex("c");
//	int k = pkb.getVarIndex("k");
//	int loops = pkb.getVarIndex("loops");
//	int j = pkb.getVarIndex("j");
//	int b = pkb.getVarIndex("b");
//	int fruit = pkb.getVarIndex("fruit");
//
//	CPPUNIT_ASSERT(pkb.isCalls(C, D));
//	CPPUNIT_ASSERT(pkb.isCalls(A, B));
//	CPPUNIT_ASSERT(pkb.isCalls(C, E));
//	CPPUNIT_ASSERT(pkb.isCalls(B, C));
//
//	CPPUNIT_ASSERT(pkb.isCallStar(A, B));
//	CPPUNIT_ASSERT(pkb.isCallStar(A, C));
//	CPPUNIT_ASSERT(pkb.isCallStar(A, D));
//	CPPUNIT_ASSERT(pkb.isCallStar(A, E));
//
//	vector<int> modifiedvars = pkb.getModifiedVarAtProc(A);
//	sort(modifiedvars.begin(), modifiedvars.end());
//	int vars[] = {x, a, c, k, loops, j, b, fruit};
//	vector<int> expectedvars(vars, vars + sizeof(vars) / sizeof(int) );
//	sort(expectedvars.begin(), expectedvars.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(0), modifiedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(1), modifiedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(2), modifiedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(3), modifiedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(4), modifiedvars.at(4));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(5), modifiedvars.at(5));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(6), modifiedvars.at(6));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(7), modifiedvars.at(7));
//
//	modifiedvars = pkb.getModifiedVarAtProc(B);
//	sort(modifiedvars.begin(), modifiedvars.end());
//	int vars2[] = {a, c, loops, j, b, fruit};
//	vector<int> expectedvars2(vars2, vars2 + sizeof(vars2) / sizeof(int) );
//	sort(expectedvars2.begin(), expectedvars2.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(0), modifiedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(1), modifiedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(2), modifiedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(3), modifiedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(4), modifiedvars.at(4));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(5), modifiedvars.at(5));
//
//	modifiedvars = pkb.getModifiedVarAtProc(C);
//	sort(modifiedvars.begin(), modifiedvars.end());
//	int vars3[] = {loops, j, b, fruit};
//	vector<int> expectedvars3(vars3, vars3 + sizeof(vars3) / sizeof(int) );
//	sort(expectedvars3.begin(), expectedvars3.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars3.at(0), modifiedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars3.at(1), modifiedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars3.at(2), modifiedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars3.at(3), modifiedvars.at(3));
//}
//
//void SystemTest2::processUses() {
//	string source = "..\\..\\Tests\\TestDesignExtractorSource.txt";
//	Parser parser;
//	PKB pkb;
//	DesignExtractor designextractor;
//	
//	parser.parse(source);
//	parser.buildPKB();
//	designextractor.buildPKB();
//
//	int A = pkb.getProcIndex("A").at(0);
//	int B = pkb.getProcIndex("B").at(0);
//	int C = pkb.getProcIndex("C").at(0);
//	int D = pkb.getProcIndex("D").at(0);
//	int E = pkb.getProcIndex("E").at(0);
//
//	int x = pkb.getVarIndex("x");
//	int a = pkb.getVarIndex("a");
//	int w = pkb.getVarIndex("w");
//	int c = pkb.getVarIndex("c");
//	int b = pkb.getVarIndex("b");
//	int k = pkb.getVarIndex("k");
//	int loops = pkb.getVarIndex("loops");
//	int newvar = pkb.getVarIndex("new");
//	int yes = pkb.getVarIndex("yes");
//
//	vector<int> usedvars = pkb.getUsedVarAtProc(A);
//	sort(usedvars.begin(), usedvars.end());
//	int vars[] = {x, a, w, c, b, k, loops, newvar, yes};
//	vector<int> expectedvars(vars, vars + sizeof(vars) / sizeof(int) );
//	sort(expectedvars.begin(), expectedvars.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(0), usedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(1), usedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(2), usedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(3), usedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(4), usedvars.at(4));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(5), usedvars.at(5));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(6), usedvars.at(6));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(7), usedvars.at(7));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(8), usedvars.at(8));
//
//	usedvars = pkb.getUsedVarAtProc(B);
//	sort(usedvars.begin(), usedvars.end());
//	int vars2[] = { a, c, b, k, loops, newvar, yes};
//	vector<int> expectedvars2(vars2, vars2 + sizeof(vars2) / sizeof(int) );
//	sort(expectedvars2.begin(), expectedvars2.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(0), usedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(1), usedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(2), usedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(3), usedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(4), usedvars.at(4));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(5), usedvars.at(5));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(6), usedvars.at(6));
//
//	usedvars = pkb.getUsedVarAtProc(C);
//	sort(usedvars.begin(), usedvars.end());
//	int vars3[] = { a, c, k, loops, yes};
//	vector<int> expectedvars3(vars3, vars3 + sizeof(vars3) / sizeof(int) );
//	sort(expectedvars3.begin(), expectedvars3.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars3.at(0), usedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars3.at(1), usedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars3.at(2), usedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars3.at(3), usedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars3.at(4), usedvars.at(4));
//}
//
//void SystemTest2::processModifyLoopProc() {
//	string source = "..\\..\\Tests\\TestDesignExtractorSource2.txt";
//	Parser parser;
//	PKB pkb;
//	DesignExtractor designextractor;
//	
//	parser.parse(source);
//	parser.buildPKB();
//	designextractor.buildPKB();
//
//	int A = pkb.getProcIndex("A").at(0);
//	int B = pkb.getProcIndex("B").at(0);
//	int C = pkb.getProcIndex("C").at(0);
//	int D = pkb.getProcIndex("D").at(0);
//
//	int x = pkb.getVarIndex("x");
//	int a = pkb.getVarIndex("a");
//	int c = pkb.getVarIndex("c");
//	int k = pkb.getVarIndex("k");
//	int loops = pkb.getVarIndex("loops");
//	int j = pkb.getVarIndex("j");
//	int b = pkb.getVarIndex("b");
//	int fruit = pkb.getVarIndex("fruit");
//
//	CPPUNIT_ASSERT(pkb.isCalls(C, D));
//	CPPUNIT_ASSERT(pkb.isCalls(A, B));
//	CPPUNIT_ASSERT(pkb.isCalls(B, C));
//	CPPUNIT_ASSERT(pkb.isCalls(C, A));
//
//	CPPUNIT_ASSERT(pkb.isCallStar(A, B));
//	CPPUNIT_ASSERT(pkb.isCallStar(A, A));
//	CPPUNIT_ASSERT(pkb.isCallStar(A, D));
//	CPPUNIT_ASSERT(pkb.isCallStar(B, A));
//
//	vector<int> modifiedvars = pkb.getModifiedVarAtProc(A);
//	sort(modifiedvars.begin(), modifiedvars.end());
//	int vars[] = {x, a, c, k, loops, j, b, fruit};
//	vector<int> expectedvars(vars, vars + sizeof(vars) / sizeof(int) );
//	sort(expectedvars.begin(), expectedvars.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(0), modifiedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(1), modifiedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(2), modifiedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(3), modifiedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(4), modifiedvars.at(4));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(5), modifiedvars.at(5));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(6), modifiedvars.at(6));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(7), modifiedvars.at(7));
//
//	modifiedvars = pkb.getModifiedVarAtProc(B);
//	sort(modifiedvars.begin(), modifiedvars.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(0), modifiedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(1), modifiedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(2), modifiedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(3), modifiedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(4), modifiedvars.at(4));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(5), modifiedvars.at(5));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(6), modifiedvars.at(6));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(7), modifiedvars.at(7));
//
//	modifiedvars = pkb.getModifiedVarAtProc(C);
//	sort(modifiedvars.begin(), modifiedvars.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(0), modifiedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(1), modifiedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(2), modifiedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(3), modifiedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(4), modifiedvars.at(4));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(5), modifiedvars.at(5));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(6), modifiedvars.at(6));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(7), modifiedvars.at(7));
//
//	modifiedvars = pkb.getModifiedVarAtProc(D);
//	sort(modifiedvars.begin(), modifiedvars.end());
//	int vars2[] = {b, fruit};
//	vector<int> expectedvars2(vars2, vars2 + sizeof(vars2) / sizeof(int) );
//	sort(expectedvars2.begin(), expectedvars2.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(0), modifiedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars2.at(1), modifiedvars.at(1));
//}
//
//void SystemTest2::processUsesLoopProc() {
//	string source = "..\\..\\Tests\\TestDesignExtractorSource2.txt";
//	Parser parser;
//	PKB pkb;
//	DesignExtractor designextractor;
//	
//	parser.parse(source);
//	parser.buildPKB();
//	designextractor.buildPKB();
//
//	int A = pkb.getProcIndex("A").at(0);
//	int B = pkb.getProcIndex("B").at(0);
//	int C = pkb.getProcIndex("C").at(0);
//	int D = pkb.getProcIndex("D").at(0);
//
//	int x = pkb.getVarIndex("x");
//	int a = pkb.getVarIndex("a");
//	int w = pkb.getVarIndex("w");
//	int c = pkb.getVarIndex("c");
//	int b = pkb.getVarIndex("b");
//	int k = pkb.getVarIndex("k");
//	int loops = pkb.getVarIndex("loops");
//	int newvar = pkb.getVarIndex("new");
//	int yes = pkb.getVarIndex("yes");
//
//	vector<int> usedvars = pkb.getUsedVarAtProc(A);
//	sort(usedvars.begin(), usedvars.end());
//	int vars[] = {x, a, w, c, b, k, loops, newvar, yes};
//	vector<int> expectedvars(vars, vars + sizeof(vars) / sizeof(int) );
//	sort(expectedvars.begin(), expectedvars.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(0), usedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(1), usedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(2), usedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(3), usedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(4), usedvars.at(4));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(5), usedvars.at(5));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(6), usedvars.at(6));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(7), usedvars.at(7));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(8), usedvars.at(8));
//
//	usedvars = pkb.getUsedVarAtProc(B);
//	sort(usedvars.begin(), usedvars.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(0), usedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(1), usedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(2), usedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(3), usedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(4), usedvars.at(4));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(5), usedvars.at(5));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(6), usedvars.at(6));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(7), usedvars.at(7));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(8), usedvars.at(8));
//
//	usedvars = pkb.getUsedVarAtProc(C);
//	sort(usedvars.begin(), usedvars.end());
//
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(0), usedvars.at(0));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(1), usedvars.at(1));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(2), usedvars.at(2));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(3), usedvars.at(3));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(4), usedvars.at(4));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(5), usedvars.at(5));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(6), usedvars.at(6));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(7), usedvars.at(7));
//	CPPUNIT_ASSERT_EQUAL(expectedvars.at(8), usedvars.at(8));
//}