#include "Parser.h"
#include "QueryProcessor.h"

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

int main() {
	Parser parser;
	parser.parse("C:\Users\Saloni\Desktop\NUS\NUS YEAR 3 SEM 2\CS3201\SampleTestingSolution\SampleTestingSolution\EmptyGeneralTesting\Release\Source1.txt");

	parser.printFollows();

	return 0;
}