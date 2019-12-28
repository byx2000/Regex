#include <iostream>
#include "Parser/RegExpr.h"
#include "Parser/RegExprParser.h"
#include "Test/Test.h"
#include "NFA/State.h"
#include "NFA/NFA.h"

using namespace std;

int main()
{
	ParserTest::run();

	//while (1)
	{
		NFA n1('a');
		cout << n1.toString() << endl;
		
	}

	_CrtDumpMemoryLeaks();
	return 0;
}