#include "QueryEvaluator.h"

/* PUBLIC FUNCTION */

// Description: this function is to start the query evaluating process
void QueryEvaluator::Evaluate() {
	int numQueries = QueryRepresentator::getSize();
	for (int i=0; i<numQueries; i++) {
		// process with queries, one by one
		table = QueryRepresentator::getSymbolTable(i);
		tree = QueryRepresentator::getQueryTree(i);
		checkValid = QueryRepresentator::getQueryValidity(i);
		evaluateQuery();
		/* COOPERATIVE MODE WITH AUTO TESTER */
		//if (AbstractWrapper::GlobalStop) {
		//	// do cleanup
		//	return;
		//}
	}
}

// Description: this function is to get result of query at index "index"
vector<string> QueryEvaluator::getResult(int index) { 
	if (resultList.size()==0) {
		throw "";
	} 
	if (index<0 && index>(int)resultList.size()) {
		throw "";
	}
	return resultList[index];
}

// Description: this function is to get results of all queries
vector<vector<string>> QueryEvaluator::getAllResult() {
	return resultList;
}

/* PRIVATE FUNCTION */
// Description: this function is to evaluate query one by one
void QueryEvaluator::evaluateQuery() {
	vector<string> symbolValues;
	vector<string> result;
	// check if query is valid or not
	if (checkValid==false) {
		resultList.push_back(result);
		return;
	}

	// initialize symbolValues with "-1" as meaningless value
	for (int i=0; i<table.getSize(); i++) {
		symbolValues.push_back("-1");
	}

	findResult(symbolValues, result);

	//return null if no result
	if (result.size()==0) {
		// do something here to acknowledge no result
		// currently, set result.size() = 0
		resultList.push_back(result);
	} else {
		// add to result list
		resultList.push_back(result);
	}
}

/* UPDATE AT 20th August 2014
* The change starts from this comment
*/

// Description: this function is to recursively update the values of symbol in SymbolTable,
// It starts to call isQueryConditionSatisfied when all symbols have their own value.
// Values are taken from PKB

// This method must assign values to all symbols used in the tree
// and check if those values satisfy the query or not
// if true, return the result
// if false, return null list.

void QueryEvaluator::findResult(vector<string> values, vector<string>& result) {
	bool QueryCondition = true;
	
	// start update values for symbols in QueryTree
	checkQueryCondition(1, values, result, QueryCondition);
}

void QueryEvaluator::checkQueryCondition(int childIndex, vector<string> values, vector<string>&result, bool check) {
	if (!check) {
		// return null result list
		return;
	}

	TNode root = *tree.getRoot();

	// if no more condition to check
	if (childIndex==root.getNumChildren()) {
		// if all conditions are satisfied
		if (check) {
			// get result's value and update result list
			updateResultList(values, result);
			// reset check
			check = true;
			return;
		} else {
			// there is no values satisfying query's conditions
			// return null list
			return;
		}
	} 

	// get root's child at index
	TNode child = *root.getChildAtIndex(childIndex);
	if (child.getType()==SuchThatCls) {
		// find values satisfying such that condition
		checkSuchThatCondition(child, values, result, check, childIndex);
	}

	if (child.getType()==PatternCls) {
		// find values satisfying pattern condition
		checkPatternCondition(child, values, result, check, childIndex);
	}

	if (child.getType()==WithCls) {
		checkWithCondition(child, values, result, check, childIndex);
	}
}
	
void QueryEvaluator::checkSuchThatCondition(TNode suchThatNode, vector<string> values, vector<string>& result, bool check, int childIndex) {
	// at this point we must check if result list has the value saved in value list or not

	// get root node
	TNode root = *tree.getRoot();

	// get relationship node under suchThat node
	TNode relationNode = *suchThatNode.getChildAtIndex(0);  

	handleRelationNode(relationNode, values, result, check, childIndex);
}

