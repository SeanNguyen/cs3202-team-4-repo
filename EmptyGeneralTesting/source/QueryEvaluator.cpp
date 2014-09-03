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
		if (AbstractWrapper::GlobalStop) {
			// do cleanup
			return;
		}
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

	TNode root = tree.getRoot();

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
	TNode child = root.getChildAtIndex(childIndex);
	if (child.getValue()=="suchThat") {
		// find values satisfying such that condition
		checkSuchThatCondition(child, values, result, check, childIndex);
	}

	if (child.getValue()=="pattern") {
		// find values satisfying pattern condition
		checkPatternCondition(child, values, result, check, childIndex);
	}
}
	
void QueryEvaluator::checkSuchThatCondition(TNode suchThatNode, vector<string> values, vector<string>& result, bool check, int childIndex) {
	// at this point we must check if result list has the value saved in value list or not

	// get root node
	TNode root = tree.getRoot();

	// get relationship node under suchThat node
	TNode relationNode = suchThatNode.getChildAtIndex(0); 
	string relation = relationNode.getValue();
	
	// from here, there are following cases:
	if (relation=="Follows") {
		handleFollowsRelationship(relationNode, suchThatNode, values, result, check, childIndex	);
	} else if (relation=="Follows*") {
		handleFollowsSRelationship(relationNode, suchThatNode, values, result, check, childIndex);
	} else if (relation=="Parent") {
		handleParentRelationship(relationNode, suchThatNode, values, result, check, childIndex);
		return;
	} else if (relation=="Parent*") {
		handleParentSRelationship(relationNode, suchThatNode, values, result, check, childIndex);
	} else if (relation=="Modifies") {
		handleModifiesRelationship(relationNode, suchThatNode, values, result, check, childIndex);
	} else if (relation=="Uses") {
		handleUsesRelationship(relationNode, suchThatNode, values, result, check, childIndex);
	}
}

void QueryEvaluator::handleFollowsRelationship(TNode relationNode, TNode suchThatNode, vector<string> values, vector<string>& result, bool check, int childIndex) {
// get child nodes
		TNode arg1Node = relationNode.getChildAtIndex(0);
		string arg1Type = arg1Node.getType();
		string arg1Value = arg1Node.getValue();
		TNode arg2Node = relationNode.getChildAtIndex(1);
		string arg2Type = arg2Node.getType();
		string arg2Value = arg2Node.getValue();
		int arg1Num; int arg2Num;

		// there are following cases:

		// IF ARGUMENT 1 OF RELATIONSHIP FOLLOWS IS A NUMBER, eg Follows(1, 2) or Follows (1, s)
		if (arg1Type=="number") {
			arg1Num = atoi(arg1Value.c_str());
			// IF ARGUMENT 2 IS A NUMBER
			if (arg2Type=="number") {
				arg2Num = atoi(arg2Value.c_str());
				if (!PKB::isFollows(arg1Num, arg2Num)) {
					check = false;
					// RETURN TO THE PREVIOUS METHOD TO UPDATE THAT THIS VALUE LIST DOES NOT SATISFY THE CONDITIONS
					checkQueryCondition(childIndex+1, values, result, check);
				} 
				// RETURN TO THE PREVIOUS METHOD TO CONTINUE WITH NEXT CONDITION (by adding the increment)
				checkQueryCondition(childIndex+1, values, result, check);
			}

			// IF ARGUMENT 2 IS A SYMBOL
			if (arg2Type=="symbol") {
				
				// get values of this symbol from vector "values"
				int index = table.getIndex(arg2Value);
				// IF WE ALREADY STORE A VALUE OF ARGUMENT 2 
				// WHEN PROCESSING A PREVIOUS CONDITION
				if (values[index]!="-1") {
					arg2Num = atoi(values[index].c_str());
					if (!PKB::isFollows(arg1Num, arg2Num)) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					} 
					checkQueryCondition(childIndex+1, values, result, check);
				}
				// IF NO VALUE OF ARGUMENT 2 WAS STORED
				else {
					arg2Num = PKB::getFollowingStmt(arg1Num);
					if (arg2Num==-1) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}
					// update values
					if (!isDeclaredType(intToString(arg2Num), arg2Value, arg2Type)) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}

					values[index] = intToString(arg2Num);
					checkQueryCondition(childIndex+1, values, result, check);
				}
			}
		}
		// IF ARGUMENT 1 IS A SYMBOL, eg Follows(s, 12)
		else if (arg1Type=="symbol"){
			// get values of this symbol from vector "values"
			int index = table.getIndex(arg1Value);
			// IF THERE WAS STORED VALUE OF ARGUMENT 1
			if (values[index]!="-1") {
			arg1Num = atoi(values[index].c_str());

				// IF ARGUMENT 2 IS A NUMBER 
				if (arg2Type=="number") {
					arg2Num = atoi(arg2Value.c_str());
					if (!PKB::isFollows(arg1Num, arg2Num)) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
					}
					checkQueryCondition(childIndex+1, values, result, check);
				} 
				// IF ARGUMENT 2 IS A SYMBOL
				else {
					int index2 = table.getIndex(arg2Value);
					// if arg2 has value stored
					if (values[index2]!="-1") {
						arg2Num = atoi(values[index2].c_str());
						if (!PKB::isFollows(arg1Num, arg2Num)) {
							check = false;
							checkQueryCondition(childIndex+1, values, result, check);
						}
						checkQueryCondition(childIndex+1, values, result, check);
					}
					// if arg2 has no value yet
					else {
						int arg2Num = PKB::getFollowingStmt(arg1Num);
						if (arg2Num==-1) {
							check = false;
							checkQueryCondition(childIndex+1, values, result, check);
							return;
						}

						if (!isDeclaredType(intToString(arg2Num), arg2Value, arg2Type)) {
							check = false;
							checkQueryCondition(childIndex+1, values, result, check);
							return;
						}

						values[index2] = intToString(arg2Num);
						checkQueryCondition(childIndex+1, values, result, check);
					}
				}
			} 
			// IF THERE IS NO VALUE STORED FOR ARGUMENT 1
			else {
				// IF ARGUMENT 2 IS A NUMBER
				if (arg2Type=="number") {
					arg2Num = atoi(arg2Value.c_str());
					arg1Num = PKB::getFollowedStmt(arg2Num);
					if (arg1Num==-1) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}

					if (!isDeclaredType(intToString(arg1Num), arg1Value, table.getType(arg1Value))) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}

					// save value of argument 1 to values list and call checkQueryCondition
					values[index] = intToString(arg1Num);
					checkQueryCondition(childIndex+1, values, result, check);
				} else {
					int index2 = table.getIndex(arg2Value);
					// IF THERE IS VALUE STORED FOR ARGUMENT 2
					if (values[index2]!="-1") {
						arg2Num = atoi(values[index2].c_str());
						arg1Num = PKB::getFollowedStmt(arg2Num);
						if (arg1Num==-1) {
							check = false;
							checkQueryCondition(childIndex+1, values, result, check);
							return;
						}

						if (!isDeclaredType(intToString(arg1Num), arg1Value, arg1Type)) {
							check = false;
							checkQueryCondition(childIndex+1, values, result, check);
							return;
						}

						// save value of argument 1 to values list and call checkQueryCondition
						values[index] = intToString(arg1Num);
						checkQueryCondition(childIndex+1, values, result, check);
					} else {
						// Brute force method
						vector<int> arg1List;
						arg1Type = table.getType(arg1Value);
						if (arg1Type=="prog_line" || arg1Type=="stmt") {
							// retrieve all statements 
							for (int i=0; i<PKB::getStatTableSize(); i++) {
								arg1List.push_back(i+1);
							}
						} else if (arg1Type=="assign") {
							arg1List = PKB::getStmtIndex("assignment");
						} else if (arg1Type=="while") {
							arg1List = PKB::getStmtIndex("while:stmtList");
							
						}
						// start checking with all values in arg1List
						for (size_t i=0; i<arg1List.size(); i++) {
							// save value of arg1 to vector "values"
							values[index] = intToString(arg1List[i]);
							// recursively call this method to continue checking arg2
							checkSuchThatCondition(suchThatNode, values, result, check, childIndex);
							/* REMARK
							 * Recursion here is not necessary, however. We can also check arg2Num 
							 * by calling PKB.getFollowingStmt(arg1Num). But I want to set this as an example
							 * of how to deal with "brute force" in harder cases: Follows*, Parent*, Modifies and Uses.
							 * Those relationship will need recursive to solve.
							 */
						}
					}
				}
			}
		}	
}

