#include "QueryPreprocessor.h"

/* CONSTRUCTOR */
QueryPreprocessor::QueryPreprocessor() {
}

QueryPreprocessor::QueryPreprocessor(string directory) {
	this -> fileDirectory = directory;
	this -> table = SymbolTable();
	this -> tree = QueryTree();
	this -> errors = vector<string>();
	this -> symbolCount = vector<int>();
}

/* PUBLIC METHOD */ 

// Description: this method is to start preprocess the file 
// whose directory is save in fileDirectory
void QueryPreprocessor::Preprocess() {
	readFileData();
	preprocessFileData();
}

void QueryPreprocessor::Preprocess(string query) {
	// first, reset storage (QueryRepresentator)
	QueryRepresentator::reset();

	vector<string> queryList; queryList.push_back(query);
	preprocessQuery(queryList, 0);
}

/* PRIVATE METHODS */
 
// Description: this method is to open file and 
// save only lines containing query into "fileData" list
void QueryPreprocessor::readFileData() {
	ifstream file(fileDirectory.c_str());

	if (file.is_open()) {
		// read line by line
		string line;
		int countLine = 0;
		int numOfQueries = 0;
		vector<string> query;
		while(!file.eof()) {
			getline(file, line);
			countLine++;
			// recognize first line as number of queries in file
			// change string to num here
			// set numOfQueries
			if (countLine==1) {
				numOfQueries = atoi(line.c_str());
				//cout <<"Num of queries: " << numOfQueries << endl;
			} else {

				// meet first line of query, recognize as description (useless info)
				// take no action
				if (countLine%5==3) {
				}
				// meet second line of query, recognize as declaration 
				// save into queryData
				else if (countLine%5==4) {
					query.push_back(line);
				}
				// meet third line of query, recognize as query part
				// save into queryData
				else if (countLine%5==0) {
					query.push_back(line);
				}
				// meet forth line of query, recognize as query results
				// NOTE: currently take no action
				else if (countLine%5==1) {
				}
				// meet fifth line of query, recognize as query's ending sign ("5000")
				// take no action.
				// push query to fileData. Reset query
				else if (countLine%5==2 && countLine!=2) {
					fileData.push_back(query);
					query.clear();
				}
			}
		}
		file.close();
	} else {
		cout << "Not a file directory" <<endl;
	}
}

// Description: this method is to take and preprocess query, one by one
void QueryPreprocessor::preprocessFileData() {
	// first, reset storage (QueryRepresentator)
	QueryRepresentator::reset();

	// loop: queryData, take query one by one
	for (size_t i=0; i<fileData.size(); i++) {
		vector<string> query = fileData[i];
	//	cout << i + 1 <<endl;
		preprocessQuery(query, i);
	}
}

// Description: this method is to save query data into QueryTree and SymbolTable,
// and save them into QueryRepresentator
void QueryPreprocessor::preprocessQuery(vector<string> query, int index) {
	table = SymbolTable();
	tree = QueryTree();
	errors = vector<string>();
	symbolCount = vector<int>();
	string element = "";

	for (size_t i=0; i<query.size(); i++) {
		string curLine = query[i];
		istringstream ss;
		ss.str(curLine);
		while (ss >> element) {
			if (SyntaxHelper::isDesignEntity(element)) {
				// find ending sign of this declaration (";");
				if (curLine.find_first_of(";")!=string::npos) {
					unsigned index = curLine.find_first_of(";");
					// read declaration
					string declaration = curLine.substr(0, index+1);
					preprocessDeclaration(declaration);
					// continue with the rest of curLine
					curLine = curLine.substr(index+1);
					ss.str(curLine);
				} else {
					errors.push_back("Error 001: Found no ending sign for symbol declaration of query " + i);
					return;
				}
			} else if (element==KEYWORD_SELECT) {
				//for (size_t i=0; i<table.getSize(); i++) 
				//	cout << i << "  "<<table.getType(i)<< " " <<table.getName(i)<<endl;
				preprocessQueryPart(curLine);
				ss.str("");
				ss.clear();
			} else {
				errors.push_back("Error 002: Unable to recognize symbol: " + element + " in line \n" + curLine);
			}
		} 
	}

	if (errors.size()==0) {
		//		tree.printTree();
		// call QueryOptimizer
		QueryOptimizer::optimizeQuery(table, tree, symbolCount);
		QueryRepresentator::addQuery(table, tree, true);
	} else {
		cout << "ERROR LIST: QUERY: " ;
		for (size_t i=0; i<query.size(); i++) {
			cout << query[i] << " ";
		}
		cout <<endl;
		for (size_t i=0; i<errors.size(); i++) {
			cout << errors[i] <<endl;
		}
		cout <<endl;
		QueryRepresentator::addQuery(table, tree, false);
	}
}