void QueryEvaluator::handleRelationNode(TNode & relationNode, vector<string> values, vector<string>& result, bool check, int childIndex) {
	// get 2 argument nodes under relationNode

	TNode arg1Node = *relationNode.getChildAtIndex(0);
	TNode arg2Node = *relationNode.getChildAtIndex(1);
	Symbol arg1Type = arg1Node.getType();
	Symbol arg2Type = arg2Node.getType();
	Symbol relation = relationNode.getType();
	string arg1Name = arg1Node.getValue();
	string arg2Name = arg2Node.getValue();

	if (arg1Type == Const && arg2Type == Const) {
		// check with query PKB::is*Relation*(arg1Value, arg2Value) 
		check = isRelation(relation, arg1Name, arg2Name);	
		//call back to checkQueryCondition
		checkQueryCondition(childIndex+1, values, result, check);
		return;
	} else if (arg1Type == Const && arg2Type == QuerySymbol) {
		string arg2Value = getStoredValue(values, arg2Name);
		if (arg2Value!="-1") {
			check = isRelation(relation, arg1Name, arg2Value);	
			//call back to checkQueryCondition
			checkQueryCondition(childIndex+1, values, result, check);
			return;
		} else {
			vector<string> arg2Value = getArgumentValueInRelation(relation, arg1Name,arg1Type, arg2Name,arg2Type, ARG2_UNKNOWN);
			if (arg2Value.size()==0) {
				checkQueryCondition(childIndex+1, values, result, false);
				return;
			}
			for (size_t i=0; i<arg2Value.size(); i++) {
				int arg2Index = table.getIndex(arg2Name);
				values[arg2Index] = arg2Value[i];
				checkQueryCondition(childIndex+1, values, result, check);
			}
			return;
		}
	} else if (arg1Type == QuerySymbol && arg2Type == Const) {
		string arg1Value=getStoredValue(values, arg1Name);
		if(arg1Value!="-1"){
			check=isRelation(relation,arg1Value, arg2Name);
			//call back to checkQueryCondition
			checkQueryCondition(childIndex+1, values, result, check);
			return;
		} else{
			vector<string> arg1Value=getArgumentValueInRelation(relation, arg1Name,arg1Type, arg2Name, arg2Type, ARG1_UNKNOWN);
			if (arg1Value.size()==0) {
				checkQueryCondition(childIndex+1, values, result, false);
				return;
			}
			// for each valu of arg1 we call checkQueryCondition again
			for (size_t i=0; i<arg1Value.size(); i++) {
				int arg1Index = table.getIndex(arg1Name);
				values[arg1Index] = arg1Value[i];
				checkQueryCondition(childIndex+1, values, result, check);
			}
			return;
		}
	} else {
		string arg1Value = getStoredValue(values, arg1Name);
		string arg2Value = getStoredValue(values, arg2Name);

		if(arg1Value!="-1" & arg2Value!="-1"){
			check=isRelation(relation, arg1Value, arg2Value);
			//call back to checkQueryCondition
			checkQueryCondition(childIndex+1, values, result, check);
			return;
		} else if(arg1Value!="-1" & arg2Value=="-1"){
			vector<string> arg2Values = getArgumentValueInRelation(relation, arg1Value,arg1Type, arg2Name,arg2Type, ARG2_UNKNOWN);
			if (arg2Values.size()==0) {
				checkQueryCondition(childIndex+1, values, result, false);
				return;
			}
			int arg2Index = table.getIndex(arg2Name);
			for (size_t i=0; i<arg2Values.size(); i++) {
				values[arg2Index] = arg2Values[i];
				checkQueryCondition(childIndex+1, values, result, check);
			}
			return;
		} else if(arg1Value=="-1" & arg2Value!="-1"){
			vector<string> arg1Values=getArgumentValueInRelation(relation, arg1Name,arg1Type, arg2Value, arg2Type, ARG1_UNKNOWN);
			if (arg1Values.size()==0) {
				checkQueryCondition(childIndex+1, values, result, false);
				return;
			}
			// for each valu of arg1 we call checkQueryCondition again
			for (size_t i=0; i<arg1Values.size(); i++) {
				int arg1Index = table.getIndex(arg1Name);
				values[arg1Index] = arg1Values[i];
				checkQueryCondition(childIndex+1, values, result, check);
			}
			return;
		} else{
			//brute force method
			string type = table.getType(arg1Name);
			vector<string> arg1Value = getAllArgValues(SyntaxHelper::getSymbolType(type));
			// for each valu of arg1 we call checkQueryCondition again
			for (size_t i=0; i<arg1Value.size(); i++) {
				int arg1Index = table.getIndex(arg1Name);
				//cout << arg1Index << " " << arg1Value[i]<< " " <<endl;
				values[arg1Index] = arg1Value[i];
				checkQueryCondition(childIndex, values, result, check);
			}
			return;
		}

	}
}

