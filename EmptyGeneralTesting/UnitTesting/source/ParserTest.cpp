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
	parser.parse(testFile_EmptyProcedure);
}

void ParserTest::testParseCall() {
	Parser parser;
	parser.parse(testFile_Call);
}

void ParserTest::testParseWhile() {
	Parser parser;
	parser.parse(testFile_While);
}

void ParserTest::testParseIf() {
	Parser parser;
	parser.parse(testFile_If);
}

void ParserTest::testParseSimpleAssign() {
	Parser parser;
	parser.parse(testFile_SimpleAssign);
}

void ParserTest::testParseComplexAssign() {
	Parser parser;
	parser.parse(testFile_ComplexAssign);
}