// Description: this method is to preprocess the declaration part of query
void QueryPreprocessor::preprocessDeclaration(string declaration) {
	// break string into words
	vector<string> list = breakStringIntoWords(declaration);

	// first word is type of symbol(s)
	string type=list[0];

	for(size_t i=1; i<list.size(); i++) {
		// expect to meet comma or semicolon
		if (i%2==0) {
			if (list[i]!="," && list[i]!=";") { 
				errors.push_back("Error 003: expect end sign");
				return;
			}
		}
		// expect to meet symbol
		else {
			if (list[i]=="," || list[i]==";")  {
				errors.push_back("Error 004: expect symbol");
				return;
			}
			string name = list[i];

			// save symbol into SymbolTable
			table.setSymbol(type, name);
			symbolCount.push_back(0);
		}
	}
}

// Description: this method is to preprocess the query part of query
void QueryPreprocessor::preprocessQueryPart(string queryPart) {
	// break string into words
	vector<string> list = breakStringIntoWords(queryPart);
	// create root node for Select
	TNode * root = new TNode(Select, "");
	// recognize result and create node for it
	TNode * result = preprocessResultNode(list, 1);
	root -> addChild(result);

	Symbol currentCondition = Undefined;
	// find and preprocess conditions of query
	for (size_t i=2; i<list.size(); i++) {
		if (list[i]=="such" && list[i+1]=="that") {
			currentCondition = SuchThatCls;
			unsigned index = findFirstElement(list, i, ")");
			if ((int)index>i) {
				vector<string> suchThatCondition = subList(list, i+2, index);
				TNode * suchThat = preprocessSuchThatCondition(suchThatCondition);
				root -> addChild(suchThat);
				// go to element after this condition
				i = index;
			}
		} else if (list[i]=="pattern") {
			currentCondition = PatternCls;
			unsigned index = findFirstElement(list, i, ")");
			if ((int)index>i) {
				vector<string> patternCondition = subList(list, i+1, index);
				TNode * pattern = preprocessPatternCondition(patternCondition);
				root -> addChild(pattern);
				// go to element after this condition
				i = index;
			}
		} else if (list[i]=="with") {
			currentCondition = WithCls;
			TNode * withCls = preprocessWithCondition(list, i);
			root -> addChild(withCls);
		} else if (list[i]=="and") {
			switch (currentCondition) {
			case SuchThatCls:
				{
					unsigned index = findFirstElement(list, i, ")");
					if ((int)index>i) {
						vector<string> suchThatCondition = subList(list, i+1, index);
						TNode * suchThat = preprocessSuchThatCondition(suchThatCondition);
						root -> addChild(suchThat);
						// go to element after this condition
						i = index;
					}
					break;
				}
			case PatternCls:
				{
					unsigned index = findFirstElement(list, i, ")");
					if ((int)index>i) {
						vector<string> patternCondition = subList(list, i+1, index);
						TNode * pattern = preprocessPatternCondition(patternCondition);
						root -> addChild(pattern);
						// go to element after this condition
						i = index;
					}
					break;
				}
			case WithCls:
				{
					currentCondition = WithCls;
					TNode * withCls = preprocessWithCondition(list, i);
					root -> addChild(withCls);
				}
			default:
				{
					errors.push_back("Error: find \"and\" with no previous clause");
					break;
				}
			}
		} else {
		}
	}

	tree.setRoot(root);
}