vector<string> QueryEvaluator::getArgumentValueInRelation(Symbol relation, string arg1Value, Symbol arg1Type, string arg2Value, Symbol arg2Type, int argIndex) {
	vector<string> resultList;

	switch (argIndex) {
	case ARG1_UNKNOWN:
	{
		switch (relation) {
			case Follows:
			{
				int stmt2 = atoi(arg2Value.c_str());
				int result = PKB::getFollowedStmt(stmt2);
				if (result!=-1) {
					resultList.push_back(intToString(result));
				}
				break;
			}
			case FollowsS:
			{
				int stmt2 = atoi(arg2Value.c_str());
				vector<int> stmts = PKB::getFollowedStarStmt(stmt2);
				for (size_t i=0; i<stmts.size(); i++) {
					resultList.push_back(intToString(stmts[i]));
				}
				break;
			}
			case Parent:
			{
				int stmt2 = atoi(arg2Value.c_str());
				int result = PKB::getParentStmt(stmt2);
				if (result!=-1) {
					resultList.push_back(intToString(result));
				}
				break;
			}
			case ParentS:
			{
				int stmt2 = atoi(arg2Value.c_str());
				vector<int> stmts = PKB::getParentStarStmt(stmt2);
				for (size_t i=0; i<stmts.size(); i++) {
					resultList.push_back(intToString(stmts[i]));
				}
				break;
			}
			case Modifies:
			{
				int var2 = PKB::getVarIndex(arg2Value);
				vector<int> stmts;

				if(table.getType(arg1Value)==KEYWORD_PROCEDURE){
					//var2=PKB::getProcIndex(arg2Value);
					stmts=PKB::getProcModifyingVar(var2);
				} else{
					var2=PKB::getVarIndex(arg2Value);
					stmts = PKB::getStmtModifyingVar(var2);
				}
				
				for (size_t i=0; i<stmts.size(); i++) {
					resultList.push_back(intToString(stmts[i]));
				}
				break;
			}
			case Uses:
			{
				int var2 = PKB::getVarIndex(arg2Value);
				vector<int> stmts;
				if(table.getType(arg1Value)==KEYWORD_PROCEDURE){ // FIX
					//var2=PKB::getProcIndex(arg2Value);
					stmts=PKB::getProcUsingVar(var2);

				}
				else{
					cout << "checkpoint 001 " <<var2 << " " << arg2Value <<endl;
					stmts = PKB::getStmtUsingVar(var2);
					cout << "checkpoint 002 " << stmts.size() <<endl;
				}

				for (size_t i=0; i<stmts.size(); i++) {
					cout << "checkpoint " << stmts[i] <<endl;
					resultList.push_back(intToString(stmts[i]+1));
				}
				break;
			}
			case Calls:
			{
				if (PKB::getProcIndex(arg2Value).size()!=0) {
					int proc2 = PKB::getProcIndex(arg2Value).front();
					//int var2=PKB::getProcIndex(arg1Value);
					vector<int> stmts=PKB::getCallingProc(proc2);
					for(size_t i=0;i<stmts.size();i++){
						string proc1Name = PKB::getProcName(stmts[i]);
						resultList.push_back(proc1Name);
					}
				}
				break;
			}
			case CallsS:
			{
				if (PKB::getProcIndex(arg2Value).size()!=0) {
					int proc2 = PKB::getProcIndex(arg2Value).front();
					//int var2=PKB::getProcIndex(arg1Value);
					vector<int> stmts=PKB::getCallingStarProc(proc2);
					for(size_t i=0;i<stmts.size();i++){
						string proc1Name = PKB::getProcName(stmts[i]);
						resultList.push_back(proc1Name);
					}
				}
				break;

			}
			case Nexts:
				{
					int stmt2 = atoi(arg2Value.c_str());
					vector<int> arg1Values = PKB::getPreviousStmts(stmt2);
					for (size_t i=0; i<arg1Values.size(); i++) {
						resultList.push_back(intToString(arg1Values[i]));
					}
					break;
				}
			case NextsS:
				{
					int stmt2 = atoi(arg2Value.c_str());
					vector<int> arg1Values = PKB::getPreviousStarStmts(stmt2);
					for (size_t i=0; i<arg1Values.size(); i++) {
						resultList.push_back(intToString(arg1Values[i]));
					}
					break;
				}
			default:
				break;
		}
		break;
	}
	case ARG2_UNKNOWN:
	{
		switch (relation) {
			case Follows:
			{
				int stmt1 = atoi(arg1Value.c_str());
				int result = PKB::getFollowingStmt(stmt1);		
				if (result!=-1) {
					resultList.push_back(intToString(result));
				}
				break;
			}
			case FollowsS:
			{
				int stmt1 = atoi(arg1Value.c_str());
				vector<int> stmts = PKB::getFollowingStarStmt(stmt1);
				for (size_t i=0; i<stmts.size(); i++) {
					resultList.push_back(intToString(stmts[i]));
				}
				break;
			}
			case Parent:
			{
				int stmt1 = atoi(arg1Value.c_str());
				vector<int> stmts = PKB::getChildStmt(stmt1);
				for (size_t i=0; i<stmts.size(); i++) {
					resultList.push_back(intToString(stmts[i]));
				}
				break;
			}
			case ParentS:
			{
				int stmt1 = atoi(arg1Value.c_str());
				vector<int> stmts = PKB::getChildStarStmt(stmt1);
				for (size_t i=0; i<stmts.size(); i++) {
					resultList.push_back(intToString(stmts[i]));
				}
				break;
			}
			case Modifies:
			{
				vector<int> stmts;
				if (isNumber(arg1Value)) { // found stmt
					int stmt1 = atoi(arg1Value.c_str());
					stmts = PKB::getModifiedVarAtStmt(stmt1);
				} else {
					vector<int> procs = PKB::getProcIndex(arg1Value);
					stmts = PKB::getModifiedVarAtProc(procs[0]);
				}
				for (size_t i=0; i<stmts.size(); i++) {
					resultList.push_back(PKB::getVarName(stmts[i]));
				}
				break;
			}
			case Uses:
			{
				vector<int> stmts;
				if (isNumber(arg1Value)) { // found stmt
					int stmt1 = atoi(arg1Value.c_str());
					stmts = PKB::getUsedVarAtStmt(stmt1);
				} else {
					vector<int> procs = PKB::getProcIndex(arg1Value);
					stmts = PKB::getUsedVarAtProc(procs[0]);
				}
				for (size_t i=0; i<stmts.size(); i++) {
					resultList.push_back(PKB::getVarName(stmts[i]));
				}
				break;
			}
			case Calls:
			{
				if (PKB::getProcIndex(arg1Value).size()!=0) {
					int proc1 = PKB::getProcIndex(arg1Value).front();
					//int var2=PKB::getProcIndex(arg1Value);
					vector<int> stmts=PKB::getCalledByProc(proc1);
					for(size_t i=0;i<stmts.size();i++){
						string proc2Name = PKB::getProcName(stmts[i]);
						resultList.push_back(proc2Name);
					}
				}
				break;

			}
			case CallsS:
			{
				if (PKB::getProcIndex(arg1Value).size()!=0) {
					int proc1 = PKB::getProcIndex(arg1Value).front();
					//int var2=PKB::getProcIndex(arg1Value);
					vector<int> stmts=PKB::getCalledByStarProc(proc1);
					for(size_t i=0;i<stmts.size();i++){
						string proc2Name = PKB::getProcName(stmts[i]);
						resultList.push_back(proc2Name);
					}
				}
				break;
			}
			case Nexts:
			{
				int stmt1 = atoi(arg2Value.c_str());
				vector<int> arg2Values = PKB::getNextStmts(stmt1);
				for (size_t i=0; i<arg2Values.size(); i++) {
					resultList.push_back(intToString(arg2Values[i]));
				}
				break;
			}
			case NextsS:
			{
				int stmt1 = atoi(arg2Value.c_str());
				vector<int> arg2Values = PKB::getNextStarStmts(stmt1);
				for (size_t i=0; i<arg2Values.size(); i++) {
					resultList.push_back(intToString(arg2Values[i]));
				}
				break;
			}
			default:
				break;
		}
		
	}
	default:
		break;
	}

	// remove values with wrong type
	switch(argIndex) {
	case (ARG1_UNKNOWN):
		{
			string argType = table.getType(arg1Value);
			Symbol type = SyntaxHelper::getSymbolType(argType);
			resultList = removeInvalidValues(resultList, type);
			break;
		}
	case (ARG2_UNKNOWN):
		{
			string argType = table.getType(arg2Value);
			Symbol type = SyntaxHelper::getSymbolType(argType);
			resultList = removeInvalidValues(resultList, type);
		}
	default:
		break;
	}

	return resultList;
}

