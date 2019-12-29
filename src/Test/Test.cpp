#include "Test.h"
#include "../Parser/RegExprParser.h"

#include <iostream>
#include <fstream>

using namespace std;

void ParserTest::run()
{
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

	cout << "Parser tests passed!" << endl;
}
