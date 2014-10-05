#ifndef Next_h
#define Next_h

#include <vector>
#include <map>

using namespace std;

class Next {
private:
	map < int, vector <int> > mapNext;
	map < int, vector <int> > mapPrevious;
	map < int, bool > isProcessed;

public :
	//public methods
	int insertNext(int stmt1, int stmt2);
	bool isNext(int stmt1, int stmt2);
	bool isNextStar(int stmt1, int stmt2);
	vector<int> getNextStmts(int stmtNo);
	vector<int> getNextStarStmts(int stmtNo);
	vector <int> getPreviousStmts(int stmtNo);
	vector <int> getPreviousStarStmts(int stmtNo);

private:
	bool isNextStarInternal (int stmt1, int stmt2);
};
#endif
