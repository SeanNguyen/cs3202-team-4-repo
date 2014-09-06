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

	return Undefined;
}