void QueryEvaluator::handleFollowsSRelationship (TNode relationNode, TNode suchThatNode, vector<string> values, vector<string>& result, bool check, int childIndex) {
	TNode arg1Node = relationNode.getChildAtIndex(0);
		string arg1Type = arg1Node.getType();
		string arg1Value = arg1Node.getValue();
		TNode arg2Node = relationNode.getChildAtIndex(1);
		string arg2Type = arg2Node.getType();
		string arg2Value = arg2Node.getValue();
		int arg1Num; int arg2Num;

		// there are following cases:

		// IF ARGUMENT 1 OF RELATIONSHIP FOLLOWS IS A NUMBER, eg Follows(1, 2) or Follows (1, s)
		if (arg1Type=="number") {
			arg1Num = atoi(arg1Value.c_str());
			// IF ARGUMENT 2 IS A NUMBER
			if (arg2Type=="number") {
				arg2Num = atoi(arg2Value.c_str());
				if (!PKB::isFollowsStar(arg1Num, arg2Num)) {
					check = false;
					// RETURN TO THE PREVIOUS METHOD TO UPDATE THAT THIS VALUE LIST DOES NOT SATISFY THE CONDITIONS
					checkQueryCondition(childIndex+1, values, result, check);
				} 
				// RETURN TO THE PREVIOUS METHOD TO CONTINUE WITH NEXT CONDITION (by adding the increment)
				checkQueryCondition(childIndex+1, values, result, check);
			}

			// IF ARGUMENT 2 IS A SYMBOL
			if (arg2Type=="symbol") {
				
				// get values of this symbol from vector "values"
				int index2 = table.getIndex(arg2Value);
				// IF WE ALREADY STORE A VALUE OF ARGUMENT 2 
				// WHEN PROCESSING A PREVIOUS CONDITION
				if (values[index2]!="-1") {
					arg2Num = atoi(values[index2].c_str());
					if (!PKB::isFollowsStar(arg1Num, arg2Num)) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					} 
					checkQueryCondition(childIndex+1, values, result, check);
				}
				// IF NO VALUE OF ARGUMENT 2 WAS STORED
				else {
					vector<int> arg2List = PKB::getFollowingStarStmt(arg1Num);
					if (arg2List.size()==0 || arg2List[0]==-1) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}
					// update values
					for (size_t i=0; i< arg2List.size(); i++) {
						if (isDeclaredType(intToString(arg2List[i]), arg2Value, arg2Type)) {
							values[index2] = intToString(arg2List[i]);
							checkQueryCondition(childIndex+1, values, result, check);
						}
					}					
				}
			}
		}
		// IF ARGUMENT 1 IS A SYMBOL, eg Follows*(s, 12)
		else if (arg1Type=="symbol"){
			// get values of this symbol from vector "values"
			int index = table.getIndex(arg1Value);
			// IF THERE WAS STORED VALUE OF ARGUMENT 1
			if (values[index]!="-1") {
			arg1Num = atoi(values[index].c_str());

				// IF ARGUMENT 2 IS A NUMBER 
				if (arg2Type=="number") {
					arg2Num = atoi(arg2Value.c_str());
					if (!PKB::isFollowsStar(arg1Num, arg2Num)) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
					}
					checkQueryCondition(childIndex+1, values, result, check);
				} 
				// IF ARGUMENT 2 IS A SYMBOL
				else {
					int index2 = table.getIndex(arg2Value);
					// if arg2 has value stored
					if (values[index2]!="-1") {
						arg2Num = atoi(values[index2].c_str());
						if (!PKB::isFollowsStar(arg1Num, arg2Num)) {
							check = false;
							checkQueryCondition(childIndex+1, values, result, check);
						}
						checkQueryCondition(childIndex+1, values, result, check);
					}
					// if arg2 has no value yet
					else {
						vector<int> arg2List = PKB::getFollowingStarStmt(arg1Num);
						if (arg2List.size()==0 || arg2List[0]==-1) {
							check = false;
							checkQueryCondition(childIndex+1, values, result, check);
							return;
						}
						for (size_t i=0; i<arg2List.size(); i++) {
							if (isDeclaredType(intToString(arg2List[i]), arg2Value, arg2Type)) {
								values[index2] = intToString(arg2List[i]);
								checkQueryCondition(childIndex+1, values, result, check);
							}
						}			
					}
				}
			} 
			// IF THERE IS NO VALUE STORED FOR ARGUMENT 1
			else {
				// IF ARGUMENT 2 IS A NUMBER
				if (arg2Type=="number") {
					arg2Num = atoi(arg2Value.c_str());
					vector<int> arg1List = PKB::getFollowedStarStmt(arg2Num);
					if (arg1List.size()==0 || arg1List[0] ==-1) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}
					// save value of argument 1 to values list and call checkQueryCondition
					for (size_t i=0; i<arg1List.size(); i++) {		
						if (isDeclaredType(intToString(arg1List[i]), arg1Value, arg1Type)) {
							values[index] = intToString(arg1List[i]);
							checkQueryCondition(childIndex+1, values, result, check);
						}
					}
				} else {
					int index2 = table.getIndex(arg2Value);
					// IF THERE IS VALUE STORED FOR ARGUMENT 2
					if (values[index2]!="-1") {
						arg2Num = atoi(values[index2].c_str());
						vector<int> arg1List = PKB::getFollowedStarStmt(arg2Num);
						if (arg1List.size()==0 || arg1List[0] ==-1) {
							check = false;
							checkQueryCondition(childIndex+1, values, result, check);
							return;
						}
						// save value of argument 1 to values list and call checkQueryCondition
						for (size_t i=0; i<arg1List.size(); i++) {
							if (isDeclaredType(intToString(arg1List[i]), arg1Value, arg1Type)) {
								values[index] = intToString(arg1List[i]);
								checkQueryCondition(childIndex+1, values, result, check);
							}
						}
					} else {
						// Brute force method
						vector<int> arg1List;
						arg1Type = table.getType(arg1Value);
						if (arg1Type=="prog_line" || arg1Type=="stmt") {
							// retrieve all statements 
							for (int i=0; i<PKB::getStatTableSize(); i++) {
								arg1List.push_back(i+1);
							}
						} else if (arg1Type=="assign") {
							arg1List = PKB::getStmtIndex("assignment");
						} else if (arg1Type=="while") {
							arg1List = PKB::getStmtIndex("while:stmtList");
							
						}
						// start checking with all values in arg1List
						for (size_t i=0; i<arg1List.size(); i++) {
							// save value of arg1 to vector "values"
							values[index] = intToString(arg1List[i]);
							// recursively call this method to continue checking arg2
							checkSuchThatCondition(suchThatNode, values, result, check, childIndex);
							/* REMARK
							 * Recursion here is not necessary, however. We can also check arg2Num 
							 * by calling PKB.getFollowingStmt(arg1Num). But I want to set this as an example
							 * of how to deal with "brute force" in harder cases: Follows*, Parent*, Modifies and Uses.
							 * Those relationship will need recursive to solve.
							 */
						}
					}
				}
			}
		}	
}