TNode * QueryPreprocessor::preprocessResultNode(vector<string> list, int i) {
	// FOR ITERATION 1 AND 2: BOOLEAN and single value
	if (list[i]=="BOOLEAN") {
		TNode * node = new TNode(ResultCls, "a-BOOLEAN");
		return node;
	} else {
		if (list[i]=="<") {
			//expect non-single tuple
			int j = findFirstElement(list, i, ">");
			if (j==-1) {
				errors.push_back("Error 005: invalid syntax for tuple result");
				TNode * node = new TNode();
				return node;
			}
			vector<string> tuple = subList(list, i, j);
			return preprocessTupleResult(tuple);
		} else {
			if (table.isSymbol(list[i])) {
				TNode * node = new TNode(ResultCls, "a-single");
				TNode * nodeChild = new TNode(QuerySymbol, list[i]);
				node -> addChild(nodeChild);
				countSymbol(list[i]);
				return node;
			}
			errors.push_back("Error 005: unable to find symbol: " + list[i]);
			TNode * node = new TNode();
			return node;
		}
	}
}

TNode * QueryPreprocessor::preprocessTupleResult(vector<string> list) {
	TNode * node = new TNode(ResultCls, "a-tuple");

	for (size_t i=1; i<list.size()-1; i++) {
		if (i%2==1) {
			// expect declared symbol
			if (table.isSymbol(list[i])) {
				TNode * child = new TNode(QuerySymbol, list[i]);
				node ->addChild(child);
				countSymbol(list[i]);
			} else {
				errors.push_back("Error 005: invalid symbol in tuple result: " + list[i]);
			}
		} else {
			// expect comma
			if (list[i]!=KEYWORD_COMMA) {
				errors.push_back("Error 005: invalid symbol in tuple result: " + list[i]);
			}
		}
	}

	return node;
}

// Description: this method is to preprocess the such that condition of query
TNode * QueryPreprocessor::preprocessSuchThatCondition(vector<string> list) {
	unsigned size = list.size();
	// create first node for such that
	TNode * suchThatNode = new TNode(SuchThatCls, "c");

	//expect first value to be relationship's name
	string relation = list[0];

	if (SyntaxHelper::isRelation(relation)) {
		Symbol relationType = SyntaxHelper::getSymbolType(relation);
		TNode * relationNode = new TNode(relationType);
		int size = list.size();
		if (list[1]!=KEYWORD_OPENBRACKET) {
			errors.push_back("Error 006: expect symbol ( after relation name");
		}
		if (list[size-1]!=KEYWORD_CLOSEBRACKET) {
			errors.push_back("Error 006: expect symbol ) at the end of relation");
		}
		int commaIndex = findFirstElement(list, 0, KEYWORD_COMMA);

		vector<string> arg1 = subList(list, 2, commaIndex-1);
		vector<string> arg2 = subList(list, commaIndex+1, size-2);
		TNode * arg1Node = new TNode();
		TNode * arg2Node = new TNode();
		switch (relationType) {
		case Follows:
		case FollowsS:
		case Parent:
		case ParentS:
		case Affects:
		case AffectsS:
			{
				arg1Node = preprocessStmtRef(arg1);
				arg2Node = preprocessStmtRef(arg2);
				break;
			}
		case Modifies:
		case Uses:
			{
				arg1Node = preprocessEntRef(arg1);
				arg2Node = preprocessVarRef(arg2);
				break;
			}
		case Calls:
		case CallsS:
			{
				arg1Node = preprocessEntRef(arg1);
				arg2Node = preprocessEntRef(arg2);
				break;
			}
		case Nexts:
		case NextsS:
			{
				arg1Node = preprocessLineRef(arg1);
				arg2Node = preprocessLineRef(arg2);
				break;
			}
		default:
			{
				break;
			}
		}
		relationNode -> addChild(arg1Node);
		relationNode -> addChild(arg2Node);
		suchThatNode -> addChild(relationNode);
	} else {
		errors.push_back("Error 008: not a relation name: " + relation);
	}

	return suchThatNode;
}

TNode * QueryPreprocessor::preprocessEntRef(vector<string> list) {
	TNode * node = new TNode();
	int size = list.size();

	if (size==1) {
		if (SyntaxHelper::isNumber(list[0])) {
			node = new TNode(Const, list[0]);
		} else if (list[0]==KEYWORD_UNDERLINE) {
			node = new TNode(Underline);
		} else if (table.isSymbol(list[0])) {
			node = new TNode(QuerySymbol, list[0]);
			countSymbol(list[0]);
		} else {
			errors.push_back("Error: not an entity: " + list[0]);
		}
	} else if (size==3) {
		if (list[0]=="\"" && list[2]=="\"") {
			node = new TNode(Const, list[1]);
		} else {
			// throw error here
		}
	} else {
		errors.push_back("Error: not an entity");
	}

	return node;
}

