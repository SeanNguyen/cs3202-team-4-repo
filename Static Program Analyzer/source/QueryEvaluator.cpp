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
				{
					arg2_val = getIndexOfConst(arg2_node, rlt, ARG2);
					vector<int> arg1_vals = getArgInRelation(rlt, arg2_val, ARG1);
					if (!arg1_vals.empty()) return true;
					break;
				}
			case QuerySymbol:
				{
					// get stored value of arg2 in row

					if (arg2_val!=-1) {
						vector<int> arg1_vals = getArgInRelation(rlt, arg2_val, ARG1);
						if (!arg1_vals.empty()) return true;
					}
					break;
				}
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
				{
					vector<int> arg2_vals = getArgInRelation(rlt, arg1_val, ARG2);
					if (!arg2_vals.empty()) return true;
					break;
				}
			case Const:
				{
					arg2_val = getIndexOfConst(arg2_node, rlt, ARG2);
					return isRelation(rlt, arg1_val, arg2_val);
				}
			case QuerySymbol:
				{
					// get value of arg2 in row
					if (arg2_val!=-1) {
						return isRelation(rlt, arg1_val, arg2_val);
					}

					vector<int> arg2_vals = getArgInRelation(rlt, arg1_val, ARG2);
					// save new values of arg2 to new_rows
					break;
				}
			default:
				break;
			}
			break;
		}
	case QuerySymbol:
		{
			// get arg1_val in row
			switch (arg2_type) {
			case Underline:
				{
					if (arg1_val!=-1) {
						vector<int> arg2_vals = getArgInRelation(rlt, arg1_val, ARG2);
						if (!arg2_vals.empty()) return true;
					}
					break;
				}
			case Const:
				{
					arg2_val = getIndexOfConst(arg2_node, rlt, ARG2);
					if (arg1_val!=-1) {
						return isRelation(rlt, arg1_val, arg2_val);
					}
					vector<int> arg1_vals = getArgInRelation(rlt, arg2_val, ARG1);
					//save arg1_vals to new_rows
					break;
				}
			case QuerySymbol:
				{
					// get value of arg2 in row
					if (arg1_val!=-1 && arg2_val!=-1) {
						return isRelation(rlt, arg1_val, arg2_val);
					} else if (arg1_val!=-1 && arg2_val==-1) {
					} else if (arg1_val==-1 && arg2_val!=-1) {
					} else {
					}
					break;
				}
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
	TNode * stmt_node = PT_node->getChildAtIndex(0);
	string stmt_name = stmt_node->getValue();
	Symbol stmt_type = SyntaxHelper::getSymbolType(table.getType(stmt_name));
	int stmt_index; // get stmt_index from row

	if (stmt_index==-1) {
		// retrieve a list of values of stmt_type from PKB
		vector<int> stmt_indexes = getAllPKBValues(stmt_name);
		for (size_t i=0; i<stmt_indexes.size(); i++) {
			//save back stmt_indexes[i] to row
			//recursive call to update new_rows
			bool isSatisfied = evaluatePTClause(PT_node, row, new_rows);
			if (!isSatisfied) return false;
		}
	}

	// from here is hell of logic
	// get ASTNode of this Stmt 
	TNode * root = PKB::getASTRoot();
	AST tree; tree.setRoot(root);
	TNode * ast_node = tree.findNodeOfStmt(stmt_index);
	switch(stmt_type) {
	case Assign:
		{

			break;
		}
	case While:
	case If:
	default:
		break;
	}
	

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
		return PKB::isFollows(arg1, arg2);
	case FollowsS:
		return PKB::isFollowsStar(arg1, arg2);
	case Parent:	
		return PKB::isParent(arg1, arg2);
	case ParentS:
		return PKB::isParentStar(arg1, arg2);
	case Modifies:
		return PKB::isModifies(arg1, arg2);
	case ModifiesP:
		return PKB::isModifiesProc(arg1, arg2);
	case Uses:
		return PKB::isUses(arg1, arg2);
	case UsesP:
		return PKB::isModifiesProc(arg1, arg2);
	case Calls:
		return PKB::isCalls(arg1, arg2);
	case CallsS:
		return PKB::isCallStar(arg1, arg2);
	case Nexts:
		return PKB::isNext(arg1, arg2);
	case NextsS:
		return PKB::isNextStar(arg1, arg2);
	case Affects:
		return PKB::isAffect(arg1, arg2);
	case AffectsS:
		return PKB::isAffectStar(arg1, arg2);
	default:
		return false;
	}
}