void QueryEvaluator::handleParentRelationship (TNode relationNode, TNode suchThatNode, vector<string> values, vector<string>& result, bool check, int childIndex) {
	TNode arg1Node = relationNode.getChildAtIndex(0);
	string arg1Type = arg1Node.getType();
	string arg1Value = arg1Node.getValue();
	TNode arg2Node = relationNode.getChildAtIndex(1);
	string arg2Type = arg2Node.getType();
	string arg2Value = arg2Node.getValue();
	int arg1Num; int arg2Num;

	// IF ARGUMENT 1 OF RELATIONSHIP PARENT IS A NUMBER, eg Follows(1, 2) or Follows (1, s)
	if (arg1Type=="number") {
		arg1Num = atoi(arg1Value.c_str());
		// IF ARGUMENT 2 IS A NUMBER
		if (arg2Type=="number") {
			arg2Num = atoi(arg2Value.c_str());
			if (!PKB::isParent(arg1Num, arg2Num)) {
				check = false;
				// RETURN TO THE PREVIOUS METHOD TO UPDATE THAT THIS VALUE LIST DOES NOT SATISFY THE CONDITIONS
				checkQueryCondition(childIndex+1, values, result, check);
			} 
			// RETURN TO THE PREVIOUS METHOD TO CONTINUE WITH NEXT CONDITION (by adding the increment)
			checkQueryCondition(childIndex+1, values, result, check);
		}

		// IF ARGUMENT 2 IS A SYMBOL
		if (arg2Type=="symbol") {
			// get values of this symbol from vector "values"
			int index = table.getIndex(arg2Value);
			// IF WE ALREADY STORE A VALUE OF ARGUMENT 2 
			// WHEN PROCESSING A PREVIOUS CONDITION
			if (values[index]!="-1") {
				arg2Num = atoi(values[index].c_str());
				if (!PKB::isParent(arg1Num, arg2Num)) {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
					return;
				} 
				checkQueryCondition(childIndex+1, values, result, check);
			}
			// IF NO VALUE OF ARGUMENT 2 WAS STORED
			else {
				// How to pass infor to value as a list of int

				vector<int> arg2List = PKB::getChildStmt(arg1Num);
				if (arg2List.size()==0 || arg2List[0] == -1) {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
					return;
				}
				// update values
				for (size_t i=0; i<arg2List.size(); i++) {
					if (isDeclaredType(intToString(arg2List[i]), arg2Value, arg2Type)) {
						values[index] = intToString(arg2List[i]);
						checkQueryCondition(childIndex+1, values, result, check);	
					}
				}
			}
		}
	}
	// IF ARGUMENT 1 IS A SYMBOL, eg Follows(s, 12)
	else if (arg1Type=="symbol"){
		// get values of this symbol from vector "values"
		int index = table.getIndex(arg1Value);
		// IF THERE WAS STORED VALUE OF ARGUMENT 1
		if (values[index]!="-1") {
			arg1Num = atoi(values[index].c_str());

			// IF ARGUMENT 2 IS A NUMBER 
			if (arg2Type=="number") {
				arg2Num = atoi(arg2Value.c_str());
				if (!PKB::isParent(arg1Num, arg2Num)) {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
				}
				checkQueryCondition(childIndex+1, values, result, check);
			} 
			// IF ARGUMENT 2 IS A SYMBOL
			else {
				int index2 = table.getIndex(arg2Value);
				// if arg2 has value stored
				if (values[index2]!="-1") {
					arg2Num = atoi(values[index2].c_str());
					if (!PKB::isParent(arg1Num, arg2Num)) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
					}
					checkQueryCondition(childIndex+1, values, result, check);
				} else { // if arg2 has no value yet
					/* REFER TO PREVIOUS CASE: arg1 is number and arg2 has no value */
					vector<int> arg2List = PKB::getChildStmt(arg1Num);
					if (arg2List.size()==0 || arg2List[0] == -1) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}
					// update values
					for (size_t i=0; i<arg2List.size(); i++) {
						if (isDeclaredType(intToString(arg2List[i]), arg2Value, arg2Type)) {
							values[index2] = intToString(arg2List[i]);
							checkQueryCondition(childIndex+1, values, result, check);	
						}
					}
				}
			}
		} 
		// IF THERE IS NO VALUE STORED FOR ARGUMENT 1
		else {
			// IF ARGUMENT 2 IS A NUMBER
			if (arg2Type=="number") {
				arg2Num = atoi(arg2Value.c_str());
				arg1Num = PKB::getParentStmt(arg2Num);
				if (arg1Num==-1) {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
					return;
				}
				
				if (!isDeclaredType(intToString(arg1Num), arg1Value, arg1Type)) {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
					return;
				}
				// save value of argument 1 to values list and call checkQueryCondition
				values[index] = intToString(arg1Num);
				checkQueryCondition(childIndex+1, values, result, check);
			} else {
				int index2 = table.getIndex(arg2Value);
				// IF THERE IS VALUE STORED FOR ARGUMENT 2
				if (values[index2]!="-1") {
					arg2Num = atoi(values[index2].c_str());
					arg1Num = PKB::getParentStmt(arg2Num);
					if (arg1Num==-1) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}

					if (!isDeclaredType(intToString(arg1Num), arg1Value, arg1Type)) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}

					// save value of argument 1 to values list and call checkQueryCondition
					values[index] = intToString(arg1Num);
					checkQueryCondition(childIndex+1, values, result, check);
				} else {

					// Brute force method
					vector<int> arg1List;
					arg1Type = table.getType(arg1Value);
					if (arg1Type=="prog_line" || arg1Type=="stmt") {
						// retrieve all statements 
						for (int i=0; i<PKB::getStatTableSize(); i++) {
							arg1List.push_back(i+1);
						}
					} else if (arg1Type=="assign") {
						arg1List = PKB::getStmtIndex("assignment");
					} else if (arg1Type=="while") {
						arg1List = PKB::getStmtIndex("while:stmtList");
					}

					// start checking with all values in arg1List
					for (size_t i=0; i<arg1List.size(); i++) {
						// save value of arg1 to vector "values"
						values[index] = intToString(arg1List[i]);
						// recursively call this method to continue checking arg2
						checkSuchThatCondition(suchThatNode, values, result, check, childIndex);
						/* REMARK
						* Recursion here is not necessary, however. We can also check arg2Num 
						* by calling PKB.getFollowingStmt(arg1Num). But I want to set this as an example
						* of how to deal with "brute force" in harder cases: Follows*, Parent*, Modifies and Uses.
						* Those relationship will need recursive to solve.
						*/
					}
				}
			}
		}
	}
}

