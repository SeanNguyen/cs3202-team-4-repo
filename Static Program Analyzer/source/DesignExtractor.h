#include <vector>

using namespace std;

class DesignExtractor
{
public:
	DesignExtractor(void);
	~DesignExtractor(void);
	void buildPKB();

private:
	void processModify();
	void processUses();

};

