#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TextTestProgressListener.h>

using namespace std;

int main(int argc, char* argv[])
{
	// Create the event manager and test controller
	CppUnit::TestResult controller;

	// Add a listener that colllects test result
	CppUnit::TestResultCollector result;
	controller.addListener( &result );

	// Add a listener that print dots as test run.
	CppUnit::TextTestProgressListener progress;
	controller.addListener( &progress );

	// Add the top suite to the test runner
	CppUnit::TestRunner runner;
	runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );   

	try
	{
		std::cout << "Running ";
		CPPUNIT_NS::TestRunner runner;
		runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
		runner.run( controller );

		std::cerr << std::endl;

		// Print test in a compiler compatible format.
		CppUnit::CompilerOutputter outputter( &result, std::cerr );
		outputter.write();
		cin.get();
	}
	catch ( std::invalid_argument &e )  // Test path not resolved
	{
		std::cerr  <<  std::endl  
			<<  "ERROR: "  <<  e.what()
			<< std::endl;
		return 0;
	}

	return result.wasSuccessful() ? 0 : 1;
}