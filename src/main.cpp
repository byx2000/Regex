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

	/*Pattern pat("(a|b|c)*abaccabac(a|b|c)*");
	pat.compileToDFA();
	cout << pat.toString() << endl;

	cout << pat.match("abaccabac") << endl;
	cout << pat.match("acbccababaccabaccbabbca") << endl;
	cout << pat.match("bbabcbaababaccabacaababaaaba") << endl;
	cout << pat.match("aaaaaaaaaaaaabbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbabacacabacbbbbbbbbbaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbb") << endl;*/

	Matcher matcher1 = new CharMatcher('a');
	Matcher atcher2 = new AnyCharMatcher();

	return 0;
}