void QueryEvaluator::handleParentSRelationship (TNode relationNode, TNode suchThatNode, vector<string> values, vector<string>& result, bool check, int childIndex) {
	TNode arg1Node = relationNode.getChildAtIndex(0);
	string arg1Type = arg1Node.getType();
	string arg1Value = arg1Node.getValue();
	TNode arg2Node = relationNode.getChildAtIndex(1);
	string arg2Type = arg2Node.getType();
	string arg2Value = arg2Node.getValue();
	int arg1Num; int arg2Num;

	// IF ARGUMENT 1 OF RELATIONSHIP PARENT IS A NUMBER, eg Follows(1, 2) or Follows (1, s)
	if (arg1Type=="number") {
		arg1Num = atoi(arg1Value.c_str());
		// IF ARGUMENT 2 IS A NUMBER
		if (arg2Type=="number") {
			arg2Num = atoi(arg2Value.c_str());
			if (!PKB::isParentStar(arg1Num, arg2Num)) {
				check = false;
				// RETURN TO THE PREVIOUS METHOD TO UPDATE THAT THIS VALUE LIST DOES NOT SATISFY THE CONDITIONS
				checkQueryCondition(childIndex+1, values, result, check);
			} 
			// RETURN TO THE PREVIOUS METHOD TO CONTINUE WITH NEXT CONDITION (by adding the increment)
			checkQueryCondition(childIndex+1, values, result, check);
		}

		// IF ARGUMENT 2 IS A SYMBOL
		if (arg2Type=="symbol") {
			// get values of this symbol from vector "values"
			int index2 = table.getIndex(arg2Value);
			// IF WE ALREADY STORE A VALUE OF ARGUMENT 2 
			// WHEN PROCESSING A PREVIOUS CONDITION
			if (values[index2]!="-1") {
				arg2Num = atoi(values[index2].c_str());
				if (!PKB::isParentStar(arg1Num, arg2Num)) {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
					return;
				} 
				checkQueryCondition(childIndex+1, values, result, check);
			}
			// IF NO VALUE OF ARGUMENT 2 WAS STORED
			else {
				// How to pass infor to value as a list of int
				vector<int> arg2List = PKB::getChildStarStmt(arg1Num);
				if (arg2List.size()==0 || arg2List[0]==-1) {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
					return;
				}
				// update values
				for (size_t i=0; i<arg2List.size(); i++) {
					if (isDeclaredType(intToString(arg2List[i]), arg2Value, arg2Type)) {
						values[index2] = intToString(arg2List[i]);
						checkQueryCondition(childIndex+1, values, result, check);	
					}
				}
			}
		}
	}
	// IF ARGUMENT 1 IS A SYMBOL, eg Follows(s, 12)
	else if (arg1Type=="symbol"){
		// get values of this symbol from vector "values"
		int index = table.getIndex(arg1Value);
		// IF THERE WAS STORED VALUE OF ARGUMENT 1
		if (values[index]!="-1") {
			arg1Num = atoi(values[index].c_str());

			// IF ARGUMENT 2 IS A NUMBER 
			if (arg2Type=="number") {
				arg2Num = atoi(arg2Value.c_str());
				if (!PKB::isParentStar(arg1Num, arg2Num)) {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
				}
				checkQueryCondition(childIndex+1, values, result, check);
			} 
			// IF ARGUMENT 2 IS A SYMBOL
			else {
				int index2 = table.getIndex(arg2Value);
				// if arg2 has value stored
				if (values[index2]!="-1") {
					arg2Num = atoi(values[index2].c_str());
					if (!PKB::isParentStar(arg1Num, arg2Num)) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
					}
					checkQueryCondition(childIndex+1, values, result, check);
				}
				// if arg2 has no value yet
				else {
					//how to pass info to value as a list
					vector<int> arg2List = PKB::getChildStarStmt(arg1Num);
					if (arg2List.size()==0 || arg2List[0]==-1) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}
					// update values
					for (size_t i=0; i<arg2List.size(); i++) {
						if (isDeclaredType(intToString(arg2List[i]), arg2Value, arg2Type)) {
							values[index] = intToString(arg2List[i]);
							checkQueryCondition(childIndex+1, values, result, check);	
						}
					}
				}
			}
		} 
		// IF THERE IS NO VALUE STORED FOR ARGUMENT 1
		else {
			// IF ARGUMENT 2 IS A NUMBER
			if (arg2Type=="number") {
				arg2Num = atoi(arg2Value.c_str());
				vector<int> arg1List = PKB::getParentStarStmt(arg2Num);
				if (arg1List.size()==0 || arg1List[0]==-1) {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
					return;
				}
				// update values
				for (size_t i=0; i<arg1List.size(); i++) {
					values[index] = intToString(arg1List[i]);
					checkQueryCondition(childIndex+1, values, result, check);	
				}
			} else {
				int index2 = table.getIndex(arg2Value);
				// IF THERE IS VALUE STORED FOR ARGUMENT 2
				if (values[index2]!="-1") {
					arg2Num = atoi(values[index2].c_str());
					vector<int> arg1List = PKB::getParentStarStmt(arg2Num);
					if (arg1List.size()==0 || arg1List[0]==-1) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}

					if (!isDeclaredType(intToString(arg1Num), arg1Value, arg1Type)) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
						return;
					}

					for (size_t i=0; i<arg1List.size(); i++) {
						if (!isDeclaredType(intToString(arg1List[i]), arg1Value, arg1Type)) {
							// save value of argument 1 to values list and call checkQueryCondition
							values[index] = intToString(arg1List[i]);
							checkQueryCondition(childIndex+1, values, result, check);
						}
					}
					
				} else {
					// Brute force method
					vector<int> arg1List;
					arg1Type = table.getType(arg1Value);
					if (arg1Type=="prog_line" || arg1Type=="stmt") {
						// retrieve all statements 
						for (int i=0; i<PKB::getStatTableSize(); i++) {
							arg1List.push_back(i+1);
						}
					} else if (arg1Type=="assign") {
						arg1List = PKB::getStmtIndex("assignment");
					} else if (arg1Type=="while") {
						arg1List = PKB::getStmtIndex("while:stmtList");

					}
					// start checking with all values in arg1List
					for (size_t i=0; i<arg1List.size(); i++) {
						// save value of arg1 to vector "values"
						values[index] = intToString(arg1List[i]);
						// recursively call this method to continue checking arg2
						checkSuchThatCondition(suchThatNode, values, result, check, childIndex);
						/* REMARK
						* Recursion here is not necessary, however. We can also check arg2Num 
						* by calling PKB.getFollowingStmt(arg1Num). But I want to set this as an example
						* of how to deal with "brute force" in harder cases: Follows*, Parent*, Modifies and Uses.
						* Those relationship will need recursive to solve.
						*/
					}
				}
			}
		}
	}
}

