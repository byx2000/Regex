#include <iostream>
#include "Test/Test.h"
#include "Pattern/Pattern.h"
#include "Parser/RegExprParser.h"

using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	PatternTest::run();

	RegParser parser("a*");
	NFA nfa;
	parser.parse(nfa);
	cout << nfa.toString() << endl;

	return 0;
}