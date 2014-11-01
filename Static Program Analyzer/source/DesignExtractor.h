#include <vector>

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


	static void calculateContain();
	static bool insertContains(int nodeContaining, int nodeContained);
	
};

