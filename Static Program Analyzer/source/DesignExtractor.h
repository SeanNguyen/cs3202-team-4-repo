#include <vector>
#include "PKB.h"

using namespace std;

class DesignExtractor
{
public:
	DesignExtractor(void);
	~DesignExtractor(void);
	void buildPKB();
	

private:
	static void processModify();
	static void processUses();


    ////////SIBLINGS EXTRACTOR//////////
	static void extractSibling();
	

	////////CONTAINS EXTRACTOR//////////

	static void extractContain();
	static void DFSRecur(TNode * node);
};

