#include <iostream>
#include "Test/Test.h"
#include "Pattern/Pattern.h"
#include "Parser/RegExprParser.h"

using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//ParserTest::run();
	PatternTest::run();

	RegParser parser(".*sdgd|sfgd.*");
	NFA nfa;
	parser.parse(nfa);
	cout << nfa.toString() << endl;

	return 0;
}