#pragma once

#include <string>

using namespace std;


const string KEYWORD_ASSIGNMENT = "assignment";

const string KEYWORD_SELECT = "Select";
const string KEYWORD_PROGRAM = "program";
const string KEYWORD_PROCEDURE = "procedure";
const string KEYWORD_PROG_LINE = "prog_line";
const string KEYWORD_STMT = "stmt";
const string KEYWORD_ASSIGN = "assign";
const string KEYWORD_CALL = "call";
const string KEYWORD_IF = "if";
const string KEYWORD_WHILE = "while";
const string KEYWORD_VAR = "variable";
const string KEYWORD_CONST = "const";



enum Symbol {
	Undefined,

	Program,
	Procedure,
	StmtList, Assign, While, If,
	Var, Const,
	Plus, Minus, Times,

	Select,
	QuerySymbol,
	ResultCls, SuchThatCls, PatternCls, WithCls,
	Follows, FollowsS, Parent, ParentS, Uses, Modifies, Calls, CallsS,
	
	Prog_line, Stmt, Underline
};

class SyntaxHelper {
public:
	static Symbol getSymbolType(string);
};