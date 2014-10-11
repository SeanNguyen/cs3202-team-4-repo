#include "PKB.h"
#include <string>

AST PKB::ast;
ListTable <string> PKB::constTable;
ListTable <string> PKB::procTable;
ListTable <string> PKB::varTable;
ListTable <string> PKB::stmtTable;

MapTable <int> PKB::followTable;
MapTable <int> PKB::parentTable;
MapTable <int> PKB::callStmtTable;
MapTable <int> PKB::callProcTable;
MapTable <int> PKB::nextTable;

MapTable <int> PKB::modifyStmtTable;
MapTable <int> PKB::modifyProcTable;
MapTable <int> PKB::useStmtTable;
MapTable <int> PKB::useProcTable;

PKB::PKB()
{
}

void PKB::resetPKB() {
	PKB::ast = AST();
	PKB::constTable = ListTable <string>();
	PKB::varTable = ListTable <string>();
	PKB::stmtTable = ListTable <string>();
	PKB::procTable = ListTable <string>();

	PKB::followTable = MapTable <int>();
	PKB::modifyStmtTable = MapTable <int>();
	PKB::modifyProcTable = MapTable <int>();
	PKB::parentTable = MapTable <int>();
	PKB::useStmtTable = MapTable <int>();
	PKB::useProcTable = MapTable <int>();
	PKB::callStmtTable = MapTable <int>();
	PKB::callProcTable = MapTable <int>();
	PKB::nextTable = MapTable <int>();
}

////////////////////////////////AST METHODS/////////////////
TNode * PKB::createNode() {
	return ast.createNode();
}

TNode * PKB::createNode(Symbol type) {
	return ast.createNode(type);
}

TNode * PKB::createNode(Symbol type, string value) {
	return ast.createNode(type, value);
}

int PKB::getNumChildren(TNode * node) {
	return ast.getNumChildren(node);
}

//TNode PKB::getChildAtIndex(TNode node, int index) {
//	return ast.getChildAtIndex(node, index);
//}

void PKB::setASTRoot(TNode * node) {
	return ast.setRoot(node);
}

TNode * PKB::getNodeOfStmt(int stmt) {
	return ast.findNodeOfStmt(stmt);
}

int PKB::addChild(TNode * parent, TNode * child) {
	return ast.addChild(parent, child);
}

///////////////////CONST TABLE METHODS////////////////////
bool PKB::insertConst(std::string value) {
	if (constTable.exist(value))
		return false;
	return constTable.insert(value);
}

int PKB::getConstIndex(std::string value){
	vector <int> indexes = constTable.getIndexes(value);
	return indexes.front();
}

std::string PKB::getConstName(int index) {
	return constTable.getValue(index);
}

int PKB::getConstTableSize()
{
	return constTable.getSize();
}

//////////////////////VAR TABLE METHODS/////////////////////////
int PKB::insertVar(std::string name) {
	if (varTable.exist(name))
		return false;
	return varTable.insert(name);
}

int PKB::getVarIndex(std::string name){
	vector <int> indexes = varTable.getIndexes(name);
	return indexes.front();
}

std::string PKB::getVarName(int index){
	return varTable.getValue(index);
}

int PKB::getVarTableSize() {
	return varTable.getSize();
}

////////////////////////STATEMENT METHODS//////////////
bool PKB::insertStmt(std::string name) {
	//if there is nothing yet, insert a dummy element
	if (stmtTable.getSize() == 0)
		stmtTable.insert("dummy");
	return stmtTable.insert(name);
}

vector<int> PKB::getStmtIndex(std::string name){
	return stmtTable.getIndexes(name);
}

std::string PKB::getStmtName(int index) {
	return stmtTable.getValue(index);
}

int PKB::getStatTableSize() {
	return stmtTable.getSize();
}

////////////////////////PROCEDURE METHODS//////////////
bool PKB::insertProc(std::string name) {
	if (procTable.exist(name))
		return false;
	return procTable.insert(name);
}

vector <int> PKB::getProcIndex(std::string name){
	return procTable.getIndexes(name);
}

std::string PKB::getProcName(int index) {
	return procTable.getValue(index);
}

int PKB::getProcTableSize()
{
	return procTable.getSize();
}

bool PKB::isProc(string name) {
	return procTable.exist(name);
}

/////////////////////FOLLOWS METHODS//////////////

bool PKB::insertFollows(int s1, int s2){
	return followTable.insert(s1, s2);
}

bool PKB::isFollows(int s1, int s2) {
	return followTable.isMapped(s1, s2);
}

bool PKB::isFollowsStar(int s1, int s2) {
	return followTable.isMappedStar(s1, s2, true);
}

int PKB::getFollowingStmt(int s1){
	vector <int> stmts = followTable.getValues(s1);
	return stmts.front();
}

int PKB::getFollowedStmt(int s1){
	vector <int> stmts = followTable.getIndexes(s1);
	return stmts.front();
}

std::vector<int> PKB::getFollowingStarStmt(int s1){
	return followTable.getValuesStar(s1, true);
}

std::vector<int> PKB::getFollowedStarStmt(int s1){
	return followTable.getIndexesStar(s1, true);
}

///////////////////////PARENT TABLE//////////////////////////////
bool PKB::isParent(int parentStmt, int childStmt){
	return parentTable.isMapped(parentStmt, childStmt);
}

