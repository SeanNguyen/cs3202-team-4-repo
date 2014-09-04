#include "PKB.h"

#include <string>

AST PKB::astObj;
ConstTable PKB::constObj;
Follow PKB::followObj;
Modify PKB::modifyObj;
VarTable PKB::varObj;
ParentTable PKB::parObj;
StatTable PKB::stmtObj;
Use PKB::useObj;

PKB::PKB()
{
		
}

//////////////////////////////////AST METHODS/////////////////
TNode PKB::createNode(string type, string value) {
	return astObj.createNode(type, value);
}

TNode PKB::getASTRoot() {
	return astObj.getRoot();
}

int PKB::getNumChildren(TNode node) {
	return astObj.getNumChildren(node);
}

TNode PKB::getChildAtIndex(TNode node, int index) {
	return astObj.getChildAtIndex(node, index);
}

void PKB::setASTRoot(TNode node) {
	return astObj.setRoot(node);
}

TNode PKB::getNodeOfStmt(int stmt) {
	return astObj.findNodeOfStmt(stmt);
}

int PKB::setChild(TNode parent, TNode child) {
	return astObj.setChild(parent, child);
}

/////////////////////CONST TABLE METHODS////////////////////
bool PKB::insertConst(std::string value) {
	return constObj.insertConst(value);
}

int PKB::getConstIndex(std::string value){
	return constObj.getIndex(value);
}

std::string PKB::getConstName(int index) {
	return constObj.getConst(index);
}

int PKB::getConstTableSize()
{
	return constObj.getSize();
}

///////////////////////FOLLOWS METHODS//////////////

bool PKB::isFollows(int s1, int s2){
	return followObj.isFollows(s1, s2);
}

bool PKB::isFollowsStar(int s1, int s2)
{
	return followObj.isFollowsStar(s1, s2);
}

bool PKB::insertFollows(int s1, int s2){

	int value = followObj.insertFollows(s1, s2);
	if (value == -1){
		return false;	
	} else {
		return true;
	}
}

int PKB::getFollowingStmt(int s1){
	
	return followObj.getFollowingStmt(s1);
}

int PKB::getFollowedStmt(int s1){
	return followObj.getFollowedStmt(s1);
}

// Method to get the following statement to statement number s1
std::vector<int> PKB::getFollowingStarStmt(int s1){
	return followObj.getFollowingStarStmt(s1);
}

//  Method to get statement which is followed star by statement s1
std::vector<int> PKB::getFollowedStarStmt(int s1){
	return followObj.getFollowedStarStmt(s1);
}

//  Method to get statement which is followed star by statement s1
std::vector<int> PKB::getAllFollowingStmt(){
	return followObj.getAllFollowingStmt();
}

//  Method to get statement which is followed star by statement s1
std::vector<int> PKB::getAllFollowedStmt(){
	return followObj.getAllFollowedStmt();
}

///////////////////MODIFY METHODS/////////////////////////////////
bool PKB::isModifies(int s1, int varIndex){
	return modifyObj.isModifies(s1, varIndex);
}

bool PKB::insertModifies(int s1, int varIndex){
	int value = modifyObj.insertModifies(s1, varIndex);
	if (value == -1){
		return false;	
	} else {
		return true;
	}
}

std::vector<int> PKB::getModifiedVarAtStmt(int s1){
	return modifyObj.getModifiedVarAtStmt(s1);
}

std::vector<int> PKB::getStmtModifyingVar(int varIndex){
	return modifyObj.getStmtModifyingVar(varIndex);
}

std::vector<int> PKB::getAllModifyingStmt(){
	return modifyObj.getAllModifyingStmt();
}

std::vector<int> PKB::getAllModifiedVar(){
	return modifyObj.getAllModifiedVar();
}

int PKB::getModifyTableSize()
{
	return modifyObj.getSize();
}

//void PKB::printModifyTable()
//{
//	return modifyObj.printTable();
//}
////////////////////////VAR TABLE METHODS/////////////////////////
int PKB::insertVar(std::string name) {
	return varObj.insertVar(name);
}

int PKB::getVarIndex(std::string name){
	return varObj.getVarIndex(name);
}

std::string PKB::getVarName(int index){
	return varObj.getVarName(index);
}

int PKB::getVarTableSize()
{
	return varObj.getSize();
}

/////////////////////////PARENT TABLE//////////////////////////////
bool PKB::isParent(int parentStmt, int childStmt){
	return parObj.isParent(parentStmt, childStmt);
}

bool PKB::isParentStar(int parentStmt, int childStmt)
{
	return parObj.isParentStar(parentStmt, childStmt);
}

bool PKB::insertParent(int parentStmt, int childStmt){
	int value = parObj.insertParent(parentStmt, childStmt);
	if (value == -1){
		return false;	
	} else {
		return true;
	} 
}

int PKB::getParentStmt(int childStmt){
	return parObj.getParentStmt(childStmt);
}

std::vector<int> PKB::getChildStmt(int parentStmt){
	return parObj.getChildStmt(parentStmt);
}

std::vector<int> PKB::getChildStarStmt(int parentStmt){
	return parObj.getChildStarStmt(parentStmt);
}

std::vector<int> PKB::getParentStarStmt(int childStmt){
	return parObj.getParentStarStmt(childStmt);
}

std::vector<int> PKB::getAllParentStmt(){
	return parObj.getAllParentStmt();
}

std::vector<int> PKB::getAllChildStmt(){
	return parObj.getAllChildStmt();
}

int PKB::getParentTableSize()
{
	return parObj.getSize();
}

//////////////////////////STATEMENT METHODS//////////////
bool PKB::insertStmt(std::string name) {
	int value = stmtObj.insertStmt(name);
	if (value == -1){
		return false;	
	} else {
		return true;
	} 
}

vector<int> PKB::getStmtIndex(std::string name){
	return stmtObj.getStmtIndex(name);
}

std::string PKB::getStmtName(int index) {
	return stmtObj.getStmtName(index);
}

int PKB::getStatTableSize()
{
	return stmtObj.getSize();
}

////////////////////////USE TABLE METHODS/////////////////////
bool PKB::isUses(int s1, int varIndex){
	return useObj.isUses(s1, varIndex);
}

bool PKB::insertUses(int s1, int varIndex){
	int value = useObj.insertUses(s1, varIndex);
	if (value == -1){
		return false;	
	} else {
		return true;
	}
}

std::vector<int> PKB::getUsedVarAtStmt(int s1){
	return useObj.getUsedVarAtStmt(s1);
}

std::vector<int> PKB::getStmtUsingVar(int varIndex){
	return useObj.getStmtUsingVar(varIndex);
}

std::vector<int> PKB::getAllUsingStmt(){
	return useObj.getAllUsingStmt();
}

std::vector<int> PKB::getAllUsedVar(){
	return useObj.getAllUsedVar();
}

int PKB::getSize(){
	return useObj.getSize();
}

//void PKB::printTable(){
//	return useObj.printTable();
//}
