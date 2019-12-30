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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ParserTest::run();
	PatternTest::run();

	return 0;
}