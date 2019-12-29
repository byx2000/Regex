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
		RegExprParser parser("(xyzw|(a*b))*|(c.d)*|apple");
		parser.parse();
		parser.toNFA();
		cout << parser.getNFA().toString() << endl;

		NFA nfa;
		nfa.addNode(false);
		nfa.addNode(true);
		nfa.addEdge(0, NFAEdge(1, 'a'));
		cout << nfa.toString() << endl;
	}

	_CrtDumpMemoryLeaks();
	return 0;
}