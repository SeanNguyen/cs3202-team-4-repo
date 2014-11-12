#include "DesignExtractor.h"

#include "PKB.h"
#include "TNode.h"
#include <queue> 

     
     

DesignExtractor::DesignExtractor(void)
{
}

DesignExtractor::~DesignExtractor(void)
{
}

void DesignExtractor::buildPKB() {
	
	PKB::calculateASTSize();

	///////CONTAINS EXTRACTOR////////
	extractContain();
	///////SIBLING EXTRACTOR////////
	extractSibling();

	PKB::preCalculateStarTables();
	
	processUses();
	processModify();

	//nodeIdToRealId();
	




}

void nodeidtorealid(TNode * node){
	int astsize = PKB::getASTSize();

	int nodeId=node->getID();
	Symbol nodeType = node->getType();
	string nodeValue = node->getValue();
	int realId=0;
	bool temp1, temp2;
	
	switch(nodeType){
		case(Const):{
			realId = PKB::getConstIndex(nodeValue);
			break;
					}
		case(Procedure):{
			vector<int> temp =PKB::getProcIndex(nodeValue);
			realId=temp.front();
			break;
						}
		case(Var):{
			realId=PKB::getVarIndex(nodeValue);
			break;
				  }
	}

	temp1=PKB::insertNodeToReal(nodeId, realId);
	temp2=PKB::insertNodeType(nodeId, SyntaxHelper::SymbolToString(nodeType));

}


void DesignExtractor::DFSRecur(TNode * node){
	
	//call method to handle dealing with the nodeIdtorReal/type --> the nodes here might be called multiple times but all will be called 
	nodeidtorealid(node);

	int nodeID = node -> getID();

	int numOfChildren = node -> getNumChildren();

	if(numOfChildren != 0){
		// Recur for all the vertices, child to this vertex
		for (size_t i = 0; i < numOfChildren; i++){
				TNode * child = node -> getChildAtIndex(i);
				int childID = child -> getID();

				//insert into containTable as long as type is not Program and not undefined
				Symbol nodeType = node -> getType();
				Symbol childType = child -> getType();
				if(nodeType != Program && nodeType != Undefined && 
					childType != Program && childType != Undefined){
						if (nodeID==16) {
							node -> printTNode();
						}
					bool result = PKB::insertContains(nodeID, childID);
				}

				DFSRecur(child);
		}
	}
	
}


void DesignExtractor::extractContain() {	
	TNode * root = PKB::getASTRoot();
	//apply depth first search on AST
	DFSRecur(root);
}

//Private Helper Methods
void DesignExtractor::processUses() {
	int numOfProc = PKB::getProcTableSize();
	vector <int> processedProc;
	
	for(size_t proc = 0; proc < numOfProc; proc++){

		//if it has not already been processed
		if(find(processedProc.begin(), processedProc.end(), proc) == processedProc.end()){

			//for every procedure, get the called procedure
			vector <int> calledProcedures = PKB::getCallingStarProc(proc);
			
			if(!calledProcedures.empty()){
				for (size_t proc2 = 0; proc2 < calledProcedures.size(); proc2++){
				
					//for this procedure get all modified vars in it
					vector <int> allUsedVar = PKB::getUsedVarAtProc(calledProcedures[proc2]);

					//get the all call stmt number which is calling proc2
					vector <int> callStmts = PKB::getCallingStmt(calledProcedures[proc2]);

					//insert modified var into the primary called proc
					for (size_t var = 0; var < allUsedVar.size(); var++){
						PKB::insertUsesProc(proc, allUsedVar[var]);

						//for every call stmt calling proc2, insert the modifiedVar list
						for (size_t stmt = 0; stmt < callStmts.size(); stmt++){
							PKB::insertUses(callStmts[stmt], allUsedVar[var]);
							// for every parent star stmt of callStmt[stmt], insert modifiedVar list
							vector <int> parentStarStmts = PKB::getParentStarStmt(callStmts[stmt]);
							for (size_t stmt1=0; stmt1<parentStarStmts.size(); stmt1++) {
								PKB::insertUses(parentStarStmts[stmt1], allUsedVar[var]);
							}
						}
					}
				}
			}
			
		}
		processedProc.push_back(proc);
	}
}

void DesignExtractor::processModify() {
	int numOfProc = PKB::getProcTableSize();
	vector <int> processedProc;
	
	for(size_t proc = 0; proc < numOfProc; proc++){

		//if it has not already been processed
		if(find(processedProc.begin(), processedProc.end(), proc) == processedProc.end()){

			//for every procedure, get the called procedure
			vector <int> calledProcedures = PKB::getCallingStarProc(proc);
			
			if(!calledProcedures.empty()){
				for (size_t proc2 = 0; proc2 < calledProcedures.size(); proc2++){
				
					//for this procedure get all modified vars in it
					vector <int> allModifiedVar = PKB::getModifiedVarAtProc(calledProcedures[proc2]);

					//get the all call stmt number which is calling proc2
					vector <int> callStmts = PKB::getCallingStmt(calledProcedures[proc2]);

					//insert modified var into the primary called proc
					for (size_t var = 0; var < allModifiedVar.size(); var++){
						PKB::insertModifiesProc(proc, allModifiedVar[var]);

						//for every call stmt calling proc2, insert the modifiedVar list
						for (size_t stmt = 0; stmt < callStmts.size(); stmt++){
							PKB::insertModifies(callStmts[stmt], allModifiedVar[var]);
							// for every parent star stmt of callStmt[stmt], insert modifiedVar list
							vector <int> parentStarStmts = PKB::getParentStarStmt(callStmts[stmt]);
							for (size_t stmt1=0; stmt1<parentStarStmts.size(); stmt1++) {
								PKB::insertModifies(parentStarStmts[stmt1], allModifiedVar[var]);
							}
						}
					}
				}
			}
			
		}
		processedProc.push_back(proc);
	}
}

void DesignExtractor::extractSibling(){

	bool test=false;

	//get size of contains table
	int astSize = PKB::getASTSize();
	//int containsSize = PKB::getContainTableSize();
	//cout << containsSize;

	//cout<< "The Size of the AST (in sibling mtd ) is: " << (astSize) << "\n";

	for (int i = 0; i < astSize; i++) {
		vector <int> children = PKB::getContaining(i);

		if(children.size() > 1){
			for (int j = 1; j < children.size(); j++){
				test = PKB::insertSibling(children[j-1], children[j]);
			}
		}
	}
}


