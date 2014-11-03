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
	PKB::preCalculateStarTables();
	processUses();
	processModify();


	extractSibling();

	///////CONTAINS EXTRACTOR////////
	//extractContain();

}

//void DesignExtractor::DFSRecur(TNode * node, bool visited[]){
//	int nodeID = node -> getID();
//
//	// Mark the current node as visited
//    visited[nodeID] = true;
//
//	int numOfChildren = node -> getNumChildren();
//
//	if(numOfChildren != 0){
//		// Recur for all the vertices, child to this vertex
//		for (size_t i = 0; i < numOfChildren; i++){
//			if(!visited[nodeID]) {
//				TNode * child = node -> getChildAtIndex(i);
//				int childID = child -> getID();
//
//				//insert into containTable as long as type is not Program and not undefined
//				Symbol nodeType = node -> getType();
//				Symbol childType = child -> getType();
//				if(nodeType != Program && nodeType != Undefined && 
//					childType != Program && childType != Undefined){
//					bool result = PKB::insertContains(nodeID, childID);
//				}
//
//				DFSRecur(child, visited);
//			}
//		}
//	}
//	
//}


//void DesignExtractor::extractContain() {
//	
//	//TNode * root = PKB::getASTRoot();
//
//	//get number of nodes
//	int sizeOfAST = TNode::getGlobalId() + 1;
//
//	// Mark all the vertices as not visited
//	bool *visited = new bool [sizeOfAST];
//	for(int i = 0; i < sizeOfAST; i++)
//        visited[i] = false;
//
//	//apply depth first search on AST
////	DFSRecur(root, visited);
//}

//Private Helper Methods
void DesignExtractor::processUses() {

	int numOfProc = PKB::getProcTableSize();
	vector <int> processedProc;
	
	for(size_t proc = 0; proc < numOfProc; proc++){

		//if it has not already been processed
		if(find(processedProc.begin(), processedProc.end(), proc) == processedProc.end()){

			//for every procedure, get the called procedure
			vector <int> calledProcedures = PKB::getCalledByStarProc(proc);

			if(!calledProcedures.empty()){
				//for this procedure get all used vars in it
				for (size_t proc2 = 0; proc2 < calledProcedures.size(); proc2++){
					vector <int> allUsedVar = PKB::getUsedVarAtProc(proc);

					//get the all call stmt number which is calling proc2
					vector <int> callStmts = PKB::getCallingStmt(proc2);

					//insert used var into the primary proc
					for (size_t var = 0; var < allUsedVar.size(); var++){
						PKB::insertUsesProc(proc2, allUsedVar.at(var));

						//for every call stmt calling proc2, insert the usesVar list
						for (size_t stmt = 0; stmt < callStmts.size(); stmt++){
							PKB::insertUses(callStmts.at(stmt), allUsedVar.at(var));
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
			vector <int> calledProcedures = PKB::getCalledByStarProc(proc);
			
			if(!calledProcedures.empty()){
				for (size_t proc2 = 0; proc2 < calledProcedures.size(); proc2++){
				
					//for this procedure get all modified vars in it
					vector <int> allModifiedVar = PKB::getModifiedVarAtProc(proc);

					//get the all call stmt number which is calling proc2
					vector <int> callStmts = PKB::getCallingStmt(proc2);

					//insert modified var into the primary called proc
					for (size_t var = 0; var < allModifiedVar.size(); var++){
						PKB::insertModifiesProc(proc2, allModifiedVar.at(var));

						//for every call stmt calling proc2, insert the modifiedVar list
						for (size_t stmt = 0; stmt < callStmts.size(); stmt++){
							PKB::insertModifies(callStmts.at(stmt), allModifiedVar.at(var));
						}
					}
				}
			}
			
		}
		processedProc.push_back(proc);
	}
}

void DesignExtractor::extractSibling(){

	//queue<int> theQueue = new arrayDequeue 

	TNode * root = PKB::getASTRoot(); 
	TNode * previous; 
	int numNodes= TNode::getGlobalId() + 1;
	TNode * curr= root;
	int key;
	int value;

	for(int i=0;i<numNodes;i ++){ 
		int children=curr->getNumChildren();

		if(children == 0 & i!=(numNodes-1)){
			//deal with gng back to the previous node to branch out 
		}

		else if(children==1){
			curr=curr->getChildAtIndex(0);
			//i++;
		}
		else{
			for(int j=1;j<children;j++){
				key=curr->getChildAtIndex(j-1)->getID();
				value=curr->getChildAtIndex(j)->getID();
				PKB::insertSibling(key, value);
			}
			curr=curr->getChildAtIndex(0);
		}
	
	
	}

}


