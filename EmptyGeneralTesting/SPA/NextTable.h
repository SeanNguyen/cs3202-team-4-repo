#ifndef Next_h
#define Next_h

#include <vector>
#include <utility>
#include <iostream>

using namespace std;

class Next
{
public :

	std::vector<std::vector<bool>> nextTable;
	

	// Constructor
	Next();  
  
	// Method to check if next relationship exists
	bool isNext(int n1, int n2);
  
	// Method to insert a pair of line numbers
	int insertNext(int n1, int n2);

	// Method to check if line numbers are nextStar
	//bool isNextStar(int n1, int n2);

	//Method to get the first parameter in the NextStar relationship --> Next*(n1, x)
	//std::vector<int> getNextOneStarLine(int n1);

	//Method to get the second parameter in the NextStar relationship --> Next*(x, n1)
	//std::vector<int> getNextTwoStarLine(int n1);

	// Method to get the list of line numbers next to n1
	std::vector<int> getNextOneLine(int n1);

	// Method to get the list of line numbers for which the next line number is n1
	std::vector<int> getNextTwoLine(int n1);

private:
	//std::vector<int> getNextOneStarLineHelper(int n1, std::vector<int> &accumulated_result);
	//std::vector<int> getNextTwoStarLineHelper(int n1, std::vector<int> &accumulated_result);
	int MAX_SIZE;
};
#endif
