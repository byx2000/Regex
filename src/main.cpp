#include <iostream>
#include "Parser/RegExpr.h"
#include "Parser/RegExprParser.h"
#include "Test/Test.h"
#include "NFA/State.h"
#include "NFA/NFAGraph.h"
#include "NFA/NFA.h"
#include "Pattern/Pattern.h"
#include "Test/StopWatch.h"

using namespace std;

int main()
{
	ParserTest::run();
	PatternTest::run();

	//while (1)
	{
		Pattern pat("a*b");
		pat.compile();
		cout << pat.match("aaaaaaaabb") << endl;
	}

	_CrtDumpMemoryLeaks();
	return 0;
}