vector<int> QueryEvaluator::getArgInRelation(Symbol relation, int arg, int arg_unknown) {
	vector<int> results;

	switch(relation) {
	case Follows:
		{
			if (arg_unknown==ARG1) {
				results.push_back(PKB::getFollowedStmt(arg));
			} else {
				results.push_back(PKB::getFollowingStmt(arg));
			}
			break;
		}
	case FollowsS:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getFollowedStarStmt(arg);
			} else {
				results = PKB::getFollowingStarStmt(arg);
			}		
			break;
		}
	case Parent:
		{
			if (arg_unknown==ARG1) {
				results.push_back(PKB::getParentStmt(arg));
			} else {
				results = PKB::getChildStmt(arg);
			}
			break;
		}
	case ParentS:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getParentStarStmt(arg);
			} else {
				results = PKB::getChildStarStmt(arg);
			}
			break;
		}
	case Modifies:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getStmtModifyingVar(arg);
			} else {
				results = PKB::getModifiedVarAtStmt(arg);
			}
			break;
		}
	case ModifiesP:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getProcModifyingVar(arg);
			} else {
				results = PKB::getModifiedVarAtProc(arg);
			}
			break;
		}
	case Uses:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getStmtUsingVar(arg);
			} else {
				results = PKB::getUsedVarAtStmt(arg);
			}
			break;
		}
	case UsesP:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getProcUsingVar(arg);
			} else {
				results = PKB::getUsedVarAtProc(arg);
			}
			break;
		}
	case Calls:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getCalledByProc(arg);
			} else {
				results = PKB::getCallingProc(arg);
			}
			break;
		}
	case CallsS:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getCalledByStarProc(arg);
			} else {
				results = PKB::getCallingStarProc(arg);
			}
			break;
		}
	case Nexts:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getPreviousStmts(arg);
			} else {
				results = PKB::getNextStmts(arg);
			}
			break;
		}
	case NextsS:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getPreviousStarStmts(arg);
			} else {
				results = PKB::getNextStarStmts(arg);
			}
			break;
		}
	case Affects:
		{
			if (arg_unknown==ARG1) {
				results = PKB::getAffected(arg);
			} else {
				results = PKB::getAffecting(arg);
			}
			break;
		}
	case AffectsS:
		{
			if (arg_unknown==ARG1) {
				//results = PKB::getAffectedStar(arg);
			} else {
				//results = PKB::getAffectingStar(arg);
			}
			break;
		}
	default:
		break;
	}
	
	if (find(results.begin(), results.end(), -1)==results.end()) {
		// results has invalid value, i.e -1
		results.clear(); 
	}

	return results;
}

vector<string> QueryEvaluator::extractResult() {
	vector<string> results;
	return results;
}

vector<string> QueryEvaluator::extractResult(TNode * result_node, ResultManager * rm, bool is_satisfied) {
	vector<string> results;

	string result_type = result_node->getValue();

	if(!is_satisfied) {
		if (result_type=="0-BOOLEAN") 
			results.push_back("false");
	} 

	if (result_type=="0-BOOLEAN") {
		results.push_back("true");
	} else {
		vector<string> symbols = getSymbolsUsedBy(result_node);
		// extract data
		ResultTable * r_table = rm->extractTable(symbols);
		// fill empty column
		fillResultTable(r_table);
		// save data to results list
		fillResultList(result_node, r_table, &results);
	}

	return results;
}