bool QueryEvaluator::isRelation(Symbol relation, string arg1Value, string arg2Value) {
	switch (relation) {
	case Follows:
	{
		// 2 arguments' values are stmt no
		int stmt1 = atoi(arg1Value.c_str());
		int stmt2 = atoi(arg2Value.c_str());
		return PKB::isFollows(stmt1, stmt2);
	}
	case FollowsS:
	{
		int stmt1 = atoi(arg1Value.c_str());
		int stmt2 = atoi(arg2Value.c_str());
		return PKB::isFollowsStar(stmt1, stmt2);
	}
	case Parent:
	{
		int stmt1 = atoi(arg1Value.c_str());
		int stmt2 = atoi(arg2Value.c_str());
		return PKB::isParent(stmt1, stmt2);
	}
	case ParentS:
	{
		int stmt1 = atoi(arg1Value.c_str());
		int stmt2 = atoi(arg2Value.c_str());
		return PKB::isParentStar(stmt1, stmt2);
	}
	case Modifies:	
	{
		int stmt1 = atoi(arg1Value.c_str());
		int varIndex = PKB::getVarIndex(arg2Value);
		return PKB::isModifies(stmt1, varIndex);
	}
	case Uses:
	{
		int stmt1 = atoi(arg1Value.c_str());
		int varIndex = PKB::getVarIndex(arg2Value);
		return PKB::isUses(stmt1, varIndex);
	}
	case Calls:
	{
		int proc1 = -1; int proc2 = -1;
		if (PKB::getProcIndex(arg1Value).size()!=0) {
			proc1 = PKB::getProcIndex(arg1Value).front();
		}
		if (PKB::getProcIndex(arg2Value).size()!=0) {
			proc2 = PKB::getProcIndex(arg2Value).front();
		}
		return PKB::isCalls(proc1, proc2);
	}
	case CallsS:
	{
		int proc1 = -1; int proc2 = -1;
		if (PKB::getProcIndex(arg1Value).size()!=0) {
			proc1 = PKB::getProcIndex(arg1Value).front();
		}
		if (PKB::getProcIndex(arg2Value).size()!=0) {
			proc2 = PKB::getProcIndex(arg2Value).front();
		}
		return PKB::isCallStar(proc1, proc2);
	}
	case Nexts:
	{
		int stmt1 = atoi(arg1Value.c_str());
		int stmt2 = atoi(arg2Value.c_str());
		return PKB::isNext(stmt1, stmt2);
	}
	case NextsS:
	{
		int stmt1 = atoi(arg1Value.c_str());
		int stmt2 = atoi(arg2Value.c_str());
		return PKB::isNextStar(stmt1, stmt2);
	}
	default:
		return false;
	}
}

