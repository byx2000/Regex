#include <iostream>
#include "Test/Test.h"
#include "Pattern/Pattern.h"
#include "NFA/DFA.h"
#include "Matcher/Matcher.h"

using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ParserTest::run();
	PatternTest::run();

	/*Pattern pat(".*abcaabcab.*");
	pat.compileToDFA();
	cout << pat.toString() << endl;

	cout << pat.match("abc") << endl;
	cout << pat.match("xyz") << endl;
	cout << pat.match("aaaaabacaaaabaaababa") << endl;
	cout << pat.match("sdjgtfuiwegjkfbmsndgfjsgdjshabcksdhfjskhjkdbsjdkfjskdb") << endl;

	Matcher matcher1 = new CharMatcher('a');
	Matcher atcher2 = new AnyCharMatcher();*/

	return 0;
}