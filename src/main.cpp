#include <iostream>
#include "Test/Test.h"
#include "Pattern/Pattern.h"
#include "Parser/RegExprParser.h"
#include "Common/Charset.h"

using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	PatternTest::run();

	return 0;
}