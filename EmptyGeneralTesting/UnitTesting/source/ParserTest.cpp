#pragma once
#include <cppunit/config/SourcePrefix.h>

#include "ParserTest.h"
#include "Parser.h"
#include "PKB.h"
#include <iostream>
#include <algorithm>

using namespace std;

string testFile_EmptyProcedure = "..\\UnitTesting\\test cases\\ParserTest_EmptyProceure.txt";
string testFile_Call = "..\\UnitTesting\\test cases\\ParserTest_Call.txt";
string testFile_While = "..\\UnitTesting\\test cases\\ParserTest_While.txt";
string testFile_If = "..\\UnitTesting\\test cases\\ParserTest_If.txt";
string testFile_SimpleAssign = "..\\UnitTesting\\test cases\\ParserTest_SimpleAssign.txt";
string testFile_ComplexAssign = "..\\UnitTesting\\test cases\\ParserTest_ComplexAssign.txt";

void ParserTest::setUp() {
}

void ParserTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( ParserTest );

void ParserTest::testParseEmptyProcedure() {
	Parser parser;
	CPPUNIT_ASSERT_THROW ( parser.parse(testFile_EmptyProcedure), bad_exception);
}

void ParserTest::testParseCall() {
	Parser parser;
	parser.parse(testFile_Call);

	int expectedProcNumber = 3;
	int expectedVarNumber = 2;
	int expectedStmtNumber = 2;
	int expectedModifyPairNumber = 1;
	int expectedUsePairNumber = 1;
	int expectedCallPairNumber = 1;

	int actualProcNumber = parser.getProcNumber();
	int actualVarNumber = parser.getVarNumber();
	int actualStmtNumber = parser.getStmtNumber();
	int actualModifyPairNumber = parser.getModifyPairNumber();
	int actualUsePairNumber = parser.getUsePairNumber();
	int actualCallPairNumber = parser.getCallPairNumber();

	CPPUNIT_ASSERT_EQUAL(expectedProcNumber, actualProcNumber);
	CPPUNIT_ASSERT_EQUAL(expectedVarNumber, actualVarNumber);
	CPPUNIT_ASSERT_EQUAL(expectedStmtNumber, actualStmtNumber);
	CPPUNIT_ASSERT_EQUAL(expectedModifyPairNumber, actualModifyPairNumber);
	CPPUNIT_ASSERT_EQUAL(expectedUsePairNumber, actualUsePairNumber);
	CPPUNIT_ASSERT_EQUAL(expectedCallPairNumber, actualCallPairNumber);
}

void ParserTest::testParseWhile() {
	Parser parser;
	parser.parse(testFile_While);

	int expectedProcNumber = 1;
	int expectedVarNumber = 7;
	int expectedStmtNumber = 4;
	int expectedModifyPairNumber = 2;
	int expectedUsePairNumber = 5;
	int expectedCallPairNumber = 0;

	int actualProcNumber = parser.getProcNumber();
	int actualVarNumber = parser.getVarNumber();
	int actualStmtNumber = parser.getStmtNumber();
	int actualModifyPairNumber = parser.getModifyPairNumber();
	int actualUsePairNumber = parser.getUsePairNumber();
	int actualCallPairNumber = parser.getCallPairNumber();

	CPPUNIT_ASSERT_EQUAL(expectedProcNumber, actualProcNumber);
	CPPUNIT_ASSERT_EQUAL(expectedVarNumber, actualVarNumber);
	CPPUNIT_ASSERT_EQUAL(expectedStmtNumber, actualStmtNumber);
	CPPUNIT_ASSERT_EQUAL(expectedModifyPairNumber, actualModifyPairNumber);
	CPPUNIT_ASSERT_EQUAL(expectedUsePairNumber, actualUsePairNumber);
	CPPUNIT_ASSERT_EQUAL(expectedCallPairNumber, actualCallPairNumber);
}

