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
	if (size==0) {
		// insert a dummy row into temp_results
		int symbol_num = temp_results->getSymbolSize();
		vector<int> dummy_values (symbol_num, -1);
		temp_results->insertValRow(dummy_values);
		size = 1;
	}
	for (int i=0; i<size; i++) {
		vector<int> row = temp_results->getValRow(i);
		vector<vector<int>> new_rows;
		is_satisfied = evaluateClause(clause_node, row, &new_rows);
		if (is_satisfied) {
			temp_results->insertValRow(new_rows);
		}
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
	string type1 = table.getType(arg1_node->getValue());
	string type2 = table.getType(arg2_node->getValue());
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
					arg2_val = row[0];
					if (arg2_val!=-1) {
						vector<int> arg1_vals = getArgInRelation(rlt, arg2_val, ARG1);
						if (!arg1_vals.empty()) return true;
						break;
					}

					vector<int> arg2_vals = getAllPKBValues(type2);
					for (size_t i=0; i<arg2_vals.size(); i++) {
						vector<int> arg1_vals = getArgInRelation(rlt, arg2_vals[i], ARG1);
						if (!arg1_vals.empty()) {
							row[0] = arg2_vals[i];
							new_rows->push_back(row);
						}
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
					arg2_val = row[0];
					if (arg2_val!=-1) {
						return isRelation(rlt, arg1_val, arg2_val);
						break;
					}
					vector<int> arg2_vals = getArgInRelation(rlt, arg1_val, ARG2);
					arg2_vals = removeInvalidValues(arg2_vals, arg2_node->getValue());
					// save new values of arg2 to new_rows
					for (size_t i=0; i<arg2_vals.size(); i++) {
						row[0] = arg2_vals[i];
						new_rows->push_back(row);
					}
					break;
				}
			default:
				break;
			}
			break;
		}
	case QuerySymbol:
		{
			arg1_val = row[0];
			switch (arg2_type) {
			case Underline:
				{
					if (arg1_val!=-1) {
						vector<int> arg2_vals = getArgInRelation(rlt, arg1_val, ARG2);
						if (!arg2_vals.empty()) return true;
						break;
					}
					vector<int> arg1_vals = getAllPKBValues(type1);
					for (size_t i=0; i<arg1_vals.size(); i++) {
						vector<int> arg2_vals = getArgInRelation(rlt, arg1_vals[i], ARG1);
						if (!arg2_vals.empty()) {
							row[0] = arg1_vals[i];
							new_rows->push_back(row);
						}
					}
					break;
				}
			case Const:
				{
					arg2_val = getIndexOfConst(arg2_node, rlt, ARG2);
					if (arg1_val!=-1) {
						return isRelation(rlt, arg1_val, arg2_val);
						break;
					} 
					vector<int> arg1_vals = getArgInRelation(rlt, arg2_val, ARG1);
					arg1_vals = removeInvalidValues(arg1_vals, arg1_node->getValue());
					//save arg1_vals to new_rows
					for (size_t i=0; i<arg1_vals.size(); i++) {
						row[0] = arg1_vals[i];
						new_rows->push_back(row);
					}
					break;
				}
			case QuerySymbol:
				{
					// get value of arg2 in row
					arg2_val = row[1];
					if (arg1_val!=-1 && arg2_val!=-1) {
						return isRelation(rlt, arg1_val, arg2_val);
					} else if (arg1_val!=-1 && arg2_val==-1) {
						vector<int> arg2_vals = getArgInRelation(rlt, arg1_val, ARG2);
						arg2_vals = removeInvalidValues(arg2_vals, arg2_node->getValue());
						for (size_t i=0; i<arg2_vals.size(); i++) {
							row[0] = arg2_vals[i];
							new_rows->push_back(row);
						}
					} else if (arg1_val==-1 && arg2_val!=-1) {
						vector<int> arg1_vals = getArgInRelation(rlt, arg2_val, ARG1);
						arg1_vals = removeInvalidValues(arg1_vals, arg1_node->getValue());
						for (size_t i=0; i<arg1_vals.size(); i++) {
							row[0] = arg1_vals[i];
							new_rows->push_back(row);
						}
					} else {
						vector<int> arg1_vals = getAllPKBValues(arg1_node->getValue());
						for (size_t i=0; i<arg1_vals.size(); i++) {
							vector<int> arg2_vals = getArgInRelation(rlt, arg1_vals[i], ARG2);
							arg2_vals = removeInvalidValues(arg2_vals, arg2_node->getValue());
							for (size_t j=0; j<arg2_vals.size(); j++) {
								row[0] = arg1_vals[i]; row[1] = arg2_vals[j];
								new_rows->push_back(row);
							}
						}
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
	int stmt_index=row[0]; // get stmt_index from row

	if (stmt_index==-1) {
		// retrieve a list of values of stmt_type from PKB
		vector<int> stmt_indexes = getAllPKBValues(stmt_name);
		for (size_t i=0; i<stmt_indexes.size(); i++) {
			//save back stmt_indexes[i] to row
			row[0] = stmt_indexes[i];
			//recursive call to update new_rows
			vector<vector<int>> rows;
			bool isSatisfied = evaluatePTClause(PT_node, row, &rows);
			if (isSatisfied) {
				for (size_t j=0; j<rows.size(); j++) {
					new_rows->push_back(rows[j]);
				}
			}
		}
	} else {
		// from here is hell of logic
		// get ASTNode of this Stmt
		TNode * root = PKB::getASTRoot();
		AST tree; tree.setRoot(root);
		TNode * ast_node = tree.findNodeOfStmt(stmt_index);
	
		// handle first argument node
		TNode * arg1_node = stmt_node->getChildAtIndex(0);
		if (!evaluatePTArgNode(arg1_node, ast_node, ARG1, row, new_rows)) 
			return false; 

		switch(stmt_type) {
		case Assign:
			{
				TNode * expr_node = stmt_node->getChildAtIndex(1);
				if (!evaluateExprNode(expr_node, ast_node)) return false;
				return true;
			}
		case While:
			{

				break;
			}
		case If:
			{

				break;
			}
		default:
			break;
		}
	}
	if (!new_rows->empty()) return true;
	return false;
}

bool QueryEvaluator::evaluateWClause(TNode * W_node, vector<int> row, vector<vector<int>> * new_rows) {
	TNode * arg1_node = W_node->getChildAtIndex(0);
	TNode * arg2_node = W_node->getChildAtIndex(1);
	Symbol arg1_type = arg1_node->getType();
	Symbol arg2_type = arg2_node->getType();
	string arg1_val = arg1_node->getValue();
	string arg2_val = arg2_node->getValue();

	if (arg1_type==Const && arg2_type==Const) {
		return arg1_val==arg2_val;
	} else if (arg1_type==Const && arg2_type==QuerySymbol) {
		arg2_val = getAttrValue(arg2_node, row[0]);
		if (arg2_val!="-1") {
			return arg1_val==arg2_val;
		} else {
			vector<int> arg2_indexes = getAttrIndex(arg2_node, arg1_val);
			for (size_t i=0; i<arg2_indexes.size(); i++) {
				row[0] = arg2_indexes[i];
				new_rows->push_back(row);
			}
		}
	} else if (arg1_type==QuerySymbol && arg2_type==Const) {
		arg1_val = getAttrValue(arg1_node, row[0]);
		if (arg1_val!="-1") {
			return arg1_val==arg2_val;
		} else {
			vector<int> arg1_indexes = getAttrIndex(arg1_node, arg2_val);
			for (size_t i=0; i<arg1_indexes.size(); i++) {
				row[0] = arg1_indexes[i];
				new_rows->push_back(row);
			}
		}
	} else {
		arg1_val = getAttrValue(arg1_node, row[0]);
		arg2_val = getAttrValue(arg2_node, row[1]);
		if (arg1_val!="-1" && arg2_val!="-1") {
			return arg1_val==arg2_val;
		} else if (arg1_val!="-1" && arg2_val=="-1") {
			vector<int> arg2_indexes = getAttrIndex(arg2_node, arg1_val);
			for (size_t i=0; i<arg2_indexes.size(); i++) {
				row[1] = arg2_indexes[i];
				new_rows->push_back(row);
			}
		} else if (arg1_val=="-1" && arg2_val!="-1") {
			vector<int> arg1_indexes = getAttrIndex(arg1_node, arg2_val);
			for (size_t i=0; i<arg1_indexes.size(); i++) {
				row[0] = arg1_indexes[i];
				new_rows->push_back(row);
			}
		} else {
			// get all possible values of arg1
			arg1_val = arg1_node->getValue();
			vector<int> arg1_indexes = getAllPKBValues(arg1_val);
			for (size_t i=0; i<arg1_indexes.size(); i++) {
				arg1_val = getAttrValue(arg1_node, arg1_indexes[i]);
				vector<int> arg2_indexes = getAttrIndex(arg2_node, arg1_val);
				for (size_t j=0; j<arg2_indexes.size(); j++) {
					row[0] = arg1_indexes[i];
					row[1] = arg2_indexes[j];
					new_rows->push_back(row);
				}
			}
		}
	}
	
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

	if (find(results.begin(), results.end(), -1)!=results.end()) {
		// results has invalid value, i.e -1
		results.clear(); 
	}

	return results;
}

bool QueryEvaluator::evaluatePTArgNode(TNode * arg_node, TNode * ast_node, int arg_index,
			vector<int> row, vector<vector<int>> * new_rows) {
	Symbol arg_type= arg_node->getType();
	string arg_name = arg_node->getValue();

	switch (arg_type) {
	case Underline: 
		{
			new_rows->push_back(row);
			return true;
		}
	case Const:
		{
			switch (arg_index) {
			case ARG1:
				{
					TNode * ast_child1 = ast_node->getChildAtIndex(0);
					string val = ast_child1->getValue();
					if (arg_name==val) {
						new_rows->push_back(row);
						return true;
					}
					return false;
				}
			default:
				// currently left for ARG2 and ARG3 of if and while stmt
				break;
			}
			break;
		}
	case QuerySymbol:
		{
			switch (arg_index) {
			case ARG1:
				{
					TNode * ast_child1 = ast_node->getChildAtIndex(0);
					string val = ast_child1->getValue();
					int index = PKB::getVarIndex(val);
					if (row[1]==-1 || row[1]==index) {
						row[1] = index;
						new_rows->push_back(row);
						return true;
					}
					return false;
				}
			default:
				// currently left for ARG2 and ARG3 of if and while stmt
				break;
			}
			break;
		}
	default:
		break;
	}

	return false;
}

bool QueryEvaluator::evaluateExprNode(TNode * expr_node, TNode * ast_node) {
	Symbol expr_type = expr_node->getType();

	switch (expr_type) {
	case Underline:
		{
			if (expr_node->getNumChildren()==0) return true;
			AST sub_ast; sub_ast.setRoot(ast_node->getChildAtIndex(1));
			Tree sub_tree; sub_tree.setRoot(expr_node->getChildAtIndex(0));
			return sub_ast.hasSubTree(sub_tree);
		}
	case No_Underline:
		{
			AST sub_ast; sub_ast.setRoot(ast_node->getChildAtIndex(1));
			Tree sub_tree; sub_tree.setRoot(expr_node->getChildAtIndex(0));
			return sub_ast.isSameTree(sub_tree);
		}
	default:
		break;
	}
	return false;
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
	} else {
		if (result_type=="0-BOOLEAN") {
			results.push_back("true");
		} else {
			vector<string> symbols = getSymbolsUsedBy(result_node);
			// extract data
			ResultTable * r_table = rm->extractTable(symbols);
			// fill empty column
			cout << "CHECKPOINT 001 " <<endl;
			fillResultTable(r_table);
			// save data to results list
			cout << "CHECKPOINT 002 " <<endl;
			fillResultList(result_node, r_table, &results);
			cout << "CHECKPOINT 003 " <<endl;
		}
	}

	return results;
}

vector<string> QueryEvaluator::getSymbolsUsedBy(TNode * node) {
	vector<string> results;

	int size = node->getNumChildren();
	for (int i=0; i<size; i++) {
		TNode * child = node->getChildAtIndex(i);
		if (child->getType()==QuerySymbol) {
			results.push_back(child->getValue());
		}
		vector<string> sub_results = getSymbolsUsedBy(child);
		for (size_t j=0; j<sub_results.size(); j++) {
			if (find(results.begin(), results.end(), sub_results[j])==results.end())
				results.push_back(sub_results[j]);
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
		ResultTable * sub_table = new ResultTable(); sub_table->insertSymbol(unknown_symbols[i]); 
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
		cout << "CHECKPOINT " << i << " " << values[i] <<endl;
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
	cout << "CHECKPOINT " + name + " " + type + " " << value <<endl;
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
		for (int i=1; i<PKB::getStatTableSize(); i++) {
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

string QueryEvaluator::getAttrValue(TNode * node, int index) {
	string result = "-1";

	if (index==-1) return result;

	string symbol_name = node->getValue();
	Symbol symbol_type = SyntaxHelper::getSymbolType(table.getType(symbol_name));

	switch(symbol_type) {
	case Procedure:
		{
			result = PKB::getProcName(index);
			break;
		}
	case Var:
		{
			result = PKB::getVarName(index);
			break;
		}
	case Const:
		{
			result = PKB::getConstName(index);
			break;
		}
	case Stmt:
	case Prog_line:
	case Assign:
	case While:
	case If:
	case CallStmt:
		{
			if (symbol_type==CallStmt) {
				TNode * attr = node->getChildAtIndex(0);
				if (attr->getValue()=="procName") {
					result = PKB::getProcName(PKB::getCalledProc(index));
				} else {
					result = to_string((long long)index);
				}
			} else {
				result = to_string((long long)index);
			}
			break;
		}
	default:
		break;
	}

	return result;
}

vector<int> QueryEvaluator::getAttrIndex(TNode * node, string attr_value) {
	vector<int> result;

	string symbol_name = node->getValue();
	Symbol symbol_type = SyntaxHelper::getSymbolType(table.getType(symbol_name));

	if (symbol_type==CallStmt) {
		TNode * attr = node->getChildAtIndex(0);
		if (attr->getValue()=="procName") {
			result = PKB::getCallingStmt(PKB::getProcIndex(attr_value).front());
			return result;
		}
	}

	switch(symbol_type) {
	case Procedure:
		{
			result.push_back(PKB::getProcIndex(attr_value).front());
			break;
		}
	case Var:
		{
			result.push_back(PKB::getVarIndex(attr_value));
			break;
		}
	case Const:
		{
			result.push_back(PKB::getConstIndex(attr_value));
			break;
		}
	case Prog_line:
	case Stmt:
	case Assign:
	case If:
	case While:
	case CallStmt:
		{
			result.push_back(atoi(attr_value.c_str()));
			break;
		}
	default:
		break;
	}

	return result;
}

vector<int> QueryEvaluator::removeInvalidValues(vector<int> values, string symbol_name) {
	vector<int> result;
	string symbol_type = table.getType(symbol_name);
	Symbol type = SyntaxHelper::getSymbolType(symbol_type);
	for (size_t i=0; i<values.size(); i++) {
		bool isCorrectType = false;
		int value = values[i];
		switch (type) {
		case Procedure:
			isCorrectType = (PKB::getProcName(value)!="");
			break;
		case Var:
			isCorrectType = (PKB::getVarName(value)!="");
			break;
		case Const:
			isCorrectType = (PKB::getConstName(value)!="");
			break;
		case Prog_line:
		case Stmt:
			isCorrectType = (PKB::getStatTableSize()>value);
			break;
		case Assign:
			isCorrectType = (PKB::getStmtName(value)==KEYWORD_ASSIGN);
			break;
		case While:
			isCorrectType = (PKB::getStmtName(value)==KEYWORD_WHILE);
			break;
		case If:
			isCorrectType = (PKB::getStmtName(value)==KEYWORD_IF);
			break;
		case CallStmt:
			isCorrectType = (PKB::getStmtName(value)==KEYWORD_CALL);
			break;
		default:
			break;
		}
		if (isCorrectType && value>0) 
			result.push_back(values[i]);
	}
	return result;
}