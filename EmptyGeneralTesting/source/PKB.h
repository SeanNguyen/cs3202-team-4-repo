#ifndef PKB_h
#define PKB_h

#include "Follow.h"
#include "ModifyTable.h"
#include "VarTable.h"
#include "ParentTable.h"
#include "StatTable.h"
#include "UseTable.h"
#include "ConstTable.h"
#include "CallTable.h"
#include "AST.h"
#include "ProcTable.h"

#include <utility>
#include <vector>
#include <iostream>
#include <string>

class PKB
{
	public: 
	PKB();

	//////////////////////////////////AST METHODS/////////////////
	static TNode createNode();

	static TNode createNode(Symbol type);

	static TNode createNode(Symbol type, string value);

	static TNode getASTRoot();

	static int getNumChildren(TNode node);
	static TNode getChildAtIndex(TNode node, int index);

	static void setASTRoot(TNode node);
	static int addChild(TNode parent, TNode child);

    static TNode getNodeOfStmt(int stmt);

	//////////////////////////CONST TABLE METHODS/////////////////
	static bool insertConst(std::string value);

	static bool isConst(std::string value);

	static int getConstIndex(std::string value);
	
	static std::string getConstName(int index);

	static int getConstTableSize();

	////////////////FOLLOWS METHODS///////////////////////
	
	// Method to return if 2 statement number s1 is followed by s2
	static bool isFollows(int s1, int s2);

	// Method to check Follows*(s1, s2) holds.
	static bool isFollowsStar(int s1, int s2);

	// Method to insert a pair of following statement numbers
	static bool insertFollows(int s1, int s2);

	// Method to get the following statement to statement number s1
	static int getFollowingStmt(int s1);

	// Method to get statement which is followed by statement s1
	static int getFollowedStmt(int s1);

	// Method to get the following statement to statement number s1
	static std::vector<int> getFollowingStarStmt(int s1);

	//  Method to get statement which is followed star by statement s1
	static std::vector<int> getFollowedStarStmt(int s1);

	//  Method to get statement which is followed star by statement s1
	static std::vector<int> getAllFollowingStmt();

	//  Method to get statement which is followed star by statement s1
	static std::vector<int> getAllFollowedStmt();

	static int getFollowTableSize();

	////////////////MODIFY METHODS///////////////////////////////

	// Method to check if modifies relationship exists
	static bool isModifies(int s1, int varIndex);
  
	// Method to insert a pair of following stmt number and variable
	static bool insertModifies(int s1, int varIndex);

	// Method to get the variables modified in stmt s1
	static std::vector<int> getModifiedVarAtStmt(int s1);

	// Method to get the list of stmt modifying var
	static std::vector<int> getStmtModifyingVar(int varIndex);

	////Method to get all statements modifying some variable
	//static std::vector<int> getAllModifyingStmt();

	////Method to get all variables being modified 
	//static std::vector<int> getAllModifiedVar();

	//static int getModifyTableSize();

	static bool isModifiesProc(int proc1, int varIndex);

	static int insertModifiesProc(int proc1, int varIndex);     

	static std::vector<int> getModifiedVarAtProc(int proc1);

	static std::vector<int> getProcModifyingVar(int varIndex);

	//static void printModifyTable();

	////////////////////VARTABLE METHODS////////////////////////

	static int insertVar(std::string name);

	static int getVarIndex(std::string name);
	
	static std::string getVarName(int index);

	static int getVarTableSize();

	////////////////////PARENT TABLE METHODS//////////////////////////

	static bool isParent(int parentStmt, int childStmt);

	static bool isParentStar(int parentStmt, int childStmt);

	static bool insertParent(int parentStmt, int childStmt);

	static int getParentStmt(int childStmt);

	static std::vector<int> getChildStmt(int parentStmt);

	static std::vector<int> getParentStarStmt(int childStmt);

	static std::vector<int> getChildStarStmt(int parentStmt);

	static std::vector<int> getAllParentStmt();

	static std::vector<int> getAllChildStmt();

	static int getParentTableSize();

	///////////////STATEMENT TABLE METHODS////////////////////////

	static bool insertStmt(string name);

	static vector<int> getStmtIndex(string name);
	
	static string getStmtName(int index);

	static int getStatTableSize();
	
	/////////////////////////////USE TABLE METHODS//////////////////

	// Method to check if uses relationship exists
	static bool isUses(int s1, int varIndex);
  
	// Method to insert a pair of following stmt number and variable
	static bool insertUses(int s1, int varIndex);

	// Method to get the variables used in stmt s1
	static std::vector<int> getUsedVarAtStmt(int s1);

	// Method to get the list of stmt using var
	static std::vector<int> getStmtUsingVar(int varIndex);



	// Method to check if uses relationship exists
	static bool isUsesProc(int proc1, int varIndex);
  
	// Method to insert a pair of uses proc number and variable
	static int insertUsesProc(int proc1, int varIndex);

	// Method to get the variables used in proc proc1
	static std::vector<int> getUsedVarAtProc(int proc1);

	// Method to get the list of proc using var
	static std::vector<int> getProcUsingVar(int varIndex);

	//Method to get all statements using some variable
	//static std::vector<int> getAllUsingStmt();

	////Method to get all variables being used 
	//static std::vector<int> getAllUsedVar();

	////Method to get the number of records in the table.
	//static int getSize();

	//Method for debugging - will be removed when submit.
	//static void printTable();

	/////////////////////////CALL TABLE/////////////////////////////////////////

	static bool isCalls(int proc1, int proc2);

	static int insertCalls(int proc1, int proc2);

	static bool isCallStar(int proc1, int proc2);

	static std::vector<int> getCallingStarProc(int proc1);

	static std::vector<int> getCalledByStarProc(int proc1);

	static std::vector<int> getCalledByProc(int proc1);

	static std::vector<int> getCallingProc(int proc1);

	///////////////////////////////PROCTABLE////////////////////////////////////

	static bool insertProc(string name);

	static vector<int> getProcIndex(string name);
	
	static string getProcName(int index);

	static int getProcTableSize();

private:
	static AST astObj;
	static ConstTable constObj;
	static Follow followObj;
	static Modify modifyObj;
	static VarTable varObj;
	static ParentTable parObj;
	static StatTable stmtObj;
	static Use useObj;
	static Call callObj;
	static ProcTable procObj;
};
#endif