#include "DesignExtractor.h"
#include "PKB.h"

DesignExtractor::DesignExtractor(void)
{
}

DesignExtractor::~DesignExtractor(void)
{
}

void DesignExtractor::buildPKB() {
	initialize();
	buildUsesTable();
	buildModifiesTable();
}

//Private Helper Methods
void DesignExtractor::initialize() {

}

void DesignExtractor::buildUsesTable() {
	
}

void DesignExtractor::buildModifiesTable() {

}