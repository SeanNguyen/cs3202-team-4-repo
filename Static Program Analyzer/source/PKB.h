#ifndef PKB_h
#define PKB_h

#include "ListTable.h"
#include "MapTable.h"
#include "AST.h"

#include <utility>
#include <vector>
#include <iostream>
#include <string>

class PKB {
private:
	static AST ast;
	static ListTable <string> constTable;
	static ListTable <string> procTable;
	static ListTable <string> varTable;
	static ListTable <string> stmtTable;

	static MapTable <int> followTable;
	static MapTable <int> modifyStmtTable;
	static MapTable <int> modifyProcTable;
	static MapTable <int> parentTable;
	static MapTable <int> useStmtTable;
	static MapTable <int> useProcTable;
	static MapTable <int> callStmtTable;
	static MapTable <int> callProcTable;
	static MapTable <int> nextTable;
	static MapTable <int> siblingTable;
	static MapTable <int> containTable;

	static map<int, bool> flags;
	static map <int, map <int, int>> commonWhiles;
	static map <int, map <int, int>> commonIfs;

public:
	PKB();
	static void resetPKB();
	static void preCalculateStarTables();
	static void setCommonWhiles(map <int, map <int, int>> data);
	static void setCommonIfs(map <int, map <int, int>> data);
	//////////////////////////////////AST METHODS/////////////////
	static TNode * createNode();
	static TNode * createNode(Symbol type);
	static TNode * createNode(Symbol type, string value);
	static TNode * getASTRoot();
	static int getNumChildren(TNode * node);
	static TNode getChildAtIndex(TNode * node, int index);
	static void setASTRoot(TNode * node);
	static int addChild(TNode * parent, TNode * child);
	static TNode * getNodeOfStmt(int stmt);

	//////////////////////////CONST TABLE METHODS/////////////////
	static bool insertConst(std::string value);
	static bool isConst(std::string value);
	static int getConstIndex(std::string value);
	static std::string getConstName(int index);
	static int getConstTableSize();

	////////////////////VARTABLE METHODS////////////////////////

	static int insertVar(std::string name);
	static int getVarIndex(std::string name);
	static std::string getVarName(int index);
	static int getVarTableSize();

	///////////////STATEMENT TABLE METHODS////////////////////////

	static bool insertStmt(string name);
	static vector<int> getStmtIndex(string name);
	static string getStmtName(int index);
	static int getStatTableSize();

	///////////////////////////////PROCTABLE///////////////////////

	static bool insertProc(string name);
	static vector<int> getProcIndex(string name);
	static string getProcName(int index);
	static int getProcTableSize();
	static bool isProc(string name);

	////////////////FOLLOWS METHODS///////////////////////
	
	static bool isFollows(int s1, int s2);
	static bool isFollowsStar(int s1, int s2);
	static bool insertFollows(int s1, int s2);
	static int getFollowingStmt(int s1);
	static int getFollowedStmt(int s1);
	static std::vector<int> getFollowingStarStmt(int s1);
	static std::vector<int> getFollowedStarStmt(int s1);

	////////////////////PARENT TABLE METHODS//////////////////////////

	static bool isParent(int parentStmt, int childStmt);
	static bool isParentStar(int parentStmt, int childStmt);
	static bool insertParent(int parentStmt, int childStmt);
	static int getParentStmt(int childStmt);
	static std::vector<int> getChildStmt(int parentStmt);
	static std::vector<int> getParentStarStmt(int childStmt);
	static std::vector<int> getChildStarStmt(int parentStmt);
	static int getParentTableSize();

	/////////////////////////CALL TABLE/////////////////////////////////////////

	static bool isCalls(int proc1, int proc2);
	static bool insertCalls(int proc1, int proc2);
	static bool isCallStar(int proc1, int proc2);
	static std::vector<int> getCallingStarProc(int proc1);
	static std::vector<int> getCalledByStarProc(int proc1);
	static std::vector<int> getCalledByProc(int proc1);
	static std::vector<int> getCallingProc(int proc1);

	static bool isCallStmt (int stmt, int proc);
	static bool insertCallStmt (int stmt, int proc);
	static int getCalledProc(int stmt);
	static vector <int> getCallingStmt (int proc);

	////////////////MODIFY METHODS///////////////////////////////

	static bool isModifies(int s1, int varIndex);
	static bool insertModifies(int s1, int varIndex);
	static std::vector<int> getModifiedVarAtStmt(int s1);
	static std::vector<int> getStmtModifyingVar(int varIndex);
	static bool isModifiesProc(int proc1, int varIndex);
	static int insertModifiesProc(int proc1, int varIndex);     
	static std::vector<int> getModifiedVarAtProc(int proc1);
	static std::vector<int> getProcModifyingVar(int varIndex);

	/////////////////////////////USE TABLE METHODS//////////////////

	static bool isUses(int s1, int varIndex);
	static bool insertUses(int s1, int varIndex);
	static std::vector<int> getUsedVarAtStmt(int s1);
	static std::vector<int> getStmtUsingVar(int varIndex);
	static bool isUsesProc(int proc1, int varIndex);
	static int insertUsesProc(int proc1, int varIndex);
	static std::vector<int> getUsedVarAtProc(int proc1);
	static std::vector<int> getProcUsingVar(int varIndex);

	///////////////////////NEXTTABLE////////////////////////////////////

	static bool isNext(int n1, int n2);
	static bool insertNext(int n1, int n2);
	static bool isNextStar(int n1, int n2);
	static std::vector<int> getNextStarStmts(int n1);
	static std::vector<int> getPreviousStarStmts(int n1);
	static std::vector<int> getNextStmts(int n1);
	static std::vector<int> getPreviousStmts(int n1);

	///////////////////////AFFECTTABLE////////////////////////////////////
	static bool isAffect(int affectingStmt, int affectedStmt);
	static bool isAffectStar(int affectingStmt, int affectedStmt);
	// temp adding getAffected(int) to run testing - Tho
	static vector<int> getAffected(int affectingStmt);
	static vector<int> getAffected (int affectingStmt, int currentStmt, bool isStartingPoint);
	// temp adding getAffecting(int) to run testing - Tho
	static vector<int> getAffecting(int affectedStmt);
	static vector<int> getAffecting (int affectedStmt, int currentStmt, bool isStartingPoint);
	static vector<int> getAffectedStar (int affectingStmt, bool isStartingPoint);
	static vector<int> getAffectingStar (int affectedStmt, bool isStartingPoint);

	///////////////////////SIBLINGTABLE////////////////////////////////////
	static bool isSibling(int nId1, int nId2);
	static bool insertSibling(int nId1, int nId2);
	static std::vector<int> getSiblings(int nId1);
	static int getSiblingTableSize();

	///////////////////////CONTAINTABLE///////////////////////////////////
	static bool isContains(int nodeContaining, int nodeContained);
	static vector<int> getContained(int nodeContaining);
	static vector<int> getContaining(int nodeContained);

};
#endif