void QueryEvaluator::handleModifiesRelationship (TNode relationNode, TNode suchThatNode, vector<string> values, vector<string>& result, bool check, int childIndex) {
	TNode arg1Node = relationNode.getChildAtIndex(0);
		string arg1Type = arg1Node.getType();
		string arg1Value = arg1Node.getValue();
		TNode arg2Node = relationNode.getChildAtIndex(1);
		string arg2Type = arg2Node.getType();
		string arg2Value = arg2Node.getValue();
		int arg1Num;

		if (arg1Type=="number") {
			arg1Num = atoi(arg1Value.c_str());
			if (arg2Type=="variable") {
				int arg2Index = PKB::getVarIndex(arg2Value);
				if (PKB::isModifies(arg1Num, arg2Index)) {
					checkQueryCondition(childIndex+1, values, result, check);
				} else {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
				}
			} else {
				int index2 = table.getIndex(arg2Value);
				if (values[index2]!="-1") {
					string arg2Name = values[index2];
					int arg2Index = PKB::getVarIndex(arg2Name);
					if (PKB::isModifies(arg1Num, arg2Index)) {
						checkQueryCondition(childIndex+1, values, result, check);
					} else {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
					}
				} else {
					vector<int> arg2Indexes = PKB::getModifiedVarAtStmt(arg1Num);
					if (arg2Indexes.size()==0 || arg2Indexes[0]==-1) {
						check = false;
						checkQueryCondition(childIndex+1, values, result, check);
					} else {
						for (size_t i=0; i< arg2Indexes.size(); i++) {
							if (isDeclaredType(PKB::getVarName(arg2Indexes[i]), arg2Value, table.getType(arg2Value))) {
								values[index2] = PKB::getVarName(arg2Indexes[i]);
								checkQueryCondition(childIndex+1, values, result, check);
							}
						}
					}
				}
			}
		} else {
			int index = table.getIndex(arg1Value);
			if (values[index]!="-1") {
				arg1Num = atoi(values[index].c_str());
				if (arg2Type=="variable") {
					int arg2Index = PKB::getVarIndex(arg2Value);
					if (PKB::isModifies(arg1Num, arg2Index)) {
						checkQueryCondition(childIndex+1, values, result, check);
					} else {
						check =false;
						checkQueryCondition(childIndex+1, values, result, check);
					}
				} else {
					int index2 = table.getIndex(arg2Value);
					if (values[index2]!="-1") {
						string arg2Name = values[index2];
						int arg2Index = PKB::getVarIndex(arg2Name);
						if (PKB::isModifies(arg1Num, arg2Index)) {
							checkQueryCondition(childIndex+1, values, result, check);
						} else {
							check =false;
							checkQueryCondition(childIndex+1, values, result, check);
						}
					} else {
						vector<int> arg2Indexes = PKB::getModifiedVarAtStmt(arg1Num);
						if (arg2Indexes.size()==0 || arg2Indexes[0] == -1) {
							check =false;
							checkQueryCondition(childIndex+1, values, result, check);
						} else {
							for (size_t i=0; i<arg2Indexes.size(); i++) {
								if (isDeclaredType(PKB::getVarName(arg2Indexes[i]), arg2Value, arg2Type)) {
									values[index2] = PKB::getVarName(arg2Indexes[i]);
									checkQueryCondition(childIndex+1, values, result, check);
								}
							}
						}
					}
				} 
			} else {
				if (arg2Type=="variable") {
					int arg2Index = PKB::getVarIndex(arg2Value);
					vector<int> arg1Values = PKB::getStmtModifyingVar(arg2Index);
					if (arg1Values.size()==0 || arg1Values[0]==-1) {
						check =false;
						checkQueryCondition(childIndex+1, values, result, check);
					} else {
						for (size_t i=0; i<arg1Values.size(); i++) {
							values[index] = intToString(arg1Values[i]);
							checkQueryCondition(childIndex+1, values, result, check);
						}
					}
				} else {
					int index2 = table.getIndex(arg2Value);
					if (values[index2]!="-1") {
						string arg2Name = values[index2];
						int arg2Index = PKB::getVarIndex(arg2Name);
						vector<int> arg1Values = PKB::getStmtModifyingVar(arg2Index);
						if (arg1Values.size()==0 || arg1Values[0]==-1) {
							check =false;
							checkQueryCondition(childIndex+1, values, result, check);
						} else {
							for (size_t i=0; i<arg1Values.size(); i++) {
								if (isDeclaredType(intToString(arg1Values[i]), arg1Value, arg1Type)) {
									values[index] = intToString(arg1Values[i]);
									checkQueryCondition(childIndex+1, values, result, check);
								}
							}
						}
					} else {
						// brute force
						vector<int> arg1List;
						arg1Type = table.getType(arg1Value);
						if (arg1Type=="prog_line" || arg1Type=="stmt") {
							// retrieve all statements 
							for (int i=0; i<PKB::getStatTableSize(); i++) {
								arg1List.push_back(i+1);
							}
						} else if (arg1Type=="assign") {
							arg1List = PKB::getStmtIndex("assignment");
						} else if (arg1Type=="while") {
							arg1List = PKB::getStmtIndex("while:stmtList");
							
						}
						// start checking with all values in arg1List
						for (size_t i=0; i<arg1List.size(); i++) {
							values[index] = intToString(arg1List[i]);
							checkQueryCondition(childIndex+1, values, result, check);
						}
					}
				}
			}
		}
}