string QueryEvaluator::getStoredValue(vector<string> values, string argName) {
	int index = table.getIndex(argName);
	return values[index];
}

void QueryEvaluator::checkPatternCondition(TNode patternNode,vector<string> values,vector<string>& result,bool check,int childIndex) {
	// get first child of patternNode
	TNode * child1 = patternNode.getChildAtIndex(0);
	string child1Name = child1 -> getValue();
	int child1Index = table.getIndex(child1Name);
	string type = table.getType(child1Name);
	Symbol child1Type = SyntaxHelper::getSymbolType(type);
	string child1Value = values[child1Index];

	if (child1Value=="-1") {
		vector<string> child1Values = getAllArgValues(child1Type);
		if (child1Values.size()==0) {
			checkQueryCondition(childIndex+1, values, result, false);
			return;
		}
		for (size_t i=0; i<child1Values.size(); i++) {
			values[child1Index] = child1Values[i];
			checkPatternCondition(patternNode, values, result, check, childIndex);
		}
		return;
	}

	// handle left hand side of pattern condition
	TNode * arg1Node = child1 -> getChildAtIndex(0);
	handlePatternLeftHand(child1Value, arg1Node, values,check);
	if (check==false) {
		checkQueryCondition(childIndex+1, values, result, check);
		return;
	}

	// handle right hand side of pattern condition
	// by definition, only consider pattern of assignment 
	switch (child1Type) {
	case Assign:
		{
			TNode * arg2Node = child1->getChildAtIndex(1);
			handlePatternRightHand(child1Value, arg2Node, values, check);
			break;
		}
	default:
		break;
	}

	checkQueryCondition(childIndex+1, values, result, check);

}

void QueryEvaluator::handlePatternLeftHand(string stmt, TNode * leftNode, vector<string> & values, bool & check) {
	Symbol leftType = leftNode->getType();
	string leftName = leftNode->getValue();
	int leftIndex = table.getIndex(leftName);

	switch (leftType) {
	case Underline: 
		{
			check = true;
			return;
		}
	case QuerySymbol:
		{
			string leftValue = values[leftIndex];
			if (leftValue=="-1") {
				int stmtNo = atoi(stmt.c_str());
				TNode * stmtNode = PKB::getNodeOfStmt(stmtNo);

				TNode * child1 = stmtNode->getChildAtIndex(0);
				string child1Name = child1 -> getValue();
				values[leftIndex] = child1Name;
			} else {
				int stmtNo = atoi(stmt.c_str());
				TNode * stmtNode = PKB::getNodeOfStmt(stmtNo);

				TNode * child1 = stmtNode->getChildAtIndex(0);
				string child1Value = child1->getValue();
				if (child1Value==leftValue) {  
					check = true;
				}
				else {
					check=false;
				} 
			}
			return;
		}
	case Const:
		{
			int stmtNo = atoi(stmt.c_str());
			TNode * stmtNode = PKB::getNodeOfStmt(stmtNo);

			TNode * child1 = stmtNode->getChildAtIndex(0);
			string child1Value = child1->getValue();
			if (child1Value==leftName) { check = true; }
			else {check=false;} 
			return;
		}
	default:
		break;
	}
	return;
}

