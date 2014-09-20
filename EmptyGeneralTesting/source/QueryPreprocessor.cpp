#include "QueryPreprocessor.h"

/* CONSTRUCTOR */
QueryPreprocessor::QueryPreprocessor() {
}

QueryPreprocessor::QueryPreprocessor(string directory) {
	this -> fileDirectory = directory;
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
	preprocessQuery(queryList);
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
		preprocessQuery(query);
	}
}

// Description: this method is to save query data into QueryTree and SymbolTable,
// and save them into QueryRepresentator
void QueryPreprocessor::preprocessQuery(vector<string> query) {
	SymbolTable table;
	QueryTree tree;
	vector<string> errors;
	string element = "";

	for (size_t i=0; i<query.size(); i++) {
		string curLine = query[i];
		istringstream ss;
		ss.str(curLine);
		while (ss >> element) {
			if (element==KEYWORD_PROG_LINE	|| element==KEYWORD_ASSIGN	||
				element==KEYWORD_STMT		|| element==KEYWORD_VAR	||
				element==KEYWORD_CONST	|| element==KEYWORD_WHILE	||
				element==KEYWORD_IF) {
				// find ending sign of this declaration (";");
				if (curLine.find_first_of(";")!=string::npos) {
					unsigned index = curLine.find_first_of(";");
					// read declaration
					string declaration = curLine.substr(0, index+1);
					preprocessDeclaration(table, declaration, errors);
					// continue with the rest of curLine
					curLine = curLine.substr(index+1);
					ss.str(curLine);
				} else {
					errors.push_back("Syntax error: Found no ending sign for symbol declaration of query " + i);
					return;
				}
			} else if (element==KEYWORD_SELECT) {
				//for (size_t i=0; i<table.getSize(); i++) 
				//	cout << i << "  "<<table.getType(i)<< " " <<table.getName(i)<<endl;
				preprocessQueryPart(tree, table, curLine, errors);
				ss.str("");
				ss.clear();
			} else {
				errors.push_back("Syntax error: Unable to recognize symbol: " + element + " in line \n" + curLine);
			}
		} 
	}

	if (errors.size()==0) {
		//		tree.printTree();
		QueryRepresentator::addQuery(table, tree, true);
	} else {
		cout << "ERROR LIST "<<endl;
		for (size_t i=0; i<errors.size(); i++) {
			cout << errors[i] <<endl;
		}
		cout <<endl;
		QueryRepresentator::addQuery(table, tree, false);
	}
}

// Description: this method is to preprocess the declaration part of query
void QueryPreprocessor::preprocessDeclaration(SymbolTable& table, string declaration, vector<string>& errors) {
	// break string into words
	vector<string> list = breakStringIntoWords(declaration);

	// first word is type of symbol(s)
	string type=list[0];

	for(size_t i=1; i<list.size(); i++) {
		// expect to meet comma or semicolon
		if (i%2==0) {
			if (list[i]!="," && list[i]!=";") { 
				errors.push_back("Syntax error: expect end sign");
				return;
			}
		}
		// expect to meet symbol
		else {
			if (list[i]=="," || list[i]==";")  {
				errors.push_back("Syntax error: expect symbol");
				return;
			}
			string name = list[i];

			// save symbol into SymbolTable
			table.setSymbol(type, name);
		}
	}
}


// Description: this method is to preprocess the query part of query
void QueryPreprocessor::preprocessQueryPart(QueryTree& tree, SymbolTable table, string queryPart, vector<string>& errors) {
	// break string into words
	vector<string> list = breakStringIntoWords(queryPart);
	// create root node for Select
	TNode * root = new TNode(Select, "");
	// recognize result and create node for it
	TNode * result = new TNode(ResultCls, "single");
	// check if result is a symbol
	if (!table.isSymbol(list[1])) {
		errors.push_back("Error: not a defined symbol: " + list[1]);
	}
	TNode * resultChild = new TNode(QuerySymbol, list[1]);
	result -> addChild(resultChild);
	root -> addChild(result);

	// find and preprocess conditions of query
	for (size_t i=2; i<list.size(); i++) {
		if (list[i]=="such" && list[i+1]=="that") {
			unsigned index = findFirstElement(list, i, ")");
			if ((int)index>i) {
				vector<string> suchThatCondition = subList(list, i, index);
				TNode * suchThat = preprocessSuchThatCondition(suchThatCondition, table, errors);
				root -> addChild(suchThat);
				// go to element after this condition
				i = index;
			}
		} else if (list[i]=="pattern") {
			unsigned index = findFirstElement(list, i, ")");
			if ((int)index>i) {
				vector<string> patternCondition = subList(list, i, index);
				TNode * pattern = preprocessPatternCondition(patternCondition, table, errors);
				root -> addChild(pattern);
				// go to element after this condition
				i = index;
			}
		} else if (list[i]=="with") {
			TNode * withCls = preprocessWithCondition(list, table, errors, i);
		} else {
			cout <<  "";
		}
	}

	tree.setRoot(root);
}

