#pragma once

#include <string>

using namespace std;


const string KEYWORD_ASSIGNMENT = "assignment";

const string KEYWORD_SELECT = "Select";
const string KEYWORD_PROGRAM = "program";
const string KEYWORD_PROCEDURE = "procedure";
const string KEYWORD_STMTLIST = "stmtList";
const string KEYWORD_PROG_LINE = "prog_line";
const string KEYWORD_STMT = "stmt";
const string KEYWORD_ASSIGN = "assign";
const string KEYWORD_CALL = "call";
const string KEYWORD_IF = "if";
const string KEYWORD_THEN = "then";
const string KEYWORD_ELSE = "else";
const string KEYWORD_WHILE = "while";
const string KEYWORD_VAR = "variable";
const string KEYWORD_CONST = "constant";
const string KEYWORD_OPENCURLYBRACKET = "{";
const string KEYWORD_CLOSECURLYBRACKET = "}";
const string KEYWORD_OPENBRACKET = "(";
const string KEYWORD_CLOSEBRACKET = ")";
const string KEYWORD_EQUALSIGN = "=";
const string KEYWORD_COMMA = ",";
const string KEYWORD_SEMICOLON = ";";
const string KEYWORD_PLUSSIGN = "+";
const string KEYWORD_MINUSSIGN = "-";
const string KEYWORD_MULTIPLYSIGN = "*";
const string KEYWORD_UNDERLINE = "_";

const string FOLLOWS_RLT = "Follows";
const string FOLLOWSSTAR_RLT = "Follows*";
const string PARENT_RLT = "Parent";
const string PARENTSTAR_RLT = "Parent*";
const string MODIFIES_RLT = "Modifies";
const string USES_RLT = "Uses";
const string CALLS_RLT = "Calls";
const string CALLSSTAR_RLT = "Calls*";
const string NEXT_RLT = "Next";
const string NEXTSTAR_RLT = "Next*";
const string AFFECTS_RLT = "Affects";
const string AFFECTSSTAR_RLT = "Affects*";

enum Symbol {
	Undefined,

	Program,
	Procedure,
	StmtList, Assign, While, If, CallStmt,
	Var, Const,
	Plus, Minus, Times,

	Select,
	QuerySymbol,
	ResultCls, SuchThatCls, PatternCls, WithCls,
	Follows, FollowsS, Parent, ParentS, Uses, Modifies, 
	Calls, CallsS, Nexts, NextsS, Affects, AffectsS,
	
	Prog_line, Stmt, Underline, No_Underline
};

class SyntaxHelper {
public:
	static Symbol getSymbolType(string);
	static string SymbolToString(Symbol symbol);
	static bool isRelation(string);
};