TNode * QueryPreprocessor::preprocessStmtRef(vector<string> list) {
	TNode * node = new TNode();
	int size = list.size();

	if (size==1) {
		if (SyntaxHelper::isNumber(list[0])) {
			node = new TNode(Const, list[0]);
		} else if (list[0]==KEYWORD_UNDERLINE) {
			node = new TNode(Underline);
		} else if (table.isSymbol(list[0])) {
			string type = table.getType(list[0]);
			if (type==KEYWORD_STMT || type==KEYWORD_ASSIGN ||
				type==KEYWORD_WHILE|| type==KEYWORD_IF     ||
				type==KEYWORD_CALL) {
				node = new TNode(QuerySymbol, list[0]);
				countSymbol(list[0]);
			} else {
				errors.push_back("Error: not a stmt reference: " + list[0]);
			}
		} else {
			errors.push_back("Error: not a stmt reference: " + list[0]);
		}
	} else {
		errors.push_back("Error: not a stmt reference: " + list[0]);
	}

	return node;
}

TNode * QueryPreprocessor::preprocessVarRef(vector<string> list) {
	TNode * node = new TNode();
	int size = list.size();

	if (size==1) {
		if (list[0]==KEYWORD_UNDERLINE) {
			node = new TNode(Underline);
		} else if (table.isSymbol(list[0])) {
			string type = table.getType(list[0]);
			if (type==KEYWORD_VAR) {
				node = new TNode(QuerySymbol, list[0]);
				countSymbol(list[0]);
			} else {
				errors.push_back("Error: not a variable reference: " + list[0]);
			}
		} else {
			errors.push_back("Error: not a variable reference: " + list[0]);
		}
	} else if (size==3) {
		if (list[0]=="\"" && list[2]=="\"") {
			node = new TNode(Const, list[1]);
		} else {
			errors.push_back("Error: not a variable reference");
		}
	} else {
		errors.push_back("Error: not a variable reference");
	}

	return node;
}

TNode * QueryPreprocessor::preprocessLineRef(vector<string> list) {
	TNode * node = new TNode();
	int size = list.size();

	if (size==1) {
		if (SyntaxHelper::isNumber(list[0])) {
			node = new TNode(Const, list[0]);
		} else if (list[0]==KEYWORD_UNDERLINE) {
			node = new TNode(Underline);
		} else if (table.isSymbol(list[0])) {
			node = new TNode(QuerySymbol, list[0]);
			countSymbol(list[0]);
		} else {
			errors.push_back("Error: not a line reference: " + list[0]);
		}
	} {
		errors.push_back("Error: not a line reference: " + list[0]);
	}

	return node;
} 

// Description: this method is to preprocess the pattern condition of query
TNode * QueryPreprocessor::preprocessPatternCondition(vector<string> list) {
	unsigned size = list.size();
	// create first node for pattern
	TNode * pattern = new TNode(PatternCls, "d");

	vector<string> patternContent = subList(list, 1, size-1);
	string argName = list[0];
	string argType = table.getType(argName);
	Symbol type = SyntaxHelper::getSymbolType(argType);

	switch (type) {
	case Assign:
		{
			TNode * assignNode = preprocessAssignPattern(argName, patternContent);
			pattern -> addChild(assignNode);
			break;
		}
	case While:
		{
			TNode * whileNode = preprocessWhilePattern(argName, patternContent);
			pattern -> addChild(whileNode);
			break;
		}
	case If:
		{
			TNode * ifNode = preprocessIfPattern(argName, patternContent);
			pattern -> addChild(ifNode);
			break;
		}
	default:
		{
			errors.push_back("Error 009: not a valid stmt type for pattern clause: " + argName);
			break;
		}
	}

	return pattern;
}