void ParserTest::testParseIf() {
	Parser parser;
	parser.parse(testFile_If);

	int expectedProcNumber = 1;
	int expectedVarNumber = 3;
	int expectedStmtNumber = 3;
	int expectedModifyPairNumber = 2;
	int expectedUsePairNumber = 1;
	int expectedCallPairNumber = 0;

	int actualProcNumber = parser.getProcNumber();
	int actualVarNumber = parser.getVarNumber();
	int actualStmtNumber = parser.getStmtNumber();
	int actualModifyPairNumber = parser.getModifyPairNumber();
	int actualUsePairNumber = parser.getUsePairNumber();
	int actualCallPairNumber = parser.getCallPairNumber();

	CPPUNIT_ASSERT_EQUAL(expectedProcNumber, actualProcNumber);
	CPPUNIT_ASSERT_EQUAL(expectedVarNumber, actualVarNumber);
	CPPUNIT_ASSERT_EQUAL(expectedStmtNumber, actualStmtNumber);
	CPPUNIT_ASSERT_EQUAL(expectedModifyPairNumber, actualModifyPairNumber);
	CPPUNIT_ASSERT_EQUAL(expectedUsePairNumber, actualUsePairNumber);
	CPPUNIT_ASSERT_EQUAL(expectedCallPairNumber, actualCallPairNumber);
}

void ParserTest::testParseSimpleAssign() {
	Parser parser;
	parser.parse(testFile_SimpleAssign);

	int expectedProcNumber = 1;
	int expectedVarNumber = 7;
	int expectedStmtNumber = 1;
	int expectedModifyPairNumber = 1;
	int expectedUsePairNumber = 6;
	int expectedCallPairNumber = 0;

	int actualProcNumber = parser.getProcNumber();
	int actualVarNumber = parser.getVarNumber();
	int actualStmtNumber = parser.getStmtNumber();
	int actualModifyPairNumber = parser.getModifyPairNumber();
	int actualUsePairNumber = parser.getUsePairNumber();
	int actualCallPairNumber = parser.getCallPairNumber();

	CPPUNIT_ASSERT_EQUAL(expectedProcNumber, actualProcNumber);
	CPPUNIT_ASSERT_EQUAL(expectedVarNumber, actualVarNumber);
	CPPUNIT_ASSERT_EQUAL(expectedStmtNumber, actualStmtNumber);
	CPPUNIT_ASSERT_EQUAL(expectedModifyPairNumber, actualModifyPairNumber);
	CPPUNIT_ASSERT_EQUAL(expectedUsePairNumber, actualUsePairNumber);
	CPPUNIT_ASSERT_EQUAL(expectedCallPairNumber, actualCallPairNumber);
}

void ParserTest::testParseComplexAssign() {
	Parser parser;
	parser.parse(testFile_ComplexAssign);

	int expectedProcNumber = 1;
	int expectedVarNumber = 14;
	int expectedStmtNumber = 2;
	int expectedModifyPairNumber = 2;
	int expectedUsePairNumber = 12;
	int expectedCallPairNumber = 0;

	int actualProcNumber = parser.getProcNumber();
	int actualVarNumber = parser.getVarNumber();
	int actualStmtNumber = parser.getStmtNumber();
	int actualModifyPairNumber = parser.getModifyPairNumber();
	int actualUsePairNumber = parser.getUsePairNumber();
	int actualCallPairNumber = parser.getCallPairNumber();

	CPPUNIT_ASSERT_EQUAL(expectedProcNumber, actualProcNumber);
	CPPUNIT_ASSERT_EQUAL(expectedVarNumber, actualVarNumber);
	CPPUNIT_ASSERT_EQUAL(expectedStmtNumber, actualStmtNumber);
	CPPUNIT_ASSERT_EQUAL(expectedModifyPairNumber, actualModifyPairNumber);
	CPPUNIT_ASSERT_EQUAL(expectedUsePairNumber, actualUsePairNumber);
	CPPUNIT_ASSERT_EQUAL(expectedCallPairNumber, actualCallPairNumber);
}