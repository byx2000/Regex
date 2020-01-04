#include "Test.h"
#include "StopWatch.h"
#include "../Parser/RegParser.h"
#include "../Pattern/Pattern.h"
#include "../Common/Error.h"

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

void PatternTest::run()
{
	StopWatch watch;
	watch.begin();
	
	test1();
	test2();
	test3();

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
					cout << "file: " << in << endl;
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
				cout << "file: " << in << endl;
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
					cout << "file: " << in << endl;
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
				cout << "file: " << in << endl;
				cout << "Pattern test failed: throw ParseError" << endl;
				cout << "expr: " << p << endl;
				cout << "txt: " << s << endl;
				cout << "info: " << err.info() << endl;
				exit(0);
			}
		}
	}

	cout << "Test 1 finished." << endl;
}

void PatternTest::test2()
{
	for (char c = 'a'; c <= 'z'; ++c)
	{
		string p, t;
		p.push_back(c);
		t.push_back(c);
		assert(Pattern(p).compile().match(t));
		assert(Pattern(p).compileToDFA().match(t));
	}

	const int NUM_TESTCASE = 3;
	for (int i = 1; i <= NUM_TESTCASE; ++i)
	{
		string in = "src\\Test\\TestCase\\PatternTest\\test2\\match" + to_string(i) + ".in";
		string out = "src\\Test\\TestCase\\PatternTest\\test2\\match" + to_string(i) + ".out";
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

		string p;
		f1 >> p;

		//NFA match
		{
			Pattern pat(p);
			try
			{
				pat.compile();
			}
			catch (ParseError err)
			{
				cout << "file: " << in << endl;
				cout << "Pattern test failed: wrong answer" << endl;
				cout << "expr: " << p << endl;
				exit(0);
			}

			string txt;
			f1 >> txt;
			while (f1 >> txt)
			{
				bool res = pat.match(txt);
				string ans;
				f2 >> ans;
				if ((res && ans != "YES") || (!res && ans != "NO"))
				{
					cout << "file: " << in << endl;
					cout << "Pattern test failed: wrong answer" << endl;
					cout << "expr: " << p << endl;
					cout << "txt: " << txt << endl;
					cout << "ans: " << ans << endl;
					cout << "output: " << res << endl;
					exit(0);
				}
			}
		}

		//DFA match
		{
			Pattern pat(p);
			try
			{
				pat.compileToDFA();
			}
			catch (ParseError err)
			{
				cout << "file: " << in << endl;
				cout << "Pattern test failed: wrong answer" << endl;
				cout << "expr: " << p << endl;
				exit(0);
			}

			string txt;
			f1 >> txt;
			while (f1 >> txt)
			{
				bool res = pat.match(txt);
				string ans;
				f2 >> ans;
				if ((res && ans != "YES") || (!res && ans != "NO"))
				{
					cout << "file: " << in << endl;
					cout << "Pattern test failed: wrong answer" << endl;
					cout << "expr: " << p << endl;
					cout << "txt: " << txt << endl;
					cout << "ans: " << ans << endl;
					cout << "output: " << res << endl;
					exit(0);
				}
			}
		}
	}

	cout << "Test 2 finished." << endl;
}

void PatternTest::test3()
{
	for (char c = 'A'; c <= 'Z'; ++c)
	{
		string p, t;
		p.push_back(c);
		t.push_back(c);
		assert(Pattern(p).compile().match(t));
		assert(Pattern(p).compileToDFA().match(t));
	}

	for (char c = '0'; c <= '9'; ++c)
	{
		string p, t;
		p.push_back(c);
		t.push_back(c);
		assert(Pattern(p).compile().match(t));
		assert(Pattern(p).compileToDFA().match(t));
	}

	char meta[] = { '.', '*', '?', '|', '(', ')', '\\', '+', '[', ']' };
	for (int i = 0; i < (int)sizeof(meta) / sizeof(char); ++i)
	{
		string p, t;
		p.push_back('\\');
		p.push_back(meta[i]);
		t.push_back(meta[i]);
		assert(Pattern(p).compile().match(t));
		assert(Pattern(p).compileToDFA().match(t));
	}

	string in = "src\\Test\\TestCase\\PatternTest\\test3\\in.txt";
	string out = "src\\Test\\TestCase\\PatternTest\\test3\\out.txt";
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

	string p, t;
	while (f1 >> p >> t)
	{
		int ans;
		f2 >> ans;

		//NFA match
		{
			try
			{
				bool res = Pattern(p).compile().match(t);
				if ((res && ans != 1) || (!res && ans != 0))
				{
					cout << "test failed" << endl;
					cout << "file: " << in << endl;
					cout << "pat: " << p << endl;
					cout << "txt: " << t << endl;
					cout << "output: " << res << endl;
					exit(0);
				}
			}
			catch (ParseError err)
			{
				cout << "test failed" << endl;
				cout << "file: " << in << endl;
				cout << "pat: " << p << endl;
				cout << "txt: " << t << endl;
				cout << "info: " << err.info() << endl;
				exit(0);
			}
		}

		//DFA match
		{
			try
			{
				bool res = Pattern(p).compileToDFA().match(t);
				if ((res && ans != 1) || (!res && ans != 0))
				{
					cout << "test failed" << endl;
					cout << "file: " << in << endl;
					cout << "pat: " << p << endl;
					cout << "txt: " << t << endl;
					cout << "output: " << res << endl;
					exit(0);
				}
			}
			catch (ParseError err)
			{
				cout << "test failed" << endl;
				cout << "file: " << in << endl;
				cout << "pat: " << p << endl;
				cout << "txt: " << t << endl;
				cout << "info: " << err.info() << endl;
				exit(0);
			}
		}
	}

	cout << "Test 3 finished." << endl;
}
