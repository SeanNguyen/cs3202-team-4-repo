#include "QueryEvaluator.h"

void QueryEvaluator::Evaluate() {
	int size = QueryRepresentator::getSize();

	for (int i=0; i<size; i++) {
		table = QueryRepresentator::getSymbolTable(i);
		tree = QueryRepresentator::getQueryTree(i);
		checkValid = QueryRepresentator::getQueryValidity(i);
		evaluateQuery();
	}
}

vector<string> QueryEvaluator::getResult(int index) {
	vector<string> result;
	int size = resultList.size();
	if (index<0 || index>=size) return result;
	return resultList[index];
}

vector<vector<string>> QueryEvaluator::getAllResult() {
	return resultList;
}

void QueryEvaluator::evaluateQuery() {
	if (checkValid) {
		TNode * select_node = tree.getRoot();
		ResultManager result_manager = ResultManager(); 
		bool is_satisfied = true;

		int size = select_node->getNumChildren();
		// ignore result node and process with all clause node
		for (int i=1; i<size; i++) {
			TNode * clause_node = select_node->getChildAtIndex(i);
			vector<string> symbols = getSymbolsUsedBy(clause_node);
			ResultTable * temp_results = result_manager.extractTable(symbols);
			is_satisfied = evaluateClause(clause_node, temp_results);
			if (!is_satisfied) {
				break;
			} else {
				result_manager.insertTable(temp_results);
				//result_manager.maintain();
			}
		}
		TNode * result_node = select_node->getChildAtIndex(0);
		vector<string> result = extractResult(result_node, &result_manager, is_satisfied);
		resultList.push_back(result);
	} else {
		vector<string> result = extractResult();
		resultList.push_back(result);
	}	
}

bool QueryEvaluator::evaluateClause(TNode * clause_node, ResultTable * temp_results) {
	bool is_satisfied = true;
	int size = temp_results->getSize();
	for (int i=0; i<size; i++) {
		vector<string> row = temp_results->getValRow(i);
		vector<vector<string>> new_rows;
		is_satisfied = evaluateClause(clause_node, row, &new_rows);
		if (!is_satisfied) {
			return is_satisfied;
		}
		temp_results->insertValRow(new_rows);
	}
	temp_results->deleleInvalidRows();
	return is_satisfied;
}

bool QueryEvaluator::evaluateClause(TNode * clause_node, vector<string> row, vector<vector<string>> * new_rows) {
	Symbol clause_type = clause_node->getType();
	switch(clause_type) {
	case SuchThatCls:
		{
			return evaluateSTClause(clause_node, row, new_rows);
		}
	case PatternCls:
		{
			return evaluatePTClause(clause_node, row, new_rows);
		}
	case WithCls:
		{
			return evaluateWClause(clause_node, row, new_rows);
		}
	default:
		return false;
	}
}

bool QueryEvaluator::evaluateSTClause(TNode * ST_node, 
									vector<string> row, 
									vector<vector<string>> * new_rows) {
	TNode * rlt_node = ST_node->getChildAtIndex(0);
	TNode * arg1_node = rlt_node->getChildAtIndex(0);
	TNode * arg2_node = rlt_node->getChildAtIndex(1);

	Symbol rlt = rlt_node->getType();
	Symbol arg1_type = arg1_node->getType();
	Symbol arg2_type = arg2_node->getType();
	string arg1_val; string arg2_val;

	if ((arg1_type==Const || arg1_type==Underline) && 
		(arg2_type==Const || arg2_type==Underline)) {
		arg1_val = arg1_node->getValue();
		arg2_val = arg2_node->getValue();
	} else if ((arg1_type==Const || arg1_type==Underline) && 
				arg2_type==QuerySymbol) {
		arg1_val = arg1_node->getValue();
		arg2_val = row[0];
	} else if (arg1_type==QuerySymbol && 
				(arg2_type==Const || arg2_type==Underline)) {
		arg1_val = row[0];
		arg2_val = arg2_node->getValue();
	} else if (arg1_type==QuerySymbol && arg2_type==QuerySymbol){
		arg1_val = row[0];
		arg2_val = row[1];
	} else {
		return false;
	}

	if (arg1_val=="-1") {
		if (arg2_val=="-1") {
			if (isRelation(rlt, arg1_val, arg2_val)) {
				vector<string> new_row;
				new_row.push_back(arg1_val); new_row.push_back(arg2_val);
				new_rows->push_back(new_row);
			}
		} else if (arg2_val=="_") {
		
		} else {

		}
	} else if (arg1_val=="_") {
		if (arg2_val=="-1") {
		} else if (arg2_val=="_") {
			return true;
		} else {

		}
	} else {
		if (arg2_val=="-1") {
		} else if (arg2_val=="_") {
		
		} else {

		}
	}

	if (!new_rows->empty()) return true;
	return false;
}

