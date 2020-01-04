#include "RegParser.h"
#include "../Common/Charset.h"
#include "../Common/Error.h"

#include <iostream>

using namespace std;

RegParser::RegParser(const std::string& input) : input(input), index(0)
{

}

void RegParser::setInput(const std::string& input)
{
	this->input = input;
}

RegParser& RegParser::parse(NFA& nfa)
{
	index = 0;
	NFAGraph ng = parseExpr();
	ng.toNFA(nfa);
	ng.clear();
	return *this;
}

char RegParser::next()
{
	if (index == input.size())
	{
		return Charset::End;
	}
	return input[index++];
}

char RegParser::peek()
{
	if (index == input.size())
	{
		return Charset::End;
	}
	return input[index];
}

void RegParser::back()
{
	if (index > 0)
	{
		index--;
	}
}

void RegParser::read(char ch)
{
	if (ch != next())
	{
		string s = "";
		s.push_back(ch);
		s += " expected.";
		throw ParseError(s);
	}
}

NFAGraph RegParser::parseExpr()
{
	//cout << "expr" << endl;
	NFAGraph ng = parseCatExpr();
	while (peek() == '|')
	{
		next();
		NFAGraph t = parseCatExpr();
		ng.parallel(t);
	}
	return ng;
}

NFAGraph RegParser::parseCatExpr()
{
	//cout << "cat" << endl;
	NFAGraph ng = parseFactor();
	char ch = peek();
	while (ch != Charset::End && ch != ')' && ch != '|')
	{
		NFAGraph t = parseFactor();
		ng.concat(t);
		ch = peek();
	}
	return ng;
}

NFAGraph RegParser::parseFactor()
{
	//cout << "fac" << endl;
	NFAGraph ng = parseTerm();
	char ch = peek();
	if (ch == '*')
	{
		next();
		ng.starClosure();
	}
	else if (ch == '+')
	{
		next();
		ng.addClosure();
	}
	return ng;
}

NFAGraph RegParser::parseTerm()
{
	//cout << "term" << endl;
	char ch = next();

	//任意字符
	if (ch == '.')
	{
		return NFAGraph(Charset::AnyChar);
	}
	//左括号
	else if (ch == '(')
	{
		NFAGraph ng = parseExpr();
		read(')');
		return ng;
	}
	//左中括号
	else if (ch == '[')
	{\
		NFAGraph ng = parseScope();
		read(']');
		return ng;
	}
	//转义字符
	else if (ch == '\\')
	{
		if (peek() == Charset::End)
		{
			throw ParseError("Unexpected end of expression.");
		}
		
		char meta = next();
		if (!Charset::IsMetaChar(meta))
		{
			string s;
			s.push_back(meta);
			s += ": ";
			throw ParseError(s + "Meta char expected.");
		}

		return NFAGraph(meta);
	}
	//其余合法字符
	else if (Charset::InCharset(ch))
	{
		return NFAGraph(ch);
	}
	//不合法字符
	else
	{
		string s = "Unexpected character: ";
		s.push_back(ch);
		throw ParseError(s);
	}
}

NFAGraph RegParser::parseScope()
{
	if (peek() == ']')
	{
		throw ParseError("Scope can not be empty.");
	}

	vector<pair<char, char>> scopes;
	while (peek() != ']' && peek() != Charset::End)
	{
		char c1 = parseChar();
		char c2 = c1;
		if (peek() == '-')
		{
			next();
			c2 = parseChar();
		}

		scopes.push_back(pair<char, char>(c1, c2));
	}

	if (peek() == Charset::End)
	{
		throw ParseError("Unexpected end of expression.");
	}

	return NFAGraph(scopes);
}

char RegParser::parseChar()
{
	char ch = next();
	if (ch == '\\')
	{
		ch = next();
		if (!Charset::IsMetaChar(ch))
		{
			string s;
			s.push_back(ch);
			s += ": ";
			throw ParseError(s + "Meta char expected.");
		}
	}

	return ch;
}
