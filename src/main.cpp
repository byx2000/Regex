#include <iostream>
#include "Parser/RegExpr.h"
#include "Parser/RegExprParser.h"
#include "Test/Test.h"
#include "NFA/State.h"
#include "NFA/NFA.h"

using namespace std;

int main()
{
	ParserTest::run();

	//State s;
	/*s.addTransfer(State(), 'a');
	s.addTransfer(State(), 'b');
	s.addTransfer(State(), 'c');*/
	//cout << s.toString() << endl;

	//while (1)
	{
		/*NFA n('a');
		for (char ch = 'b'; ch <= 'z'; ++ch)
		{
			NFA t(ch);
			n.concat(t);
		}
		cout << n.toString() << endl;*/

		/*NFA n1('a'), n2('b');
		n1.parallel(n2);
		cout << n1.toString() << endl;
		cout << n2.toString() << endl;*/

		/*NFA n1('a');
		n1.addClosure();
		cout << n1.toString() << endl;*/

		State s1, s2;
		s1.addTransfer(s2, ' ');
		s2.addTransfer(s1, ' ');
	}

	_CrtDumpMemoryLeaks();
	return 0;
}