void QueryEvaluator::handlePatternRightHand(string stmt, TNode * leftNode, vector<string> & values, bool & check) {
	Symbol leftType = leftNode->getType();
	string leftName = leftNode->getValue();

	switch (leftType) {
	case Underline:
		{
			int leftIndex = table.getIndex(leftName);
			if (leftNode->getNumChildren()==0) {
				check = true;
			} else {
				TNode * node = leftNode->getChildAtIndex(0); 
				int stmtNo = atoi(stmt.c_str());
				TNode * stmtNode = PKB::getNodeOfStmt(stmtNo);
				TNode * rightSideStmtNode = stmtNode ->getChildAtIndex(1);
				Tree tree1; tree1.setRoot(node);
				AST tree2; tree2.setRoot(rightSideStmtNode);
				check = tree2.hasSubTree(tree1);
			}
			break;
		}
	case No_Underline:
		{
			int leftIndex = table.getIndex(leftName);
			TNode * node = leftNode->getChildAtIndex(0); 
			int stmtNo = atoi(stmt.c_str());
			TNode * stmtNode = PKB::getNodeOfStmt(stmtNo);
			//stmtNode->printTNode();
			TNode * rightSideStmtNode = stmtNode ->getChildAtIndex(1);
			Tree tree1; tree1.setRoot(node);
			AST tree2; tree2.setRoot(rightSideStmtNode);
			check = tree2.isSameTree(tree1);
			break;
		}
	default:
		check = false;
		break;
	}

	return;
}

void QueryEvaluator::checkWithCondition(TNode withNode, vector<string> values, vector<string>& result, bool check, int childIndex) {
	TNode * child1 = withNode.getChildAtIndex(0);
	TNode * child2 = withNode.getChildAtIndex(1);
	Symbol child1Type = child1 -> getType();
	Symbol child2Type = child2 -> getType();
	string child1Name = child1 -> getValue();
	string child2Name = child2 -> getValue();

	switch (child1Type) {
	case Const:
		{
			switch (child2Type) {
			case Const:
				{
					check = (child1Name==child2Name);
					checkQueryCondition(childIndex+1, values, result, check);
					return;
				}
			case QuerySymbol:
				{
					int child2Index = table.getIndex(child2Name);
					string child2Value = values[child2Index];
					if (child2Value!="-1") {
						check = (child1Name==child2Value);
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					} else {
						string type = table.getType(child2Name);
						vector<string> child2Values = getAllArgValues(SyntaxHelper::getSymbolType(type));
						if (child2Values.size()==0) {
							checkQueryCondition(childIndex, values, result, false);
							return;						
						}
						for (size_t i=0; i<child2Values.size(); i++) {
							values[child2Index]=child2Values[i];
							check = (child1Name==child2Values[i]);
							checkQueryCondition(childIndex+1, values, result, check);
							return;
						}
					}
				}
			default:
				break;
			}
			break;
		}
	case QuerySymbol:
		{
			int child1Index = table.getIndex(child1Name);
			string child1Value = values[child1Index];
			if (child1Value=="-1") {
				// get all possible values of child1
				string type = table.getType(child1Name);
				vector<string> child1Values = getAllArgValues(SyntaxHelper::getSymbolType(type));
				if (child1Values.size()==0) {
					checkQueryCondition(childIndex+1, values, result, false);
					return;
				}
				for (size_t i=0; i<child1Values.size(); i++) {
					values[child1Index]=child1Values[i];
					checkWithCondition(withNode, values, result, check, childIndex);
				}
			} else {
				switch (child2Type) {
					case Const:
						{
							check = (child1Value==child2Name);
							checkQueryCondition(childIndex+1, values, result, check);
							return;
						}
					case QuerySymbol:
						{
							int child2Index = table.getIndex(child2Name);
							string child2Value = values[child2Index];
							if (child2Value!="-1") {
								check = (child1Value==child2Value);
								checkQueryCondition(childIndex+1, values, result, check);
								return;
							} else {
								string type = table.getType(child2Name);
								vector<string> child2Values = getAllArgValues(SyntaxHelper::getSymbolType(type));
								if (child2Values.size()==0) {
									checkQueryCondition(childIndex, values, result, false);
									return;						
								}
								for (size_t i=0; i<child2Values.size(); i++) {
									values[child2Index]=child2Values[i];
									check = (child1Value==child2Values[i]);
									checkQueryCondition(childIndex+1, values, result, check);
									return;
								}
							}
						}
					default:
						break;
				}
			}
			break;
		}
	default:
		break;
	}
}

