#include <iostream>
#include "Parser/RegExpr.h"
#include "Parser/RegExprParser.h"
#include "Test/Test.h"
#include "NFA/State.h"
#include "NFA/NFAGraph.h"
#include "NFA/NFA.h"

using namespace std;

int main()
{
	ParserTest::run();

	//while (1)
	{
		RegExprParser parser("xy(ab|c)*|zw");
		parser.parse();
		parser.toNFA();

		NFAGraph ng = parser.getNFA();
		cout << ng.toString() << endl;

		NFA nfa = ng.toNFA();
		cout << nfa.toString() << endl;
	}

	_CrtDumpMemoryLeaks();
	return 0;
}