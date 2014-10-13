#include "DesignExtractor.h"
#include "PKB.h"


DesignExtractor::DesignExtractor(void)
{
}

DesignExtractor::~DesignExtractor(void)
{
}

void DesignExtractor::buildPKB() {
	processUses();
	processModify();
}

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
					vector <int> allUsedVar = PKB::getUsedVarAtProc(proc2);

					//get the all call stmt number which is calling proc2
					vector <int> callStmts = PKB::getCallingStmt(proc2);

					//insert used var into the primary proc
					for (size_t var = 0; var < allUsedVar.size(); var++){
						PKB::insertUsesProc(proc, var);

						//for every call stmt calling proc2, insert the usesVar list
						for (size_t stmt = 0; stmt < callStmts.size(); stmt++){
							PKB::insertUses(stmt, var);
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
					vector <int> allModifiedVar = PKB::getModifiedVarAtProc(proc2);

					//get the all call stmt number which is calling proc2
					vector <int> callStmts = PKB::getCallingStmt(proc2);

					//insert modified var into the primary proc
					for (size_t var = 0; var < allModifiedVar.size(); var++){
						PKB::insertModifiesProc(proc, var);

						//for every call stmt calling proc2, insert the modifiedVar list
						for (size_t stmt = 0; stmt < callStmts.size(); stmt++){
							PKB::insertModifies(stmt, var);
						}
					}
				}
			}
			
		}
		processedProc.push_back(proc);
	}
}