vector<string> QueryEvaluator::getAllArgValues(Symbol type) {
	vector<string> result;
	switch(type) {
	case Var:
		for (int i=0; i<PKB::getVarTableSize(); i++) {
			result.push_back(PKB::getVarName(i));
		}
		break;
	case Const:
		for (int i=0; i<PKB::getConstTableSize(); i++) {
			result.push_back(PKB::getConstName(i));
		}
		break;
	case Procedure:
		for (int i=0; i<PKB::getProcTableSize(); i++) {
			result.push_back(PKB::getProcName(i));
		}
		break;
	case Stmt:
	case Prog_line:
		for (int i=1; i<PKB::getStatTableSize(); i++) {
			result.push_back(intToString(i));
		}
		break;
	case Assign:
		{
			vector<int> assignStmts = PKB::getStmtIndex(KEYWORD_ASSIGN);
			for (size_t i=0; i<assignStmts.size(); i++) {
				result.push_back(intToString(assignStmts[i]));
			}
			break;
		}
	case While:
		{
			vector<int> whileStmts = PKB::getStmtIndex(KEYWORD_WHILE);
			for (size_t i=0; i<whileStmts.size(); i++) {
				result.push_back(intToString(whileStmts[i]));
			}
			break;
		}
	case If:
		{
			vector<int> IfStmts = PKB::getStmtIndex(KEYWORD_IF);
			for (size_t i=0; i<IfStmts.size(); i++) {
				result.push_back(intToString(IfStmts[i]));
			}
			break;
		}
	case CallStmt: {
			vector<int> callStmts = PKB::getStmtIndex(KEYWORD_CALL);
			for (size_t i=0; i<callStmts.size(); i++) {
				result.push_back(intToString(callStmts[i]));
			}
			break;
		}
	default:
		break;
	}
	return result;
}

void QueryEvaluator::updateResultList(vector<string> values, vector<string>& result) {
	TNode root = *tree.getRoot();
	// get first child
	TNode child1 = *root.getChildAtIndex(0);
	string child1Name = child1.getValue();

	TNode child = *child1.getChildAtIndex(0);
	Symbol paramType = child.getType();
	string paramName = child.getValue();

	if (child1Name=="a-BOOLEAN") { // BOOLEAN query
		result.push_back("true");
		return;
	}

	// get index of the parameter
	int paramIndex = table.getIndex(paramName);
	string paramVal = values[paramIndex];
	// check if paramVal is null value or not
	if (paramVal!="-1") {
		// check if paramVal has same type as in paramType
		string type = table.getType(paramName);
		if (!isDeclaredType(paramVal, paramName, type)) { 
			return;
		}

		// check if result list has this paramVal
		if (!isResult(paramVal, result)) {
			// add new result to list
			result.push_back(paramVal);
		}
	} else {
		// all values possible of param are result
		string paramType = table.getType(paramName);
		if (paramType== KEYWORD_PROG_LINE || paramType==KEYWORD_STMT) {
			// retrieve all statements 
			for (int i=1; i<PKB::getStatTableSize(); i++) {
				paramVal = intToString(i);
				if (!isResult(paramVal, result)) {
					// add new result to list
					result.push_back(paramVal);
				}
			}
		} else if (paramType==KEYWORD_ASSIGN) {
			vector<int> paramList = PKB::getStmtIndex(KEYWORD_ASSIGN);
			for (size_t i=0; i<paramList.size(); i++) {
				paramVal = intToString(paramList[i]);
				if (!isResult(paramVal, result)) {
					// add new result to list
					result.push_back(paramVal);
				}
			}
		} else if (paramType==KEYWORD_WHILE) {
			vector<int> paramList = PKB::getStmtIndex(KEYWORD_WHILE);
			for (size_t i=0; i<paramList.size(); i++) {
				paramVal = intToString(paramList[i]);
				if (!isResult(paramVal, result)) {
					// add new result to list
					result.push_back(paramVal);
				}
			}
		} else if (paramType==KEYWORD_IF) {
			vector<int> paramList = PKB::getStmtIndex(KEYWORD_IF);
			for (size_t i=0; i<paramList.size(); i++) {
				paramVal = intToString(paramList[i]);
				if (!isResult(paramVal, result)) {
					// add new result to list
					result.push_back(paramVal);
				}
			}
		} else if (paramType==KEYWORD_CALL) {
			vector<int> paramList = PKB::getStmtIndex(KEYWORD_CALL);
			for (size_t i=0; i<paramList.size(); i++) {
				paramVal = intToString(paramList[i]);
				if (!isResult(paramVal, result)) {
					// add new result to list
					result.push_back(paramVal);
				}
			}
		} else if (paramType==KEYWORD_VAR) {
			for (int i=0; i<PKB::getVarTableSize(); i++) {
				result.push_back(PKB::getVarName(i));
			}
		} else if (paramType==KEYWORD_CONST) {
			for (int i=0; i<PKB::getConstTableSize(); i++) {
				result.push_back(PKB::getConstName(i));
			}
		} else if (paramType==KEYWORD_PROCEDURE) {
			for (int i=0; i<PKB::getProcTableSize(); i++) {
				result.push_back(PKB::getProcName(i));
			}
		}
		else return;
	}	
}