bool QueryEvaluator::evaluatePTClause(TNode * PT_node, vector<string> row, vector<vector<string>> * new_rows) {

	if (!new_rows->empty()) return true;
	return false;
}

bool QueryEvaluator::evaluateWClause(TNode * W_node, vector<string> row, vector<vector<string>> * new_rows) {

	if (!new_rows->empty()) return true;
	return false;
}

bool QueryEvaluator::isRelation(Symbol relation, string arg1, string arg2) {
	switch (relation) {
	case Follows:
		{
			int stmt1 = atoi(arg1.c_str());
			int stmt2 = atoi(arg2.c_str());
			return PKB::isFollows(stmt1, stmt2);
		}
	case FollowsS:
		{
			int stmt1 = atoi(arg1.c_str());
			int stmt2 = atoi(arg2.c_str());
			return PKB::isFollowsStar(stmt1, stmt2);
		}
	case Parent:
		{
			int stmt1 = atoi(arg1.c_str());
			int stmt2 = atoi(arg2.c_str());
			return PKB::isParent(stmt1, stmt2);
		}
	case ParentS:
		{
			int stmt1 = atoi(arg1.c_str());
			int stmt2 = atoi(arg2.c_str());
			return PKB::isParentStar(stmt1, stmt2);
		}
	case Modifies:
		{
			string type = table.getType(arg1);
			if (SyntaxHelper::isStmtSymbol(type)) {
				int stmt = atoi(arg1.c_str());
				int varIndex = PKB::getVarIndex(arg2);
				return PKB::isModifies(stmt, varIndex);
			} else if (type==KEYWORD_PROCEDURE) {
				if (!PKB::getProcIndex(arg1).empty()) {
					int procIndex = PKB::getProcIndex(arg1).front();
					int varIndex = PKB::getVarIndex(arg2);
					return PKB::isModifiesProc(procIndex, varIndex);
				}			
			} else {
				return false;
			}
		}
	case Uses:
		{
			string type = table.getType(arg1);
			if (SyntaxHelper::isStmtSymbol(type)) {
				int stmt = atoi(arg1.c_str());
				int varIndex = PKB::getVarIndex(arg2);
				return PKB::isUses(stmt, varIndex);
			} else if (type==KEYWORD_PROCEDURE) {
				if (!PKB::getProcIndex(arg1).empty()) {
					int procIndex = PKB::getProcIndex(arg1).front();
					int varIndex = PKB::getVarIndex(arg2);
					return PKB::isUsesProc(procIndex, varIndex);
				}
			} else {
				return false;
			}
		}
	case Calls:
		{
			if (!PKB::getProcIndex(arg1).empty() &&
				!PKB::getProcIndex(arg2).empty()) {
				int proc1 = PKB::getProcIndex(arg1).front();
				int proc2 = PKB::getProcIndex(arg2).front();
				return PKB::isCalls(proc1, proc2);
			} else {
				return false;
			}
		}
	case CallsS:
		{
			if (!PKB::getProcIndex(arg1).empty() &&
				!PKB::getProcIndex(arg2).empty()) {
				int proc1 = PKB::getProcIndex(arg1).front();
				int proc2 = PKB::getProcIndex(arg2).front();
				return PKB::isCallStar(proc1, proc2);
			} else {
				return false;
			}
		}
	case Nexts:
		{
			int line1 = atoi(arg1.c_str());
			int line2 = atoi(arg2.c_str());
			return PKB::isNext(line1, line2);
		}
	case NextsS:
		{
			int line1 = atoi(arg1.c_str());
			int line2 = atoi(arg2.c_str());
			return PKB::isNextStar(line1, line2);
		}
	case Affects:
		{
			int line1 = atoi(arg1.c_str());
			int line2 = atoi(arg2.c_str());
			return PKB::isAffect(line1, line2);
		}
	case AffectsS:
		{
			int line1 = atoi(arg1.c_str());
			int line2 = atoi(arg2.c_str());
			return PKB::isAffectStar(line1, line2);
		}
	default:
		return false;
	}
}

