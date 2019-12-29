#include <iostream>
#include "Parser/RegExpr.h"
#include "Parser/RegExprParser.h"
#include "Test/Test.h"
#include "NFA/State.h"
#include "NFA/NFAGraph.h"
#include "NFA/NFA.h"
#include "Pattern/Pattern.h"

using namespace std;

int main()
{
	ParserTest::run();

	//while (1)
	{
		Pattern pat("abc");
		pat.compile();
		pat.compile();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}