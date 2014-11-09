#include "SyntaxHelper.h"

Symbol SyntaxHelper::getSymbolType(string type) {
	if (type.compare("prog_line")==0) {
		return Prog_line;
	} 
	if (type.compare("procedure")==0) {
		return Procedure;
	}
	if (type.compare("assign")==0) {
		return Assign;
	}
	if (type.compare("while")==0) {
		return While;
	}
	if (type.compare("if")==0) {
		return If;
	}
	if (type.compare("call")==0) {
		return CallStmt;
	}
	if (type.compare("stmt")==0) {
		return Stmt;
	}
	if (type.compare("variable")==0) {
		return Var;
	}
	if (type.compare("constant")==0) {
		return Const;
	}

	if (type.compare("Follows")==0) {
		return Follows;
	}
	if (type.compare("Follows*")==0) {
		return FollowsS ;
	}
	if (type.compare("Parent")==0) {
		return Parent;
	}
	if (type.compare("Parent*")==0) {
		return ParentS;
	}
	if (type.compare("Modifies")==0) {
		return Modifies;
	}
	if (type.compare("Uses")==0) {
		return Uses;
	}
	if (type.compare("Calls")==0) {
		return Calls;
	}
	if (type.compare("Calls*")==0) {
		return CallsS;
	}
	if (type.compare("Next")==0) {
		return Nexts;
	}
	if (type.compare("Next*")==0) {
		return NextsS;
	}
	if (type.compare("Affects")==0) {
		return Affects;
	}
	if (type.compare("Affects*")==0) {
		return AffectsS;
	}
	return Undefined;
}

string SyntaxHelper::SymbolToString(Symbol symbol) {
	switch (symbol) {
	case Program:
		return KEYWORD_PROGRAM;
	case Procedure:
		return KEYWORD_PROCEDURE;
	case StmtList:
		return KEYWORD_STMTLIST;
	case Prog_line:
		return KEYWORD_PROG_LINE;
	case Stmt:
		return KEYWORD_STMT;
	case Assign:
		return KEYWORD_ASSIGN;
	case While:
		return KEYWORD_WHILE;
	case If:
		return KEYWORD_IF;
	case CallStmt:
		return KEYWORD_CALL;
	case Var:
		return KEYWORD_VAR;
	case Const:
		return KEYWORD_CONST; 
	case Plus:
		return "+";
	case Minus:
		return "-";
	case Times:
		return "*";
		
	case Select:
		return KEYWORD_SELECT;
	case ResultCls:
		return "ResultCls";
	case Attr:
		return "Attribute";
	case SuchThatCls:
		return "SuchThatCls";
	case PatternCls:
		return "PatternCls";
	case WithCls:
		return "WithCls";
	case QuerySymbol:
		return "QuerySymbol";
	case Underline:
		return "Underline";
	case No_Underline:
		return "No underline";
	case Follows:
		return FOLLOWS_RLT;
	case FollowsS:
		return FOLLOWSSTAR_RLT;
	case Parent:
		return PARENT_RLT;
	case ParentS:
		return PARENTSTAR_RLT;
	case Modifies:
		return MODIFIES_RLT;
	case Uses:
		return USES_RLT;
	case Calls:
		return CALLS_RLT;
	case CallsS:
		return CALLSSTAR_RLT;
	case Nexts:
		return NEXT_RLT;
	case NextsS:
		return NEXTSTAR_RLT;
	case Affects:
		return AFFECTS_RLT;
	case AffectsS:
		return AFFECTSSTAR_RLT;
	default:
		return "Undefined";
	}
}

bool SyntaxHelper::isRelation(string str) {
	if (str==FOLLOWS_RLT) return true;
	if (str==FOLLOWSSTAR_RLT) return true;
	if (str==PARENT_RLT) return true;
	if (str==PARENTSTAR_RLT) return true;
	if (str==MODIFIES_RLT) return true;
	if (str==USES_RLT) return true;
	if (str==CALLS_RLT) return true;
	if (str==CALLSSTAR_RLT) return true;
	if (str==NEXT_RLT) return true;
	if (str==NEXTSTAR_RLT) return true;	
	if (str==AFFECTS_RLT) return true;	
	if (str==AFFECTSSTAR_RLT) return true;	

	return false;
}

bool SyntaxHelper::isDesignEntity(string str) {
	if (str==KEYWORD_PROCEDURE	|| str==KEYWORD_STMTLIST	||
		str==KEYWORD_STMT		|| str==KEYWORD_ASSIGN		||
		str==KEYWORD_CALL		|| str==KEYWORD_WHILE		||
		str==KEYWORD_IF			|| str==KEYWORD_VAR			||
		str==KEYWORD_CONST		|| str==KEYWORD_PROG_LINE)
		return true;
	return false;
}

bool SyntaxHelper::isNumber(string str) {
	string::const_iterator it = str.begin();
    while (it != str.end() && isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

bool SyntaxHelper::isStmtSymbol(string str) {
	if (str==KEYWORD_STMT		|| str==KEYWORD_ASSIGN		||
		str==KEYWORD_CALL		|| str==KEYWORD_WHILE		||
		str==KEYWORD_IF)
		return true;
	return false;
}