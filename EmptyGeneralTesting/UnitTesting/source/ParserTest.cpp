#pragma once
#include <cppunit/config/SourcePrefix.h>

#include "ParserTest.h"
#include "Parser.h"
#include "PKB.h"
#include <iostream>
#include <algorithm>

using namespace std;

string testFile = "..\\UnitTesting\\test cases\\Source1.txt";
void ParserTest::setUp() {
}

void ParserTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( ParserTest );

void ParserTest::testParse() {
	Parser parser;
	parser.parse(testFile);
}