vector<string> QueryEvaluator::getArgInRelation(Symbol relation, string arg1_type, string arg, int arg_unknown) {
	vector<string> results;

	switch(arg_unknown) {
	case ARG1_UNKNOWN:
		{
			switch(relation) {
			case Follows:
				{
					int stmt = atoi(arg.c_str());
					int result = PKB::getFollowedStmt(stmt);
					if (result!=-1) {
						results.push_back(to_string((long long)result));
					}
					break;
				}
			case FollowsS:
				{
					int stmt = atoi(arg.c_str());
					vector<int> r = PKB::getFollowedStarStmt(stmt);
					for (unsigned i=0; i<r.size(); i++) {
						results.push_back(to_string((long long)r[i]));
					}
					break;
				}
			case Parent:
				{
					int stmt = atoi(arg.c_str());
					int result = PKB::getParentStmt(stmt);
					if (result!=-1) {
						results.push_back(to_string((long long)result));
					}
					break;
				}
			case ParentS:
				{
					int stmt = atoi(arg.c_str());
					vector<int> r = PKB::getParentStarStmt(stmt);
					for (unsigned i=0; i<r.size(); i++) {
						results.push_back(to_string((long long)r[i]));
					}
					break;
				}
			case Modifies:
				{
					vector<int> r;
					if (arg1_type==KEYWORD_PROCEDURE) {
						r = PKB::getProcModifyingVar(proc);
					} else {
						int stmt = atoi(arg.c_str());
						r = PKB::getStmtModifyingVar(stmt);
					}
					for (unsigned i=0; i<r.size(); i++) {
						results.push_back(to_string((long long)r[i]));
					}
					break;
				}
			case Uses:
				{
					vector<int> r;
					int varIndex = PKB::getVarIndex(arg);
					string type = table.getType(arg);
					if (type==KEYWORD_PROC) {
						int proc = PKB::getProcIndex(arg);
						r = PKB::getUsedVarAtProc(proc);
					} else {
						int stmt = atoi(arg.c_str());
						r = PKB::getModifiedVarAtStmt(stmt);
					}
					for (unsigned i=0; i<r.size(); i++) {
						results.push_back(to_string((long long)r[i]));
					}
					break;
				}
			case Calls:
			case CallsS:
			case Nexts:
			case NextsS:
			case Affects:
			case AffectsS:
			default:
				break;
			}
		}
	case ARG2_UNKNOWN:
		{
			switch(relation) {
				case Follows:
				case FollowsS:
				case Parent:
				case ParentS:
				case Modifies:
				case Uses:
				case Calls:
				case CallsS:
				case Nexts:
				case NextsS:
				case Affects:
				case AffectsS:
				default:
					break;
			}
		}
	default:
		break;
	}

	return results;
}

vector<string> QueryEvaluator::extractResult() {
	vector<string> results;
	return results;
}

vector<string> QueryEvaluator::extractResult(TNode * result_node, ResultManager * rm, bool is_satisfied) {
	vector<string> results;
	return results;
}

vector<string> QueryEvaluator::getSymbolsUsedBy(TNode * node) {
	vector<string> results;
	return results;
}