TNode * QueryPreprocessor::preprocessAssignPattern(string name, vector<string> list) {
	TNode * assignNode = new TNode(QuerySymbol, name);
	countSymbol(name);
	unsigned size = list.size();
	if (list[0]!=KEYWORD_OPENBRACKET || list[size-1]!=KEYWORD_CLOSEBRACKET) {
		errors.push_back("Error 010: no valid bracket for pattern");
	}
	int commaIndex = findFirstElement(list, 0, ",");

	vector<string> arg1 = subList(list, 1, commaIndex-1);
	TNode * arg1Node = preprocessVarRef(arg1);

	assignNode ->addChild(arg1Node);

	// preprocess right hand side 
	switch (size-commaIndex) {
	case 3:
		{
			// expect an underline in the right of the comma
			if (list[commaIndex+1]!=KEYWORD_UNDERLINE) {
				errors.push_back("Error 012_02: Syntax of pattern");
				return assignNode;
			}
			TNode * arg2Node = new TNode(Underline);
			assignNode ->addChild(arg2Node);
			break;
		}
	default:
		{
			if (list[commaIndex+1]!=KEYWORD_UNDERLINE || list[size-2]!=KEYWORD_UNDERLINE) {
				if (list[commaIndex+1]!="\"" || list[size-2]!="\"") {
					errors.push_back("Error 012_03: Syntax of pattern");
					return assignNode;
				}
				vector<string> expression = subList(list, commaIndex+2, size-3);
				TNode * arg2Node = new TNode(No_Underline);
				TNode * exprNode = preprocessExpressionNode(expression);
				arg2Node ->addChild(exprNode);
				assignNode ->addChild(arg2Node);
			} else {
				if (list[commaIndex+2]!="\"" || list[size-3]!="\"") {
					errors.push_back("Error 012_04: Syntax of pattern");
					return assignNode;
				}
				vector<string> expression = subList(list, commaIndex+3, size-4);
				TNode * arg2Node = new TNode(Underline);
				TNode * exprNode = preprocessExpressionNode(expression);
				arg2Node ->addChild(exprNode);
				assignNode ->addChild(arg2Node);
			}
			break;
		}
	}
	
	return assignNode;
}

TNode * QueryPreprocessor::preprocessWhilePattern(string name, vector<string> list) {
	TNode * whileNode = new TNode(QuerySymbol, name);
	countSymbol(name);
	unsigned size = list.size();
	if (list[0]!=KEYWORD_OPENBRACKET || list[size-1]!=KEYWORD_CLOSEBRACKET) {
		errors.push_back("Error 010: no valid bracket for pattern");
	}
	int commaIndex = findFirstElement(list, 0, ",");
	
	vector<string> arg1 = subList(list, 1, commaIndex-1);
	TNode * arg1Node = preprocessVarRef(arg1);

	whileNode ->addChild(arg1Node);

	// expect right hand side is underline
	if (commaIndex>(int)size-2 || list[commaIndex+1]!=KEYWORD_UNDERLINE) {
		errors.push_back("Error 012_05: syntax of pattern");
	} else {
		TNode * arg2Node = new TNode(Underline);
		whileNode ->addChild(arg2Node);
	}

	return whileNode;
}

TNode * QueryPreprocessor::preprocessIfPattern(string name, vector<string> list) {
	TNode * ifNode = new TNode(QuerySymbol, name);
	countSymbol(name);
	unsigned size = list.size();
	if (list[0]!=KEYWORD_OPENBRACKET || list[size-1]!=KEYWORD_CLOSEBRACKET) {
		errors.push_back("Error 010: no valid bracket for pattern");
	}
	int commaIndex = findFirstElement(list, 0, ",");

	vector<string> arg1 = subList(list, 1, commaIndex-1);
	TNode * arg1Node = preprocessVarRef(arg1);

	ifNode ->addChild(arg1Node);

	// expect right hand side has 2 underline signs
	if (commaIndex>(int)size-4 || list[commaIndex+1]!=KEYWORD_UNDERLINE) {
		errors.push_back("Error 012_05: syntax of pattern");
	} else {
		TNode * arg2Node = new TNode(Underline);
		ifNode ->addChild(arg2Node);
	}

	if (list[size-3]!=KEYWORD_COMMA || list[size-2]!=KEYWORD_UNDERLINE) {
		errors.push_back("Error 012_06: syntax of pattern");
	} else {
		TNode * arg3Node = new TNode(Underline);
		ifNode ->addChild(arg3Node);
	}

	return ifNode;
}

