#ifndef TestUse_h
#define TestUse_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class UseTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( UseTest ); // Note 3 
	CPPUNIT_TEST( testInsert );
	CPPUNIT_TEST( testisUse );
	CPPUNIT_TEST( testgetUsedVarAtStmt ) ;
	CPPUNIT_TEST( testgetStmtUsingVar ) ;
	CPPUNIT_TEST( testgetAllUsingStmt ) ;
	CPPUNIT_TEST( testgetAllUsedVar ) ;

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test insert
	void testInsert();

	void testisUse();
		
	void testgetUsedVarAtStmt();

	void testgetStmtUsingVar();

	void testgetAllUsingStmt();

	void testgetAllUsedVar();

};
#endif
    