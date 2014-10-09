#include <vector>

using namespace std;

class DesignExtractor
{
public:
	DesignExtractor(void);
	~DesignExtractor(void);
	void buildPKB();

private:
	void initialize();
	void buildUsesTable();
	void buildModifiesTable();

};

