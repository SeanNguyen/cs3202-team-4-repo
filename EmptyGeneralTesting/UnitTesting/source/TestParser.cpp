#pragma once
#include <cppunit/config/SourcePrefix.h>

#include "TestParser.h"
#include "Parser.h"
#include "PKB.h"
#include <iostream>
#include <algorithm>

using namespace std;

string testFile = "..\sample_SIMPLE_source.txt";

void ParserTest::setUp() {
	Parser parser;
	parser.parse(testFile);
	parser.buildVarTable();
	parser.buildFollowTable();
	parser.buildModifyTable();
	parser.buildParentTable();
	parser.buildStatTable();
	parser.buildUseTable();
	

	PKB pkb;
	// CPPUNIT_ASSERT("i" == pkb.getVarName(1));
	//for(size_t i = 0; i < pkb.getVarTableSize(); i++)
	//{
	//	std::cout << "At index: " << i << " " << pkb.getVarName(i) << std::endl;
	//}
	
	// Test VarTable
	std::cout << "VAR TABLE: " << std::endl; 
	bool isVar1 = (pkb.getVarIndex("tmp") == 6);
	bool isVar2 = (pkb.getVarName(12) == "left");
	std::cout << "Test isVar1: " << isVar1 << std::endl;
	//std::cout << pkb.getVarName(12) << std::endl;
	std::cout << "Test isVar2: " << isVar2 << std::endl;
	std::cout << " " << std::endl;

	// Raw test for Follow Table.
	std::cout << "FOLLOW TABLE: " << std::endl; 

	bool isFollows1 = (pkb.isFollows(1, 20) == false);
	bool isFollows2 = (pkb.isFollows(1, 2) == true);
	std::cout << "Test isFollow1: " << isFollows1 << std::endl;
	std::cout << "Test isFollow2: " << isFollows2 << std::endl;

	bool isFollows3 = (pkb.getFollowingStmt(7) == 9);
	bool isFollows4 = (pkb.getFollowedStmt(11) == 10);
	std::cout << "Test isFollow3: " << isFollows3 << std::endl;
	//std::cout << "Test isFollow4: " << isFollows4 << std::endl;

	vector<int> allFollowing1;
	vector<int> allFollowing2;

	allFollowing1.push_back(2); allFollowing1.push_back(3); allFollowing1.push_back(4);
	allFollowing2.push_back(14); allFollowing2.push_back(15);

	bool isFollows5 = (pkb.getFollowingStarStmt(1) == allFollowing1);
	bool isFollows6 = (pkb.getFollowingStarStmt(13) == allFollowing2);
	std::cout << "Test isFollow5: " << isFollows5 << std::endl;
	std::cout << "Test isFollow6: " << isFollows6 << std::endl;
	vector<int> temp = pkb.getFollowingStarStmt(13);
	for (size_t index=0; index < temp.size(); index++)
	{
		std::cout << "Stmt that following stmt13: " << temp[index] << std::endl;
	}

	vector<int> allFollowing3;
	vector<int> allFollowed4;

	allFollowing3.push_back(2); allFollowing3.push_back(3); allFollowing3.push_back(4);
	allFollowing3.push_back(7); allFollowing3.push_back(9); allFollowing3.push_back(11);
	allFollowing3.push_back(14); allFollowing3.push_back(15); allFollowing3.push_back(16);
	allFollowing3.push_back(18); allFollowing3.push_back(19); allFollowing3.push_back(20);

	allFollowed4.push_back(1); allFollowed4.push_back(2); allFollowed4.push_back(3);
	allFollowed4.push_back(6); allFollowed4.push_back(7); allFollowed4.push_back(10);
	allFollowed4.push_back(13); allFollowed4.push_back(14); allFollowed4.push_back(12);
	allFollowed4.push_back(16); allFollowed4.push_back(9); allFollowed4.push_back(5);

	bool isFollows7 = (pkb.getAllFollowingStmt() == allFollowing3);
	bool isFollows8 = (pkb.getAllFollowedStmt() == allFollowed4);

	std::cout << "Test isFollow7: " << isFollows7 << std::endl;
	std::cout << "Test isFollow8: " << isFollows8 << std::endl;

	std::cout << " " << std::endl;

	// Raw test for Modify Table.
	std::cout << "MODIFY TABLE: " << std::endl; 
	// Test isModifies
	bool modify1 = (pkb.isModifies(1, 0) == true);
	bool modify2 = (pkb.isModifies(1, 11) == false);
	cout << "Test modify1: " << modify1 << endl;
	cout << "Test modify2: " << modify2 << endl;

	// Test getModifiedVarAtStmt
	vector<int> expectedModifiedVar;
	expectedModifiedVar.push_back(5); expectedModifiedVar.push_back(11); expectedModifiedVar.push_back(14);
	expectedModifiedVar.push_back(1); expectedModifiedVar.push_back(2); expectedModifiedVar.push_back(3);
	expectedModifiedVar.push_back(18);

	vector<int> actualModifiedVar;
	actualModifiedVar = pkb.getModifiedVarAtStmt(4);
	cout << "Print value of actualModifiedVar: " << endl;
	for(size_t index = 0; index < actualModifiedVar.size(); ++index)
	{
		cout << actualModifiedVar.at(index) << " ";
	}
	cout << " " << endl;


	sort(expectedModifiedVar.begin(), expectedModifiedVar.end());
	sort(actualModifiedVar.begin(), actualModifiedVar.end());
	bool modify3 = (expectedModifiedVar == actualModifiedVar);

	cout << "Test modify3: " << modify3 << endl;

	// Test getStmtModifyingVar
	vector<int> expectedAllModifiedVar;
	expectedAllModifiedVar.push_back(0); expectedAllModifiedVar.push_back(1); expectedAllModifiedVar.push_back(2);
	expectedAllModifiedVar.push_back(5); expectedAllModifiedVar.push_back(11); expectedAllModifiedVar.push_back(14);
	expectedAllModifiedVar.push_back(3); expectedAllModifiedVar.push_back(18);

	vector<int> actualAllModifiedVar = pkb.getAllModifiedVar();
	cout << "Print value of actualAllModifiedVar: " << endl;
	for(size_t index = 0; index < actualAllModifiedVar.size(); ++index)
	{
		cout << actualAllModifiedVar.at(index) << " ";
	}
	cout << " " << endl;

	sort(expectedAllModifiedVar.begin(), expectedAllModifiedVar.end());
	sort(actualAllModifiedVar.begin(), actualAllModifiedVar.end());

	bool modify4 = (expectedAllModifiedVar == actualAllModifiedVar);
	cout << "Test modify4: " << modify4 << endl;

	// Raw test for Parent Table.
	bool parent1 = (pkb.isParent(12, 13) == true);
	bool parent2 = (pkb.isParent(12, 16) == false);
	cout << "Test parent1: " << parent1 << endl;
	cout << "Test parent2: " << parent2 << endl;

	int expectedParent = pkb.getParentStmt(11);
	bool parent3 = (expectedParent == 9);
	cout << "Test parent3: " << parent3 << endl;
	
	vector<int> expectedChildren;
	expectedChildren.push_back(6); expectedChildren.push_back(7);
	expectedChildren.push_back(9); expectedChildren.push_back(19);
	bool parent4 = (expectedChildren == pkb.getChildStmt(5));
	cout << "Test parent4: " << parent4 << endl;

	vector<int> expectedAllChildren;
	for(int index=6; index <= 19; index++)
	{
		expectedAllChildren.push_back(index);
	}
	bool parent5 = (expectedAllChildren == pkb.getChildStarStmt(5));
	cout << "Test parent5: " << parent5 << endl;

	vector<int> expectedAllParents;
	expectedAllParents.push_back(4); expectedAllParents.push_back(5);
	expectedAllParents.push_back(9);

	bool parent6 = (expectedAllParents == pkb.getParentStarStmt(10));
	cout << "Test parent6: " << parent6 << endl;

	cout << " " << endl;
	//pkb.printModifyTable();
	
	// Raw test for Stat Table.
	bool stat1 = (pkb.getStmtName(12) == "while:stmtList");
	bool stat2 = (pkb.getStmtName(3) == "assignment");
	cout << "Test stat1: " << stat1 << endl;
	cout << "Test stat2: " << stat2 << endl;
	cout << "" << endl;

	// Raw test for Use Table.
	std::cout << "USE TABLE: " << std::endl; 
	bool use1 = (true == pkb.isUses(5, 4));
	bool use2 = (false == pkb.isUses(6, 5));
	cout << "Test use1: " << use1 << endl;
	cout << "Test use2: " << use2 << endl;

	vector<int> expectedVar;
	expectedVar.push_back(4); expectedVar.push_back(2); 
	for (size_t index=6; index<=17; index++)
	{
		expectedVar.push_back(index);
	}
	vector<int> actualVar = pkb.getUsedVarAtStmt(5);
	sort(expectedVar.begin(), expectedVar.end());
	sort(actualVar.begin(), actualVar.end());
	
	bool use3 = (expectedVar == actualVar);
	cout << "Test use3: " << use3 << endl;

	vector<int> expectedStmt;
	expectedStmt.push_back(3); expectedStmt.push_back(4);
	vector<int> actualStmt = pkb.getStmtUsingVar(3);

	sort(expectedStmt.begin(), expectedStmt.end());
	sort(actualStmt.begin(), actualStmt.end());
	bool use4 = (expectedStmt == actualStmt);
	cout << "Test use4: " << use4 << endl;

	for(size_t index=0; index < actualStmt.size(); ++index)
	{
		cout << actualStmt.at(index) << " ";
	}
	cout << "" << endl;
	
	system("pause");
}