void QueryEvaluator::handleUsesRelationship (TNode relationNode, TNode suchThatNode, vector<string> values, vector<string>& result, bool check, int childIndex) {
	TNode arg1Node = relationNode.getChildAtIndex(0);
	string arg1Type = arg1Node.getType();
	string arg1Value = arg1Node.getValue();
	TNode arg2Node = relationNode.getChildAtIndex(1);
	string arg2Type = arg2Node.getType();
	string arg2Value = arg2Node.getValue();
	int arg1Num;

	if (arg1Type=="number") {
		arg1Num = atoi(arg1Value.c_str());
		if (arg2Type=="variable") {
			int arg2Index = PKB::getVarIndex(arg2Value);
			if (PKB::isUses(arg1Num, arg2Index)) {
				checkQueryCondition(childIndex+1, values, result, check);
			} else {
				check = false;
				checkQueryCondition(childIndex+1, values, result, check);
			}
		} else {
			int index2 = table.getIndex(arg2Value);
			if (values[index2]!="-1") {
				string arg2Name = values[index2];
				int arg2Index = PKB::getVarIndex(arg2Name);
				if (PKB::isUses(arg1Num, arg2Index)) {
					checkQueryCondition(childIndex+1, values, result, check);
				} else {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
				}
			} else {
				vector<int> arg2Indexes = PKB::getUsedVarAtStmt(arg1Num);
				if (arg2Indexes.size()==0 || arg2Indexes[0]==-1) {
					check = false;
					checkQueryCondition(childIndex+1, values, result, check);
				} else {
					for (size_t i=0; i< arg2Indexes.size(); i++) {
						if (isDeclaredType(PKB::getVarName(arg2Indexes[i]), arg2Value, table.getType(arg2Value))) {
							values[index2] = PKB::getVarName(arg2Indexes[i]);
							checkQueryCondition(childIndex+1, values, result, check);
						}
					}
				}
			}
		}
	} else {
		int index = table.getIndex(arg1Value);
		if (values[index]!="-1") {
			arg1Num = atoi(values[index].c_str());
			if (arg2Type=="variable") {
				int arg2Index = PKB::getVarIndex(arg2Value);
				if (PKB::isUses(arg1Num, arg2Index)) {
					checkQueryCondition(childIndex+1, values, result, check);
				} else {
					check =false;
					checkQueryCondition(childIndex+1, values, result, check);
				}
			} else {
				int index2 = table.getIndex(arg2Value);
				if (values[index2]!="-1") {
					string arg2Name = values[index2];
					int arg2Index = PKB::getVarIndex(arg2Name);
					if (PKB::isUses(arg1Num, arg2Index)) {
						checkQueryCondition(childIndex+1, values, result, check);
					} else {
						check =false;
						checkQueryCondition(childIndex+1, values, result, check);
					}
				} else {
					vector<int> arg2Indexes = PKB::getUsedVarAtStmt(arg1Num);
					if (arg2Indexes.size()==0 || arg2Indexes[0] == -1) {
						check =false;
						checkQueryCondition(childIndex+1, values, result, check);
					} else {
						for (size_t i=0; i<arg2Indexes.size(); i++) {
							if (isDeclaredType(PKB::getVarName(arg2Indexes[i]), arg2Value, table.getType(arg2Value))) {
								values[index2] = PKB::getVarName(arg2Indexes[i]);
								checkQueryCondition(childIndex+1, values, result, check);
							}
						}
					}
				}
			} 
		} else {
			if (arg2Type=="variable") {
				int arg2Index = PKB::getVarIndex(arg2Value);
				vector<int> arg1Values = PKB::getStmtUsingVar(arg2Index);
				if (arg1Values.size()==0 || arg1Values[0]==-1) {
					check =false;
					checkQueryCondition(childIndex+1, values, result, check);
				} else {
					for (size_t i=0; i<arg1Values.size(); i++) {
						if (isDeclaredType(intToString(arg1Values[i]), arg1Value, arg1Type)) {
							values[index] = intToString(arg1Values[i]);
							checkQueryCondition(childIndex+1, values, result, check);
						}
					}
				}
			} else {
				int index2 = table.getIndex(arg2Value);
				if (values[index2]!="-1") {
					string arg2Name = values[index2];
					int arg2Index = PKB::getVarIndex(arg2Name);
					vector<int> arg1Values = PKB::getStmtUsingVar(arg2Index);
					if (arg1Values.size()==0 || arg1Values[0]==-1) {
						check =false;
						checkQueryCondition(childIndex+1, values, result, check);
					} else {
						for (size_t i=0; i<arg1Values.size(); i++) {
							if (isDeclaredType(intToString(arg1Values[i]), arg1Value, arg1Type)) {
								values[index] = intToString(arg1Values[i]);
								checkQueryCondition(childIndex+1, values, result, check);
							}
						}
					}
				} else {
					// brute force
					vector<int> arg1List;
						arg1Type = table.getType(arg1Value);
						if (arg1Type=="prog_line" || arg1Type=="stmt") {
							// retrieve all statements 
							for (int i=0; i<PKB::getStatTableSize(); i++) {
								arg1List.push_back(i+1);
							}
						} else if (arg1Type=="assign") {
							arg1List = PKB::getStmtIndex("assignment");
						} else if (arg1Type=="while") {
							arg1List = PKB::getStmtIndex("while:stmtList");
							
						}
						// start checking with all values in arg1List
						for (size_t i=0; i<arg1List.size(); i++) {
							values[index] = intToString(arg1List[i]);
							checkQueryCondition(childIndex+1, values, result, check);
						}
					}
				}
			}
		}
}

