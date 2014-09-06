#pragma once

#include <string>

using namespace std;

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
