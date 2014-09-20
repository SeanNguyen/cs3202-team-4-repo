#ifndef TestCall_h
#define TestCall_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class CallTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( CallTest ); // Note 3 
	CPPUNIT_TEST( testInsert );
	CPPUNIT_TEST( testisCalls );
	CPPUNIT_TEST( testisCallStar );

	CPPUNIT_TEST( testgetCallingStarProc ) ;
	CPPUNIT_TEST( testgetCalledByProc ) ;
	CPPUNIT_TEST( testgetCallingProc );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test insert
	void testInsert();

	//method to test calls
	void testisCalls();

	void testisCallStar();

	void testgetCallingStarProc();

	void testgetCalledByStarProc();

	void testgetCalledByProc();

	void testgetCallingProc();

};
#endif
    