#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <string>
#include <math.h>
#include "TutorialConfig.h"
#include "salApplication.h"

class MyApp: public sal::Application
{
public:
	MyApp( int appId, int maxNumberOfThreads );

private:
	// put your variables (e.g., sal::ActiveObjects etc.) and methods here
};

MyApp::MyApp( int appId, int maxNumberOfThreads ):
	sal::Application( appId, maxNumberOfThreads )
{
	// do your initialization and start your threads here
}

int main(int argc, char *argv[])
{
	MyApp myApp( 2, 5 );
    return myApp.run();

	return 0;
}