void QueryEvaluator::checkPatternCondition(TNode patternNode,vector<string> values,vector<string>& result,bool check,int childIndex) {
	// get first child of patternNode
	TNode child1 = patternNode.getChildAtIndex(0);
	string child1Name = child1.getValue();
	int child1Index = table.getIndex(child1Name);

	// check if child1 has value stored in "values" list
	if (values[child1Index]=="-1")	{ // no value stored yet
		// since this node store an assignment-symbol parameter,
		// we only need to get all assignments in PKB
		vector<int> child1List = PKB::getStmtIndex("assignment");

		if (child1List.size()==0 || child1List[0]==-1) {
			check = false;
			checkQueryCondition(childIndex+1, values, result, check);
			return;
		}

		// recursive call 
		for (size_t i=0; i<child1List.size(); i++) {
			if (isDeclaredType(intToString(child1List[i]), child1Name, table.getType(child1Name))) {
				values[child1Index] = intToString(child1List[i]);
				checkPatternCondition(patternNode, values, result, check, childIndex);
			}
		}
	} else {
		// get value of child1
		int child1Val = atoi(values[child1Index].c_str());

		// set up 2 boolean values to check correctness of
		// expressions in left hand and right hand sides
		bool leftHandSide = false; 
		bool rightHandSide = false;


		// get second child and check it value
		TNode child2 = patternNode.getChildAtIndex(1);
		string child2Type = child2.getType();
		string child2Val = child2.getValue();
		if (child2Type=="underline") {
			leftHandSide = true;
		} else if (child2Type=="variable"){
			// check if child2Val is a variable name or not
			int child2Index = PKB::getVarIndex(child2Val);
			if (child2Index==-1) {
				leftHandSide = false;
			} else {
				// check if assignment child1Val modifies variable in child2
				if (!PKB::isModifies(child1Val, child2Index)) {
					leftHandSide = false;
				} else leftHandSide = true;
			}
		} else if (child2Type=="symbol") {
			// check if child2 has value stored in "values" list
			int child2Index = table.getIndex(child2Val);
			if (values[child2Index]!="-1") {
				// if yes, do the same as case child2Type == variable
				child2Index = PKB::getVarIndex(values[child2Index]);
				if (child2Index==-1) {
					leftHandSide = false;
				} else {
					// check if assignment child1Val modifies variable in child2
					if (!PKB::isModifies(child1Val, child2Index)) {
						leftHandSide = false;
					} else leftHandSide = true;
				}
			} else {
				// if no, get variable modified by assignment in child1 
				vector<int> child2List = PKB::getModifiedVarAtStmt(child1Val);
				// unimportant, but to be careful if while stmt are mixed in child1Val
				if (child2List.size()!=1) {
					leftHandSide = false;			
				} else {
					// update child2 to values list
					values[child2Index] = PKB::getVarName(child2List[0]);

					child2Index = child2List[0];
					if (child2Index==-1) {
						leftHandSide = false;
					} else {
						// check if assignment child1Val modifies variable in child2
						if (!PKB::isModifies(child1Val, child2Index)) {
							leftHandSide = false;
						} else leftHandSide = true;
					}
				}
			}
		}
		
		// get third child, which is the right hand side
		TNode child3 = patternNode.getChildAtIndex(2);

		if (child3.getType()=="underline") {
			rightHandSide=true;
		} else {
			TNode node = PKB::getNodeOfStmt(child1Val);
			AST subAST; subAST.setRoot(node.getChildAtIndex(1));
			Tree tree; tree.setRoot(child3);
			rightHandSide = subAST.hasSubTree(tree);
		}

		// update boolean value "check"
		check = leftHandSide && rightHandSide;
		checkQueryCondition(childIndex+1, values, result, check);
	}
}
	

void QueryEvaluator::updateResultList(vector<string> values, vector<string>& result) {
	TNode root = tree.getRoot();
	// get first child
	TNode child = root.getChildAtIndex(0);

	child = child.getChildAtIndex(0);
	string paramType = child.getType();
	string paramName = child.getValue();
	// get index of the parameter
	int paramIndex = table.getIndex(paramName);
	string paramVal = values[paramIndex];
	// check if paramVal is null value or not
	if (paramVal!="-1") {
		// check if paramVal has same type as in paramType
		if (!isDeclaredType(paramVal, paramName, paramType)) {
			return;
		}

		// for debugging

		// check if result list has this paramVal
		if (!isResult(paramVal, result)) {
			// add new result to list
			result.push_back(paramVal);
		}
	} else {
		// all values possible of param are result
		string paramType = table.getType(paramName);
		if (paramType=="prog_line" || paramType=="stmt") {
			// retrieve all statements 
			for (int i=0; i<PKB::getStatTableSize(); i++) {
				paramVal = intToString(i+1);
				if (!isResult(paramVal, result)) {
					// add new result to list
					result.push_back(paramVal);
				}
			}
		} else if (paramType=="assign") {
			vector<int> paramList = PKB::getStmtIndex("assignment");
			for (size_t i=0; i<paramList.size(); i++) {
				paramVal = intToString(paramList[i]);
				if (!isResult(paramVal, result)) {
					// add new result to list
					result.push_back(paramVal);
				}
			}
		} else if (paramType=="while") {
			vector<int> paramList = PKB::getStmtIndex("while:stmtList");
			for (size_t i=0; i<paramList.size(); i++) {
				paramVal = intToString(paramList[i]);
				if (!isResult(paramVal, result)) {
					// add new result to list
					result.push_back(paramVal);
				}
			}
		} else if (paramType=="variable") {
			for (int i=0; i<PKB::getVarTableSize(); i++) {
				result.push_back(PKB::getVarName(i));
			}
		} else if (paramType=="constant") {
			for (int i=0; i<PKB::getConstTableSize(); i++) {
				result.push_back(PKB::getConstName(i));
			}
		}
		else return;
	}	
}

bool QueryEvaluator::isResult(string val, vector<string> result) {
	for (size_t i=0; i<result.size(); i++) {
		if (result[i]==val) return true;
	}
	return false;
}


bool QueryEvaluator::isDeclaredType(string val, string name, string type) {
	if (type=="constant") {
		if (PKB::getConstIndex(val)==-1) return false; 
	} else if (type=="variable") {
		if (PKB::getVarIndex(val)==-1) return false;
	} else if (type=="procedure") {
		// implement here
	} else {
		// search in StmtTable for this case
		if (table.getType(name)!= "prog_line" && table.getType(name)!= "stmt") {
			string stmtType = PKB::getStmtName(atoi(val.c_str()));
			if (stmtType=="assignment" && table.getType(name)!="assign") return false; 
			if (stmtType=="while:stmtList" && table.getType(name)!="while") return false;
			// implement further for call, etc.
		} else return true;
	}

	return true;
}

