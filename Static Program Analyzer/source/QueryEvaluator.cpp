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
		vector<int> row = temp_results->getValRow(i);
		vector<vector<int>> new_rows;
		is_satisfied = evaluateClause(clause_node, row, &new_rows);
		if (!is_satisfied) {
			return is_satisfied;
		}
		temp_results->insertValRow(new_rows);
	}
	temp_results->deleleInvalidRows();
	return is_satisfied;
}

bool QueryEvaluator::evaluateClause(TNode * clause_node, vector<int> row, vector<vector<int>> * new_rows) {
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
									vector<int> row, 
									vector<vector<int>> * new_rows) {
	TNode * rlt_node = ST_node->getChildAtIndex(0);
	TNode * arg1_node = rlt_node->getChildAtIndex(0);
	TNode * arg2_node = rlt_node->getChildAtIndex(1);

	Symbol rlt = rlt_node->getType();
	Symbol arg1_type = arg1_node->getType();
	Symbol arg2_type = arg2_node->getType();
	int arg1_val; int arg2_val;

	switch (arg1_type) {
	case Underline:
		{
			switch (arg2_type) {
			case Underline:
				return true;
			case Const:
			case QuerySymbol:
			default:
				break;
			}
			break;
		}
	case Const:
		{
			arg1_val = getIndexOfConst(arg1_node, rlt, ARG1);
			switch (arg2_type) {
			case Underline:
			case Const:
				{
					arg2_val = getIndexOfConst(arg2_node, rlt, ARG2);
					return isRelation(rlt, arg1_val, arg2_val);
				}
			case QuerySymbol:
			default:
				break;
			}
			break;
		}
	case QuerySymbol:
		{
			switch (arg2_type) {
			case Underline:
			case Const:
			case QuerySymbol:
			default:
				break;
			}
			break;
		}
	default:
		break;
	}

	if (!new_rows->empty()) return true;
	return false;
}

bool QueryEvaluator::evaluatePTClause(TNode * PT_node, vector<int> row, vector<vector<int>> * new_rows) {

	if (!new_rows->empty()) return true;
	return false;
}

bool QueryEvaluator::evaluateWClause(TNode * W_node, vector<int> row, vector<vector<int>> * new_rows) {

	if (!new_rows->empty()) return true;
	return false;
}

bool QueryEvaluator::isRelation(Symbol relation, int arg1, int arg2) {
	switch (relation) {
	case Follows:
		{
			return PKB::isFollows(arg1, arg2);
		}
	case FollowsS:
		{
			return PKB::isFollowsStar(arg1, arg2);
		}
	case Parent:
		{
			return PKB::isParent(arg1, arg2);
		}
	case ParentS:
		{
			return PKB::isParentStar(arg1, arg2);
		}
	case Modifies:
		{
			string type = table.getType(arg1);
			if (SyntaxHelper::isStmtSymbol(type)) {
				return PKB::isModifies(arg1, arg2);
			} else if (type==KEYWORD_PROCEDURE) {
				return PKB::isModifiesProc(arg1, arg2);
			} else {
				return false;
			}
		}
	case Uses:
		{
			string type = table.getType(arg1);
			if (SyntaxHelper::isStmtSymbol(type)) {
				return PKB::isUses(arg1, arg2);
			} else if (type==KEYWORD_PROCEDURE) {
				return PKB::isUsesProc(arg1, arg2);
			} else {
				return false;
			}
		}
	case Calls:
		{
			return PKB::isCalls(arg1, arg2);
		}
	case CallsS:
		{
			return PKB::isCallStar(arg1, arg2);
		}
	case Nexts:
		{
			return PKB::isNext(arg1, arg2);
		}
	case NextsS:
		{
			return PKB::isNextStar(arg1, arg2);
		}
	case Affects:
		{
			return PKB::isAffect(arg1, arg2);
		}
	case AffectsS:
		{
			return PKB::isAffectStar(arg1, arg2);
		}
	default:
		return false;
	}
}

vector<string> QueryEvaluator::getArgInRelation(Symbol relation, string arg1_type, int arg, int arg_unknown) {
	vector<string> results;

	switch(arg_unknown) {
	case ARG1:
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
	case ARG2:
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

int QueryEvaluator::getIndexOfConst(TNode * const_node, Symbol relation, int arg_index) {
	string val = const_node->getValue();
	switch (relation) {
	case Follows:
	case FollowsS:
	case Parent:
	case ParentS:
		return atoi(val.c_str());
	case Modifies:
	case Uses:
		{
			if (isNumber(val)) 
				return atoi(val.c_str());

			if (arg==ARG1) {
				if (!PKB::getProcIndex(val).empty())
					return PKB::getProcIndex(val).front();
				return -1;
			} else {
				return PKB::getVarIndex(val);
			}
		}
	case Calls:
	case CallsS:
		{
			if (isNumber(val)) 
				return atoi(val.c_str());
			if (!PKB::getProcIndex(val).empty())
				return PKB::getProcIndex(val).front();
			return -1;
		}
	case Nexts:
	case NextsS:
	case Affects:
	case AffectsS:
		return atoi(val.c_str());
	default:
		return -1;
	}
	return -1;
}

bool QueryEvaluator::isNumber(string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}