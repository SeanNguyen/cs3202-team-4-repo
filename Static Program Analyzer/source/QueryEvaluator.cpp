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
				result_manager.maintain();
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

	if (arg1_type==Const && arg2_type==Const) {
		arg1_val = arg1_node->getValue();
		arg2_val = arg2_node->getValue();
	} else if (arg1_type==Const && arg2_type==QuerySymbol) {
		arg1_val = arg1_node->getValue();
		arg2_val = row[0];
	} else if (arg1_type==QuerySymbol && arg2_type==Const) {
		arg1_val = row[0];
		arg2_val = arg2_node->getValue();
	} else if (arg1_type==QuerySymbol && arg2_type==QuerySymbol){
		arg1_val = row[0];
		arg2_val = row[1];
	} else {
		return false;
	}

	if (arg1_val!="-1" && arg2_val!="-1") {
	} else if (arg1_val!="-1" && arg2_val=="-1") {
	} else if (arg1_val=="-1" && arg2_val!="-1") {
	} else {
	}

	if (!new_rows->empty()) return true;
	return false;
}

bool evaluatePTClause(TNode * PT_node, vector<string> row, vector<vector<string>> * new_rows) {

	if (!new_rows->empty()) return true;
	return false;
}

bool evaluateWClause(TNode * W_node, vector<string> row, vector<vector<string>> * new_rows) {

	if (!new_rows->empty()) return true;
	return false;
}

vector<string> QueryEvaluator::extractResult() {
	vector<string> results;
	return results;
}

vector<string> QueryEvaluator::extractResult(TNode * result_node, ResultManager * rm, bool is_satisfied) {
	vector<string> results;
	return results;
}