vector<string> QueryEvaluator::removeInvalidValues(vector<string> list, Symbol type) {
	vector<string> result;
	for (size_t i=0; i<list.size(); i++) {
		string value = list[i];
		switch (type) {
		case Procedure:
			{
				if (PKB::isProc(value)) { result.push_back(value); }	
				break;
			}
		case Stmt: 
		case Prog_line:
			{
				int stmt = atoi(value.c_str());
				if (stmt <= PKB::getStatTableSize() ) { result.push_back(value);}
				break;
			}
		case Assign:
			{
				int stmt = atoi(value.c_str())-1;
				if (PKB::getStmtName(stmt)==KEYWORD_ASSIGN ) { result.push_back(value);}
				break;
			}
		case While:
			{
				int stmt = atoi(value.c_str())-1;
				if (PKB::getStmtName(stmt)==KEYWORD_WHILE ) { result.push_back(value);}
				break;
			}
		case If:
			{
				int stmt = atoi(value.c_str())-1;
				if (PKB::getStmtName(stmt)==KEYWORD_IF ) { result.push_back(value);}
				break;
			}
		case CallStmt:
			{
				int stmt = atoi(value.c_str())-1;
				if (PKB::getStmtName(stmt)==KEYWORD_CALL ) { result.push_back(value);}
				break;
			}
		case Var:
			{
				if (PKB::getVarIndex(value)!=-1 ) { result.push_back(value);}
				break;
			}
		case Const:
			{
				if (PKB::getConstIndex(value)!=-1 ) { result.push_back(value);}
				break;
			}
		default:
			break;
		}
	}
	return result;
}

bool QueryEvaluator::isResult(string val, vector<string> result) {
	for (size_t i=0; i<result.size(); i++) {
		if (result[i]==val) return true;
	}
	return false;
}

bool QueryEvaluator::isDeclaredType(string val, string name, string type) {
	if (type=="const") {
		if (PKB::getConstIndex(val)==-1) return false; 
	} else if (type=="variable") {
		if (PKB::getVarIndex(val)==-1) return false;
	} else if (type=="procedure") {
		if (PKB::getProcIndex(val).size()==0) return false;
	} else {
		// search in StmtTable for this case
		if (table.getType(name)!= "prog_line" && table.getType(name)!= "stmt") {
			string stmtType = PKB::getStmtName(atoi(val.c_str())-1);
			if (stmtType==KEYWORD_ASSIGN && table.getType(name)!="assign") return false; 
			if (stmtType=="while" && table.getType(name)!="while") return false;
			// implement further for call, etc.
		} else return true;
	}

	return true;
}

// Description: this function is to get the result values from list of symbols' values
// after the functions isSuchThatConditionSatisfied and isPatternConditionSatisfied finish
string QueryEvaluator::getResultAfterEvaluation(vector<string> values) {
	// get node containing symbol name of result
	TNode root = *tree.getRoot();
	TNode result = *root.getChildAtIndex(0);
	TNode resultChild1 = *result.getChildAtIndex(0);

	string name = resultChild1.getValue();
	int index = table.getIndex(name);

	return values[index];
}

void QueryEvaluator::addNewResult(vector<string>& resultList, string result) {
	for  (size_t i=0; i<resultList.size(); i++) {
		if (resultList[i] == result) {
			return;
		}
	}
	resultList.push_back(result);
}

/* SUPPORTING FUNCTION */

// Description: change parameter's type from int to string 
string QueryEvaluator::intToString(int num) {
    ostringstream ss;
    ss << num;
    return ss.str();
}

bool QueryEvaluator::isNumber(string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

/* TESTING FUNCTION */

// Description: print all symbols' values retrieved at a certain point
void QueryEvaluator::printSymbolValues(vector<string> symbolValues) {
	cout <<endl << "Symbol values: " ;
	for (size_t i=0; i<symbolValues.size(); i++) {
		cout << symbolValues[i] << " " ;
	}
	cout <<endl;
}

