#include "Test.h"
#include "StopWatch.h"
#include "../Parser/RegExprParser.h"
#include "../Pattern/Pattern.h"

#include <iostream>
#include <fstream>

using namespace std;

void ParserTest::run()
{
	StopWatch watch;
	watch.begin();

	string in = "src//Test//TestCase//ParserTest//in.txt";
	string out = "src//Test//TestCase//ParserTest//out.txt";
	ifstream f1(in), f2(out);

	if (!f1)
	{
		cout << "Failed _to open file: "  << in << endl;
		exit(0);
	}

	if (!f2)
	{
		cout << "Failed _to open file: " << out << endl;
		exit(0);
	}

	string expr;
	while (f1 >> expr)
	{
		RegExprParser parser(expr);
		try
		{
			parser.parse();
		}
		catch (ParseError err)
		{
			cout << "Parser test failed: throw ParseError" << endl;
			cout << "expr: " << expr << endl;
			cout << "info: " << err.info() << endl;
			exit(0);
		}

		string ans;
		f2 >> ans;
		if (parser.getRegExpr().toString() != ans)
		{
			cout << "Parser test failed: wrong answer" << endl;
			cout << "expr: " << expr << endl;
			cout << "output: " << parser.getRegExpr().toString() << endl;
			cout << "ans: " << ans << endl;
			exit(0);
		}
	}

	watch.end();
	cout << "Parser tests passed!\ttime: " << watch.duration() << "s" << endl;
}

void PatternTest::run()
{
	StopWatch watch;
	watch.begin();
	
	test1();

	watch.end();
	cout << "Pattern tests passed!\ttime: " << watch.duration() << "s" << endl;
}

void PatternTest::test1()
{
	const int NUM_TESTCASE = 11;
	for (int i = 1; i <= NUM_TESTCASE; ++i)
	{
		string in = "src\\Test\\TestCase\\PatternTest\\test1\\regular" + to_string(i) + ".in";
		string out = "src\\Test\\TestCase\\PatternTest\\test1\\regular" + to_string(i) + ".out";
		ifstream f1(in), f2(out);

		if (!f1)
		{
			cout << "Failed _to open file: " << in << endl;
			exit(0);
		}

		if (!f2)
		{
			cout << "Failed _to open file: " << out << endl;
			exit(0);
		}

		string p, s;
		while (f1 >> p >> s)
		{
			string ans;
			f2 >> ans;

			//NFA match
			try
			{
				bool res = Pattern(p).compile().match(s);
				if ((res && ans != "Yes") || (!res && ans != "No"))
				{
					cout << "Pattern test failed: wrong answer" << endl;
					cout << "expr: " << p << endl;
					cout << "txt: " << s << endl;
					cout << "ans: " << ans << endl;
					cout << "output: " << res << endl;
					exit(0);
				}
			}
			catch (ParseError err)
			{
				cout << "Pattern test failed: throw ParseError" << endl;
				cout << "expr: " << p << endl;
				cout << "txt: " << s << endl;
				cout << "info: " << err.info() << endl;
				exit(0);
			}

			//DFA match
			try
			{
				bool res = Pattern(p).compileToDFA().match(s);
				if ((res && ans != "Yes") || (!res && ans != "No"))
				{
					cout << "Pattern test failed: wrong answer" << endl;
					cout << "expr: " << p << endl;
					cout << "txt: " << s << endl;
					cout << "ans: " << ans << endl;
					cout << "output: " << res << endl;
					exit(0);
				}
			}
			catch (ParseError err)
			{
				cout << "Pattern test failed: throw ParseError" << endl;
				cout << "expr: " << p << endl;
				cout << "txt: " << s << endl;
				cout << "info: " << err.info() << endl;
				exit(0);
			}
		}
	}
}