TNode * QueryPreprocessor::preprocessExpressionNode(vector<string> list) {
	TNode * exprNode = new TNode();
	unsigned size = list.size();
	// base case
	if (size==0) {
		errors.push_back("Error 013: lack in pattern expression");
	} else if (size==1) {
		string expr = list[0];
		if (expr==KEYWORD_PLUSSIGN || expr==KEYWORD_MINUSSIGN || expr==KEYWORD_MULTIPLYSIGN ||
			expr==KEYWORD_OPENBRACKET ||expr==KEYWORD_CLOSEBRACKET) {
			errors.push_back("Error 013: lack in pattern expression");
		} else {
			if (SyntaxHelper::isNumber(expr)) {
				exprNode = new TNode(Const, expr);
			} else {
				exprNode = new TNode(Var, expr);
			}
		}
	} else {
		// find last index of plus/ minus/ multiple outside of bracket
		int plusSignIndex = getLastIndexOfTokenNotInsideBracket(list, KEYWORD_PLUSSIGN);
		int minusSignIndex = getLastIndexOfTokenNotInsideBracket(list, KEYWORD_MINUSSIGN);
		int signIndex = max(plusSignIndex, minusSignIndex);
		if (signIndex < 0) {
			int multiplySignIndex = getLastIndexOfTokenNotInsideBracket(list, KEYWORD_MULTIPLYSIGN);
			// create node for multiply sign and make 2 nodes before/after it its children
			if (multiplySignIndex > 0) {
				TNode * multiplyNode = new TNode(Times);
				vector<string> sublist1 = subList(list, 0, multiplySignIndex-1);
				vector<string> sublist2 = subList(list, multiplySignIndex+1, size-1);
				TNode * node1 = preprocessExpressionNode(sublist1);
				TNode * node2 = preprocessExpressionNode(sublist2);
				multiplyNode ->addChild(node1);
				multiplyNode ->addChild(node2);
				return multiplyNode;
			} else {
				// there is a bracket covering all expression
				if (list[0]==KEYWORD_OPENBRACKET && list[size-1]==KEYWORD_CLOSEBRACKET) {
					list = subList(list, 1, size-2);
					return preprocessExpressionNode(list);
				} else {
					errors.push_back("Error 013: invalid pattern expression");
					return exprNode;
				}
			}
		} else {
			if (plusSignIndex>minusSignIndex) {
				exprNode = new TNode(Plus);
			} else {
				exprNode = new TNode(Minus);
			}
			vector<string> sublist1 = subList(list, 0, signIndex-1);
			vector<string> sublist2 = subList(list, signIndex+1, size-1);
			TNode * node1 = preprocessExpressionNode(sublist1);
			TNode * node2 = preprocessExpressionNode(sublist2);
			exprNode ->addChild(node1);
			exprNode ->addChild(node2);

			return exprNode;
		}
	}

	return exprNode;
}

TNode * QueryPreprocessor::preprocessWithCondition(vector<string> list, int index) {
	TNode * withCls = new TNode(WithCls, "b");
	int size = list.size();
	int equalSignIndex = findFirstElement(list, index, KEYWORD_EQUALSIGN);

	vector<string> arg1 = subList(list, index+1, equalSignIndex-1);
	TNode * arg1Node = preprocessAttrRef(arg1);

	withCls ->addChild(arg1Node);

	vector<string> arg2;
	if (equalSignIndex+3>= size || 
		(list[equalSignIndex+2]!=KEYWORD_DOT &&
		(list[equalSignIndex+1]!="\"" || list[equalSignIndex+3]!="\""))) {
		arg2.push_back(list[equalSignIndex+1]);
	} else {
		arg2 = subList(list, equalSignIndex+1, equalSignIndex+3);
	}
	TNode * arg2Node = preprocessAttrRef(arg2);

	withCls ->addChild(arg2Node);

	return withCls;
}