vector<string> QueryEvaluator::getSymbolsUsedBy(TNode * node) {
	vector<string> results;

	int size = node->getNumChildren();
	for (int i=0; i<size; i++) {
		TNode * child = node->getChildAtIndex(0);
		if (child->getType()==QuerySymbol) {
			results.push_back(child->getValue());
		}
		vector<string> sub_results = getSymbolsUsedBy(child);
		for (size_t j=0; j<sub_results.size(); j++) {
			if (find(results.begin(), results.end(), sub_results[i])==results.end())
				results.push_back(sub_results[i]);
		}
 	}

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

			if (arg_index==ARG1) {
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

void QueryEvaluator::fillResultTable(ResultTable * table) {
	// base case
	if (table->getSymbolSize()==1 && table->getSize()==0) {
		string symbol = table->getSymbol(0);
		vector<int> values = getAllPKBValues(symbol);
		for (size_t i=0; i<values.size(); i++) {
			vector<int> row; row.push_back(values[i]);
			table->insertValRow(row);
		}
	}

	// get symbols with unknown values
	vector<string> unknown_symbols = getUnknownSymbols(table);
	ResultManager rm;
	// go to base case for each symbol and merge back to the table
	for (size_t i=0; i<unknown_symbols.size(); i++) {
		ResultTable * sub_table; sub_table->insertSymbol(unknown_symbols[i]); 
		fillResultTable(sub_table);
		table = rm.mergeTables(table, sub_table);
	}
}

void QueryEvaluator::fillResultList(TNode * result_node, ResultTable * table, vector<string> * results) {
	for (int i=0; i<table->getSize(); i++) {
		vector<int> row = table->getValRow(i);
		string result = fillResult(result_node, row);
		results->push_back(result);
	}
}

string QueryEvaluator::fillResult(TNode * result_node, vector<int> values) {
	string result = "";
	for (size_t i=0; i<values.size(); i++) {
		TNode * node = result_node->getChildAtIndex(i);
		string str = fillResult(node, values[i]);
		if (values.size()==1) { result = str; }
		else { result += str + " "; }
	}
	return result;
}

string QueryEvaluator::fillResult(TNode * node, int value) {
	string name = node->getValue();
	string type = table.getType(name);
	
	// special case
	if (type==KEYWORD_CALL) {
		if (node->getNumChildren()!=0) {
			TNode * attr = node->getChildAtIndex(0);
			if (attr->getType()==Attr &&
				attr->getValue()=="procName") {
					value = PKB::getCalledProc(value);
					type=KEYWORD_PROCEDURE;
			}
		}
	}

	if (type==KEYWORD_PROCEDURE) {
		return PKB::getProcName(value);
	} else if (type==KEYWORD_VAR) {
		return PKB::getVarName(value);
	} else if (type==KEYWORD_CONST) {
		return PKB::getConstName(value);
	} else if (type==KEYWORD_PROG_LINE || SyntaxHelper::isStmtSymbol(type)) {
		return to_string((long long)value); 
	} else {
	}
	return "-1";
}

vector<int> QueryEvaluator::getAllPKBValues(string name) {
	vector<int> result;
	string type = table.getType(name);
	if (type==KEYWORD_PROCEDURE) {
		for (int i=0; i<PKB::getProcTableSize(); i++) {
			result.push_back(i);
		}
	} else if (type==KEYWORD_VAR) {
		for (int i=0; i<PKB::getVarTableSize(); i++) {
			result.push_back(i);
		}
	} else if (type==KEYWORD_CONST) {
		for (int i=0; i<PKB::getConstTableSize(); i++) {
			result.push_back(i);
		}
	} else if (type==KEYWORD_PROG_LINE || type==KEYWORD_STMT) {
		for (int i=0; i<PKB::getStatTableSize(); i++) {
			result.push_back(i);
		}
	} else if (type==KEYWORD_ASSIGN) {
		result = PKB::getStmtIndex(KEYWORD_ASSIGN);
	} else if (type==KEYWORD_WHILE) {
		result = PKB::getStmtIndex(KEYWORD_WHILE);
	} else if (type==KEYWORD_IF) {
		result = PKB::getStmtIndex(KEYWORD_IF);
	} else if (type==KEYWORD_CALL) {
		result = PKB::getStmtIndex(KEYWORD_CALL);
	} else {
	}
	return result;
}

vector<string> QueryEvaluator::getUnknownSymbols(ResultTable * table) {
	vector<string> result;

	for (int i=0; i<table->getSize(); i++) {
		vector<int> row = table->getValRow(i);
		for (size_t j=0; j<row.size(); j++) {
			if (row[j]==-1 && 
				find(result.begin(), result.end(), table->getSymbol(i))==result.end()) 
				result.push_back(table->getSymbol(i));
		}
	}

	return result;
}