bool PKB::isParentStar(int parentStmt, int childStmt)
{
	return parentTable.isMappedStar(parentStmt, childStmt, true);
}

bool PKB::insertParent(int parentStmt, int childStmt){
	return parentTable.insert(parentStmt, childStmt);
}

int PKB::getParentStmt(int childStmt){
	return parentTable.getIndexes(childStmt).front();
}

std::vector<int> PKB::getChildStmt(int parentStmt){
	return parentTable.getValues(parentStmt);
}

std::vector<int> PKB::getChildStarStmt(int parentStmt){
	return parentTable.getValuesStar(parentStmt, true);
}

std::vector<int> PKB::getParentStarStmt(int childStmt){
	return parentTable.getIndexesStar(childStmt, true);
}

int PKB::getParentTableSize()
{
	return parentTable.getSize();
}

///////////////////////CALL TABLE////////////////////////
bool PKB::isCalls(int proc1, int proc2){
	return callProcTable.isMapped(proc1, proc2);
}

bool PKB::insertCalls(int proc1, int proc2){
	return callProcTable.insert(proc1, proc2);
}

bool PKB::isCallStar(int proc1, int proc2){
	return callProcTable.isMappedStar(proc1, proc2, true);
}

std::vector<int> PKB::getCallingStarProc(int proc1){
	return callProcTable.getValuesStar(proc1, true);
}

std::vector<int> PKB::getCalledByStarProc(int proc1){
	return callProcTable.getIndexesStar(proc1, true);
}

std::vector<int> PKB::getCalledByProc(int proc1){
	return callProcTable.getIndexes(proc1);
}

std::vector<int> PKB::getCallingProc(int proc1){
	return callProcTable.getValues(proc1);
}

bool PKB::isCallStmt (int stmt, int proc) {
	return callStmtTable.isMapped(stmt, proc);
}

bool PKB::insertCallStmt (int stmt, int proc) {
	return callStmtTable.insert(stmt, proc);
}

int PKB::getCalledProc(int stmt) {
	return callStmtTable.getValues(stmt).front();
}

vector <int> PKB::getCallingStmt (int proc) {
	callStmtTable.getIndexes(proc);
}

/////////////////MODIFY METHODS/////////////////////////////////
bool PKB::isModifies(int s1, int varIndex){
	return modifyStmtTable.isMapped(s1, varIndex);
}

bool PKB::insertModifies(int s1, int varIndex){
	return modifyStmtTable.insert(s1, varIndex);
}

std::vector<int> PKB::getModifiedVarAtStmt(int s1){
	return modifyStmtTable.getValues(s1);
}

std::vector<int> PKB::getStmtModifyingVar(int varIndex){
	return modifyStmtTable.getIndexes(varIndex);
}

bool PKB::isModifiesProc(int proc1, int varIndex){
	return modifyProcTable.isMapped(proc1, varIndex);
}

int PKB::insertModifiesProc(int proc1, int varIndex){
	return modifyProcTable.insert(proc1, varIndex);
}

std::vector<int> PKB::getModifiedVarAtProc(int proc1){
	return modifyProcTable.getValues(proc1);
}

std::vector<int> PKB::getProcModifyingVar(int varIndex){
	return modifyProcTable.getIndexes(varIndex);
}

//////////////////////USE TABLE METHODS/////////////////////
bool PKB::isUses(int s1, int varIndex){
	return useStmtTable.isMapped(s1, varIndex);
}

bool PKB::insertUses(int s1, int varIndex){
	return useStmtTable.insert(s1, varIndex);
}

std::vector<int> PKB::getUsedVarAtStmt(int s1){
	return useStmtTable.getValues(s1);
}

std::vector<int> PKB::getStmtUsingVar(int varIndex){
	return useStmtTable.getIndexes(varIndex);
}

bool PKB::isUsesProc(int proc1, int varIndex){
	return useProcTable.isMapped(proc1, varIndex);
}

int PKB::insertUsesProc(int proc1, int varIndex){
	return useProcTable.insert (proc1, varIndex);
}

std::vector<int> PKB::getUsedVarAtProc(int proc1){
	return useProcTable.getValues(proc1);
}

std::vector<int> PKB::getProcUsingVar(int varIndex){
	return useProcTable.getValues(varIndex);
}

////////////////////////////////////Next METHODS///////////////////////////////

// Method to check if next relationship exists
bool PKB::isNext(int n1, int n2){
	return nextTable.isMapped(n1, n2);
}

// Method to insert a pair of line numbers
bool PKB::insertNext(int n1, int n2){
	return nextTable.insert(n1, n2);
}

// Method to check if line numbers are nextStar
bool PKB::isNextStar(int n1, int n2) {
	return nextTable.isMappedStar(n1, n2, true);
}

//Method to get the first parameter in the NextStar relationship --> Next*(n1, x)
std::vector<int> PKB::getNextStarStmts(int n1) {
	return nextTable.getValuesStar(n1, true);
}

//Method to get the second parameter in the NextStar relationship --> Next*(x, n1)
std::vector<int> PKB::getPreviousStarStmts(int n1) {
	return nextTable.getIndexesStar(n1, true);
}

// Method to get the list of line numbers next to n1
std::vector<int> PKB::getNextStmts(int n1){
	return nextTable.getValues(n1);
}

// Method to get the list of line numbers for which the next line number is n1
std::vector<int> PKB::getPreviousStmts(int n1){
	return nextTable.getIndexes(n1);
}