#include "RegExprParser.h"

#include <iostream>

using namespace std;

ParseError::ParseError(const std::string& msg) : msg(msg)
{

}

std::string ParseError::info() const
{
	return msg;
}

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
		return 0;
	}
	return input[index++];
}

char RegParser::peek()
{
	if (index == input.size())
	{
		return 0;
	}
	return input[index];
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
	NFAGraph ng = parseFactor();
	char ch = peek();
	while (ch != 0 && ch != ')' && ch != '|')
	{
		NFAGraph t = parseFactor();
		ng.concat(t);
		ch = peek();
	}
	return ng;
}

NFAGraph RegParser::parseFactor()
{
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
	char ch = next();
	if ((ch >= 'a' && ch <= 'z') || ch == '.')
	{
		return NFAGraph(ch);
	}
	else if (ch == '(')
	{
		NFAGraph ng = parseExpr();
		read(')');
		return ng;
	}
	else
	{
		string s = "Unexpected character: ";
		s.push_back(ch);
		throw ParseError(s);
	}
}