// Description: this method is to preprocess the such that condition of query
TNode * QueryPreprocessor::preprocessSuchThatCondition(vector<string> list, SymbolTable table, vector<string>& errors) {
	unsigned size = list.size();
	// create first node for such that
	TNode * suchThatNode = new TNode(SuchThatCls);

	//expect second node to be relationship's name
	string relation = list[2];

	if (SyntaxHelper::isRelation(relation)) {
		TNode * relationNode = new TNode(SyntaxHelper::getSymbolType(relation));
		
		if (list[3]!="(") {
			errors.push_back("Expect symbol ( after relation name");
		}

		int commaIndex=0;
		if (list[5]==",") {
			commaIndex=5;
			string arg1 = list[4];
			if (isNumber(arg1)) {
				TNode * arg1Node = new TNode(Const, arg1);
				relationNode -> addChild(arg1Node);
			} else {
				TNode * arg1Node = new TNode(QuerySymbol, arg1);
				relationNode -> addChild(arg1Node);
			}
		} else if (list[7]==",") {
			commaIndex = 7;
			// expect a procedure name
			TNode * arg1Node = new TNode(Const, list[5]);
			relationNode -> addChild(arg1Node);
		}

		if (list[commaIndex+2]==")") {
			string arg2 = list[commaIndex+1];
			if (isNumber(arg2)) {
				TNode * arg2Node = new TNode(Const, arg2);
				relationNode -> addChild(arg2Node);
			} else {
				TNode * arg2Node = new TNode(QuerySymbol, arg2);
				relationNode -> addChild(arg2Node);
			}
		} else if (list[commaIndex+4]==")") {
			// expect a name
			TNode * arg2Node = new TNode(Const, list[commaIndex+2]);
			relationNode -> addChild(arg2Node);
		} else {
			errors.push_back("Error: no sign of ending for relation");
		}

		suchThatNode -> addChild(relationNode);
	} else {
		errors.push_back("Not a relation name: " + relation);
	}

	return suchThatNode;
}

// Description: this method is to preprocess the pattern condition of query
TNode * QueryPreprocessor::preprocessPatternCondition(vector<string> list, SymbolTable table, vector<string>& errors) {
	unsigned size = list.size();
	// create first node for pattern
	TNode * pattern = new TNode(PatternCls);

	// expect second element as name of assignment symbol
	string assignSymbol = list[1];
	if (false) {
	}
	TNode * assignNode = new TNode(QuerySymbol, assignSymbol);
	pattern -> addChild(assignNode);

	// expect bracelets
	if (list[2]!="(" || list[size-1]!=")") {
	}
	
	// find index of comma used to separate content
	unsigned index = findFirstElement(list, 2, ",");
	
	// process argument 1 of pattern
	if ((int)index==4) {
		// expect underline or variable symbol in argument 1.
		if (list[3]=="_") {
			TNode * arg1Node = new TNode(Underline);
			pattern -> addChild(arg1Node);
		} else {
			if (table.getType(list[3])!= "variable") {
				errors.push_back("Error: unable to find symbol: " + list[3] + " in pattern");
			} else {
				TNode * arg1Node = new TNode(QuerySymbol, list[3]);
				pattern -> addChild(arg1Node);
			}
		}
	} else if ((int)index==6) {
		// expect name of variable
		if (list[3]!="\"" || list[5]!="\"") {
		}
		TNode * arg1Node = new TNode (Var, list[4]);
		pattern -> addChild(arg1Node);
	}

	// process argument 2 of pattern
	// NOTE: for now, we just process with argument
	// of at most 1 plus expression
	if ((int)(size-index)==3) {
		// expect underline
		if (list[index+1]!="_") {
		}
		TNode * arg2Node = new TNode(Underline);
		pattern -> addChild(arg2Node);
	} else if ((int)(size-index)==7) {
		// expect one variable name
		if (list[index+1]!="_" || list[index+2]!="\"" ||
			list[size-3]!="\"" || list[size-2]!="_") {
		}
		string arg2 = list[index+3]; 
		if (isNumber(arg2)) {
			TNode * arg2Node = new TNode(Const, arg2);
			pattern -> addChild(arg2Node);
		} else {
			TNode * arg2Node = new TNode(Var, arg2);
			pattern -> addChild(arg2Node);
		}
	}  else if ((int)(size-index)==9) {
		if (list[index+1]!="_" || list[index+2]!="\"" ||
			list[size-3]!="\"" || list[size-2]!="_") {
		}
		if (list[index+4]!="+") {
		}
		TNode * arg2Node = new TNode(Plus);
		
		string factor1 = list[index+3];
		string factor2 = list[index+5];

		if (isNumber(factor1)) {
			TNode * factor1Node = new TNode(Const, factor1);
			arg2Node -> addChild(factor1Node);
		} else {
			TNode * factor1Node = new TNode(Var, factor1);
			arg2Node -> addChild(factor1Node);
		}

		if (isNumber(factor2)) {
			TNode * factor2Node = new TNode(Const, factor2);
			arg2Node -> addChild(factor2Node);
		} else {
			TNode * factor2Node = new TNode(Var, factor2);
			arg2Node -> addChild(factor2Node);
		}
		pattern -> addChild(arg2Node);
	} else {
	} 

	return pattern;
}

TNode * QueryPreprocessor::preprocessWithCondition(vector<string> list, SymbolTable table, vector<string> & errors, int index) {
	TNode * withCls = new TNode(WithCls);

	return withCls;
}

/* SUPPORTING FUCNTIONS */

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

// Description: this method is to check if a string is a number or not
bool QueryPreprocessor::isNumber(string str) {
	string::const_iterator it = str.begin();
    while (it != str.end() && isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

/* TESTING METHODS */

// Description: this method is to print fileData for testing 
void QueryPreprocessor::printFileData() {
	for (size_t i=0; i<fileData.size(); i++) {
		cout << "	Query " << i <<endl;
		vector<string> query = fileData[i];
		if (query.size()==2) {
			cout << query[0] << endl;
			cout << query[1] << endl;
		}
	}
}