TNode * QueryPreprocessor::preprocessAttrRef(vector<string> list) {
	TNode * node = new TNode();
	int size = list.size();

	if (size==1) {
		if (SyntaxHelper::isNumber(list[0])) {
			node = new TNode(Const, list[0]);
		} else if (table.getType(list[0])==KEYWORD_PROG_LINE) {
			node = new TNode(QuerySymbol, list[0]);
			countSymbol(list[0]);
		} else {
			errors.push_back("Error: not an attribute reference: " + list[0]);
		}
	} else if (size==3) {
		if (table.isSymbol(list[0]) && list[1]==KEYWORD_DOT) {
			string type = table.getType(list[0]);
			if ((type==KEYWORD_PROCEDURE && list[2]=="procName") ||
				(type==KEYWORD_VAR && list[2]=="varName")		 ||
				(type==KEYWORD_CONST && list[2]=="value")		 ||
				(SyntaxHelper::isStmtSymbol(type) && list[2]=="stmt#")) {
				node = new TNode(QuerySymbol, list[0]);		
				countSymbol(list[0]);
			} else {
				errors.push_back("Error: not an attribute reference");
			}
		} else if (list[0]=="\"" && list[2]=="\""){
			node = new TNode(Const, list[1]);
		} else {
			errors.push_back("Error: not an attribute reference");
		}
	} else {
		errors.push_back("Error: not an attribute reference");
	}

	return node;
}

/* SUPPORTING FUCNTIONS */

void QueryPreprocessor::countSymbol(string str) {
	int index = table.getIndex(str);
	if (index!=-1) {
		symbolCount[index] ++;
	}
}

// Description: this method is to retrieve a sublist of input list
vector<string> QueryPreprocessor::subList(vector<string> list, int i, int j) {
	vector<string> subList;
	for (int index=i; index<=j; index++) {
		subList.push_back(list[index]);
	}
	return subList;
}

// Description: this method is to break a string into list of words in that string
// Furthermore, it separates elements (variable and expression, container and data inside, etc. )
vector<string> QueryPreprocessor::breakStringIntoWords(string str) {
	vector<string> list;
	string word;

	//separate elements
	for (size_t i=0; i<str.length(); i++) {
		char curChar = str.at(i);
		if (curChar=='(') {
			str = str.replace(i, 1, " ( ");
			i+=2;
		}
		if (curChar=='+') {
			str = str.replace(i, 1, " + ");
			i+=2;
		}
		if (curChar==')') {
			str = str.replace(i, 1, " ) ");
			i+=2;
		}
		if (curChar==';') {
			str = str.replace(i, 1, " ; ");
			i+=2;
		}
		if (curChar==',') {
				str = str.replace(i, 1, " , ");
				i+=2;
		}
		if (curChar=='_') {
			if ((int) i>3 && str.substr(i-4, 9) == "prog_line") {
			} else { 
				str = str.replace(i, 1, " _ ");
				i+=2;
			}
		}
		if (curChar==34) {
			str = str.replace(i, 1, " \" ");
			i+=2;
		}
		if (curChar=='.') {
			str = str.replace(i, 1, " . ");
			i+=2;
		}
		if (curChar=='<') {
			str = str.replace(i, 1, " < ");
			i+=2;
		}
		if (curChar=='>') {
			str = str.replace(i, 1, " > ");
			i+=2;
		}
		if (curChar=='=') {
			str = str.replace(i, 1, " = ");
			i+=2;
		}
	}

	istringstream ss;
	ss.str(str);
	while (ss >> word) {
		list.push_back(word);
	}
	return list;
}

// Description: this method is to find first index of an element in a list of string
unsigned int QueryPreprocessor::findFirstElement(vector<string> list, unsigned index, string element) {
	for (size_t i=index+1; i<list.size(); i++) {
		if (list[i]==element) 
			return i;
	}
	return -1;
}

unsigned int QueryPreprocessor::findLastElement(vector<string> list, unsigned index, string element) {
	for (size_t i=index; i>=0; i--) {
		if (list[i]==element) 
			return i;
	}
	return -1;
}

int QueryPreprocessor::getLastIndexOfTokenNotInsideBracket(vector<string> list, string token) {
	vector<int> depth;
	int nestedLv = 0;
	
	for (size_t i=0; i<list.size(); i++) {
		if (list[i]==KEYWORD_OPENBRACKET) nestedLv++;
		if (list[i]==KEYWORD_CLOSEBRACKET) nestedLv--;
		depth.push_back(nestedLv);
	}

	for (size_t i=list.size()-1; i>0; i--) {
		if (list[i]==token && depth[i]==0) {
			return i;
		}
	}

	return -1;
}