void ParserTest::tearDown() {

}

// Registers the fixture into the 'registry'
//CPPUNIT_TEST_SUITE_REGISTRATION( ParserTest );

void ParserTest::testBuildVarTable()
{
	Parser parser;
	parser.parse(testFile);
	parser.buildVarTable();

	PKB pkb;
	CPPUNIT_ASSERT("i" == pkb.getVarName(0));
	//for(size_t i = 0; i < pkb.getVarTableSize(); i++)
	//{
	//	std::cout << "At index: " << pkb.getVarName(i);
	//}

	return;
}

void ParserTest::testBuildModifyTable()
{
	Parser parser;
	parser.parse(testFile);
	parser.buildVarTable();
	parser.buildModifyTable();

	PKB pkb;
	// Test isModifies
	bool modify1 = (pkb.isModifies(1, 0) == true);
	bool modify2 = (pkb.isModifies(1, 11) == false);
	cout << "Test modify1: " << modify1 << endl;
	cout << "Test modify2: " << modify2 << endl;

	// Test getModifiedVarAtStmt
	vector<int> expectedModifiedVar;
	expectedModifiedVar.push_back(5); expectedModifiedVar.push_back(11); expectedModifiedVar.push_back(14);
	expectedModifiedVar.push_back(1); expectedModifiedVar.push_back(2); expectedModifiedVar.push_back(3);
	expectedModifiedVar.push_back(18);

	vector<int> actualModifiedVar;
	actualModifiedVar = pkb.getModifiedVarAtStmt(4);

	sort(expectedModifiedVar.begin(), expectedModifiedVar.end());
	sort(actualModifiedVar.begin(), actualModifiedVar.end());
	bool modify3 = (expectedModifiedVar == actualModifiedVar);
	cout << "Test modify3: " << modify3 << endl;

	// Test getStmtModifyingVar
	vector<int> expectedAllModifiedVar;
	expectedAllModifiedVar.push_back(0); expectedAllModifiedVar.push_back(1); expectedAllModifiedVar.push_back(2);
	expectedAllModifiedVar.push_back(5); expectedAllModifiedVar.push_back(11); expectedAllModifiedVar.push_back(14);
	expectedAllModifiedVar.push_back(3); expectedAllModifiedVar.push_back(18);

	vector<int> actualAllModifedVar = pkb.getAllModifiedVar();

	sort(expectedAllModifiedVar.begin(), expectedAllModifiedVar.end());
	sort(actualAllModifedVar.begin(), actualAllModifedVar.end());

	bool modify4 = (expectedAllModifiedVar == actualAllModifedVar);
	cout << "Test modify4: " << modify4 << endl;



	

	std::cout << " " << std::endl;
}