/*
void QueryEvaluator::findResult(int index, vector<string> values, vector<string>& result) {
	int size = table.getSize();
	// base case
	if (index==size) { // no more symbol to retrieve
		// printSymbolValues(values);
		if (isQueryConditionsSatisfied(values)) {

		// update result and return
		string value = getResultAfterEvaluation(values);
		addNewResult(result, value);
		}
		return;
	} else {
		// retrieve list of values for next symbol in SymbolTable
		string type = table.getType(index);
		vector<string> symbolValues;

		if (type=="prog_line" || type=="stmt") {
			// retrieve all stmt numbers from stmtTable
			// and change them to string type
			for (int i=0; i<PKB::getStatTableSize(); i++) {
				string stmtNum = intToString(i+1);
				symbolValues.push_back(stmtNum);
			}
		} else if (type=="assign") {
			vector<int> assignList = PKB::getStmtIndex("assignment");
			for (size_t i=0; i<assignList.size(); i++) {
				string assignNum = intToString(assignList[i]);
				symbolValues.push_back(assignNum);
			}
		} else if (type=="while") {
			vector<int> whileList = PKB::getStmtIndex("while:stmtList");
			for (size_t i=0; i<whileList.size(); i++) {
				string whileNum = intToString(whileList[i]);
				symbolValues.push_back(whileNum);
			}
		} else if (type=="variable") {
			// retrieve all variable names from VarTable
			for (int i=0; i<PKB::getVarTableSize(); i++) {
				
				string varName = PKB::getVarName(i);
				symbolValues.push_back(varName);
			}
		} else if (type=="const") {
			for (int i=0; i<PKB::getConstTableSize(); i++) {
				
				string constName = PKB::getConstName(i);
				symbolValues.push_back(constName);
			}
		}

		// if no values is retrieve, add a null value to symbolValues
		if (symbolValues.size()==0) 
			symbolValues.push_back("");

		for (size_t i=0; i<symbolValues.size(); i++) {
			values.push_back(symbolValues[i]);
			findResult(index+1, values, result);
			values.erase(values.begin() + index);
		}
	}
} 

// Description: check whether the conditions of query are satisfied
// by the current list of values of symbols

bool QueryEvaluator::isQueryConditionsSatisfied(vector<string> values) {
	bool check_1 = true;
	bool check_2 = true;

	TNode root = tree.getRoot();

	for (int i=0; i<root.getNumChildren(); i++) {
		TNode child = root.getChildAtIndex(i);
		if (child.getValue()=="suchThat") {
			check_1 = isSuchThatConditionSatisfied(values, child);
		} 
		if (child.getValue()=="pattern") {
			check_2 = isPatternConditionSatisfied(values, child);
		}
	}

	return (check_1 && check_2) ? true : false;
}

// Description: check if such that condition is satisfied
bool QueryEvaluator::isSuchThatConditionSatisfied(vector<string> values, TNode node) {
	string relation;
	string arg1;
	string arg2;
	TNode relationNode = node.getChildAtIndex(0);
	TNode arg1Node = relationNode.getChildAtIndex(0);
	TNode arg2Node = relationNode.getChildAtIndex(1);

	// get relation type
	relation = relationNode.getValue();
	// get arg1 value
	if (arg1Node.getType()=="number") {
		arg1 = arg1Node.getValue();
	} else {
		// find index of symbol and its value stored in values
		int index = table.getIndex(arg1Node.getValue());
		arg1 = values[index];
	}
	// get arg2 value
	if (arg2Node.getType()=="number") {
		arg2 = arg2Node.getValue();
	} else if (arg2Node.getType()=="variable")  {
		arg2 = arg2Node.getValue();
	} else {
		// find index of symbol and its value stored in values
		int index = table.getIndex(arg2Node.getValue());
		arg2 = values[index];
	}
	// check if arg1 or arg2 takes no value
	if (arg1=="" || arg2=="") {
		return false;
	}

	// convert to type int if necessary
	int argNum1 = atoi(arg1.c_str());
	int argNum2;
	if (relation!="Uses" && relation!="Modifies") {
		argNum2 = atoi(arg2.c_str());
	} else {
		argNum2 = PKB::getVarIndex(arg2);
	}

	// check validity of relation
	if (relation=="Follows") {
		return PKB::isFollows(argNum1, argNum2);
	}  
	if (relation=="Follows*") {
		return PKB::isFollowsStar(argNum1, argNum2);
	}
	if (relation=="Parent") {
		return PKB::isParent(argNum1, argNum2);
	}
	if (relation=="Parent*") {
		// fault
		return PKB::isParentStar(argNum1, argNum2);
	}
	if (relation=="Uses") {
		return PKB::isUses(argNum1, argNum2);
	}
	if (relation=="Modifies") {
		return PKB::isModifies(argNum1, argNum2);
	}
	
	return false;
}

// Description: check if pattern condition is satisfied
bool QueryEvaluator::isPatternConditionSatisfied(vector<string> values, TNode node) {
	bool leftHandSide = false;
	bool rightHandSide = false;

	// get first child and retrieve it value from values list
	// NOTE: value is stmt# of the stmt in pattern condition
	// that we want to check
	TNode child_1 = node.getChildAtIndex(0);
	string name = child_1.getValue();
	int index = table.getIndex(name);
	string value = values[index];

	// check if symbol is not type assign
	if (table.getType(index)!="assign") {
		return false;
	}

	// check if value is not null
	if (value=="") {
		return false;
	}

	// get modified var by this assignment
	int stmtNum = atoi(value.c_str());
	vector<int> varIndexes;
	varIndexes = PKB::getModifiedVarAtStmt(stmtNum);
	int varIndex = varIndexes[0];
	string var = PKB::getVarName(varIndex);

	TNode assign("", "assign");

	// get second child and check it value
	TNode child_2 = node.getChildAtIndex(1);
	if (child_2.getType()=="underline" || 
		(child_2.getType()=="variable" && child_2.getValue()==var)) {
		leftHandSide = true;
	} else {
		if (child_2.getType()=="symbol") {
			int index = table.getIndex(child_2.getValue());
			if (values[index]==var) {
				leftHandSide = true;
			}
		}
	}

	// get third child and check it value
	TNode child_3 = node.getChildAtIndex(2);
	if (child_3.getType()=="underline") {
		rightHandSide = true;
	}

	// Get node containing assignment whose stmt number is stmtNum 
	// TNode node = PKB::findNodeOfStmt(stmtNum);
	// AST subAST; subAST.setRoot(node);
	// Tree tree; tree.setRoot(child_3);
	// rightHandSide = subAST.hasSubTree(tree);

	return (leftHandSide && rightHandSide) ? true : false;
}
*/

// Description: this function is to get the result values from list of symbols' values
// after the functions isSuchThatConditionSatisfied and isPatternConditionSatisfied finish



string QueryEvaluator::getResultAfterEvaluation(vector<string> values) {
	// get node containing symbol name of result
	TNode root = tree.getRoot();
	TNode result = root.getChildAtIndex(0);
	TNode resultChild1 = result.getChildAtIndex(0);

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

/* TESTING FUNCTION */

// Description: print all symbols' values retrieved at a certain point
void QueryEvaluator::printSymbolValues(vector<string> symbolValues) {
	cout <<endl << "Symbol values: " ;
	for (size_t i=0; i<symbolValues.size(); i++) {
		cout << symbolValues[i] << " " ;
	}
	cout <<endl;
}